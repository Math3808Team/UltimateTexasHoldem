#include <QDebug>
#include "roundresultservice.h"

const QHash<int, int> RoundResultService::tripsPayoutTable = QHash<int,int>(
        {
          {9, 50},
          {8, 40},
          {7, 30},
          {6, 8},
          {5, 6},
          {4, 5},
          {3, 3}
         });

const QHash<int, float> RoundResultService::blindPayoutTable = QHash<int, float>(
        {
          {9, 500},
          {8, 50},
          {7, 10},
          {6, 3},
          {5, 3.0f/2.0f},
          {4, 1}
          });


RoundResultService::RoundResultService(Player& player, House& house)
    : player(player), house(house) {}

inline int RoundResultService::getTripsPayout(const int& tripsAmount, RoundResult& result) const {
    if (tripsPayoutTable.contains(player.hand.rank)) {
        result.tripsPayout = tripsAmount*tripsPayoutTable[player.hand.rank];
        return tripsAmount + result.tripsPayout;
    }
    result.tripsPayout = -tripsAmount; // payback
    return 0; // payoff
}

inline int RoundResultService::getBlindPayout(const int& blindAmount, RoundResult& result) const {
    if (blindPayoutTable.contains(player.hand.rank)) {
        result.blindPayout = blindAmount*blindPayoutTable[player.hand.rank];
        return blindAmount + result.blindPayout;
    }
    result.blindPayout = -blindAmount;
    return 0;
}

RoundResult RoundResultService::determineWinners(const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount, bool playerFolded) {
    RoundResult result;
    handRanker.rankHand(player.hand);
    handRanker.rankHand(house.hand);

    bool houseQualifies = true;
    if (house.hand.rank < 1)
        houseQualifies = false;

    if (playerFolded) {// then player loses no matter what
        determinePayoutPlayerLoss(true, anteAmount, blindAmount, tripsAmount, playAmount); // always true?
    }

    if (player.hand.rank > house.hand.rank) {
        qInfo() << "player won with a " + handRanker.rankToString(player.hand.rank) + ".";
        result = determinePayoutPlayerWon(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
    } else if (player.hand.rank < house.hand.rank) {
        qInfo() << "house won with a " + handRanker.rankToString(house.hand.rank) + ".";
        result = determinePayoutPlayerLoss(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
    } else {
        qInfo() << "tie being tested: ";

        if (player.hand.rank == 0 && house.hand.rank == 0) {
            //special case where no one has anything
            qInfo() << "tie with nothing.";
            result.winner = 0;
            return result;
        }


       int tieResult = handRanker.breakTie(player,house);
       if (tieResult == 1) {
           qInfo() << "player won with a " + handRanker.rankToString(player.hand.rank) + ".";
           result = determinePayoutPlayerWon(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
       }
       else if (tieResult == 2) {
           qInfo() << "house won with a " + handRanker.rankToString(house.hand.rank) + ".";
           result = determinePayoutPlayerLoss(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
       }
       else {
           qInfo() << "tie with a " + handRanker.rankToString(player.hand.rank) + ".";
           result = determinePayoutTie(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
       }

       return result;
    }
    return result;
}


RoundResult RoundResultService::determinePayoutPlayerWon(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const {
    RoundResult result;
    result.winner = 2;

    // payback = The amount given to the player NOT the net sum of doing the bet.
    int antePayback = 0, blindPayback = 0, tripsPayback = 0, playPayback = 0;

    if (houseQualifies) {
        qInfo() << "Dealer qualifies";
        antePayback = anteAmount * 2;
        result.antePayout = anteAmount;
    } else {
        qInfo() << "Dealer did not qualify";
        antePayback = anteAmount; // push
        result.antePayout = 0;
    }
    blindPayback = getBlindPayout(blindAmount, result);
    playPayback = playAmount * 2;
    result.playPayout = playAmount;
    tripsPayback = getTripsPayout(tripsAmount, result);

    qInfo() << "Player's money: " << player.money;
    qInfo() << "Ante Payback " << (!houseQualifies ? "PUSH" : "") << antePayback;
    qInfo() << "Blind Payback " << blindPayback;
    qInfo() << "Play Payback " << playPayback;
    qInfo() << "Trips Payback " << tripsPayback;

    player.money += antePayback + blindPayback + playPayback + tripsPayback;
    qInfo() << "Player's money AFTER : " << player.money << "\n";

    return result;
}

RoundResult RoundResultService::determinePayoutPlayerLoss(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const {
    RoundResult result;
    result.winner = 1;
    // even if the house does/doesn't qualify, we still lose the blind and play bets.
    result.playPayout = -playAmount;
    result.blindPayout = -blindAmount;

    qInfo() << "Dealer does " << (!houseQualifies ? "not " : "") << "qualify";

    int tripsPayout = getTripsPayout(tripsAmount, result);
    int antePayout = houseQualifies ? 0 : anteAmount;
    result.antePayout = houseQualifies ? 0 : -anteAmount;

    qInfo() << "Player's money: " << player.money;
    qInfo() << "TripsPayout " << tripsPayout;
    qInfo() << "AntePayout " << antePayout;

    player.money += tripsPayout;
    qInfo() << "Player's money AFTER : " << player.money << "\n";
    return result;
}

RoundResult RoundResultService::determinePayoutTie(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const {
    Q_UNUSED(houseQualifies); // In a tie, it doesn't matter if the house qualifies.

    RoundResult result;
    result.winner = 0;
    // regardless of the house qualifiing, all bets are pushed.
    // but trips is optional, so it can change.

    int antePayout = anteAmount, blindPayout = blindAmount, playPayout = playAmount; // push ante, blind and play
    result.antePayout = result.blindPayout = result.playPayout = 0;

    int tripsPayout = getTripsPayout(tripsAmount, result);

    qInfo() << "Player's money: " << player.money;
    qInfo() << "AntePayout " << antePayout;
    qInfo() << "BlindPayout " << blindPayout;
    qInfo() << "PlayPayout " << playPayout;
    qInfo() << "tripsPayout " << tripsPayout;

    player.money += antePayout + blindPayout + playPayout + tripsPayout;
    qInfo() << "Player's money AFTER : " << player.money << "\n";

    return result;
}
