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
    : player(player), house(house) {

}

inline int RoundResultService::getTripsPayout(const int& tripsAmount) const {
    return tripsAmount + (tripsPayoutTable.contains(player.hand.rank) ? tripsAmount*tripsPayoutTable[player.hand.rank] : 0);
}

inline int RoundResultService::getBlindPayout(const int& blindAmount) const {
    return blindAmount + (blindPayoutTable.contains(player.hand.rank) ? blindAmount*blindPayoutTable[player.hand.rank] : 0);
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

    int antePayout = 0, blindPayout = 0, tripsPayout = 0, playPayout = 0;

    if (houseQualifies) {
        qInfo() << "Dealer qualifies";
        antePayout = anteAmount * 2;
    } else {
        qInfo() << "Dealer did not qualify...";
        antePayout = anteAmount; // push
    }
    blindPayout = getBlindPayout(blindAmount);
    playPayout = playAmount * 2;
    tripsPayout = getTripsPayout(tripsAmount);

    qInfo() << "Player's money: " << player.money;
    qInfo() << "AntePayout " << (!houseQualifies ? "PUSH" : "") << antePayout;
    qInfo() << "BlindPayout " << blindPayout;
    qInfo() << "PlayPayout " << playPayout;
    qInfo() << "tripsPayout " << tripsPayout;

    player.money += antePayout + blindPayout + playPayout + tripsPayout;
    qInfo() << "Player's money AFTER : " << player.money << "\n";

    return result;
}

RoundResult RoundResultService::determinePayoutPlayerLoss(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const {
    RoundResult result;
    result.winner = 1;
    // even if the house qualifies, we still lose the blind and play bets.

    qInfo() << "Dealer does " << (!houseQualifies ? "not " : "") << "qualify";

    int tripsPayout = getTripsPayout(tripsAmount);
    int antePayout = houseQualifies ? 0 : anteAmount;

    qInfo() << "Player's money: " << player.money;
    qInfo() << "TripsPayout " << tripsPayout;
    qInfo() << "AntePayout " << antePayout;

    player.money += tripsPayout;
    qInfo() << "Player's money AFTER : " << player.money << "\n";
    return result;
}

RoundResult RoundResultService::determinePayoutTie(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const{
    RoundResult result;
    result.winner = 0;
    // regardless of the house qualifiing, all bets are pushed.
    // but trips is optional, so it can change.

    int antePayout = anteAmount, blindPayout = blindAmount, playPayout = playAmount; // push ante, blind and play
    int tripsPayout = tripsAmount + (tripsPayoutTable.contains(player.hand.rank) ? tripsAmount*tripsPayoutTable[player.hand.rank] : 0);

    qInfo() << "Player's money: " << player.money;
    qInfo() << "AntePayout " << antePayout;
    qInfo() << "BlindPayout " << blindPayout;
    qInfo() << "PlayPayout " << playPayout;
    qInfo() << "tripsPayout " << tripsPayout;

    player.money += antePayout + blindPayout + playPayout + tripsPayout;
    qInfo() << "Player's money AFTER : " << player.money << "\n";

    return result;
}
