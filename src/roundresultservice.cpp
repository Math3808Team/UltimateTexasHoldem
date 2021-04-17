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

int RoundResultService::getTripsPayout(const int& tripsAmount, RoundResult& result) const {
    if (tripsPayoutTable.contains(player.hand.rank)) {
        result.tripsPayout = tripsAmount*tripsPayoutTable[player.hand.rank];
        return tripsAmount + result.tripsPayout;
    }
    result.tripsPayout = -tripsAmount; // payback (we lost the trips bet)
    return 0; // payoff
}

int RoundResultService::getBlindPayout(const int& blindAmount, RoundResult& result) const {
    if (blindPayoutTable.contains(player.hand.rank)) {
        result.blindPayout = blindAmount*blindPayoutTable[player.hand.rank];
        return blindAmount + result.blindPayout;
    }
    result.blindPayout = 0; // push
    return blindAmount;
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
        result = determinePayoutPlayerWon(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
    } else if (player.hand.rank < house.hand.rank) {
        result = determinePayoutPlayerLoss(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
    } else {

       int tieResult = handRanker.breakTie(player,house);
       if (tieResult == 1) {
           result = determinePayoutPlayerWon(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
       }
       else if (tieResult == 2) {
           result = determinePayoutPlayerLoss(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
       }
       else {
           result = determinePayoutTie(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
       }

       return result;
    }
    return result;
}


RoundResult RoundResultService::determinePayoutPlayerWon(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const {
    RoundResult result;
    result.winner = 1;

    // payback = The amount given to the player NOT the net sum of doing the bet.
    int antePayback = 0, blindPayback = 0, tripsPayback = 0, playPayback = 0;

    if (houseQualifies) {
        antePayback = anteAmount * 2;
        result.antePayout = anteAmount;
    } else {
        antePayback = anteAmount; // push
        result.antePayout = 0;
    }
    blindPayback = getBlindPayout(blindAmount, result);
    playPayback = playAmount * 2;
    result.playPayout = playAmount;
    tripsPayback = getTripsPayout(tripsAmount, result);

    player.money += antePayback + blindPayback + playPayback + tripsPayback;

    result.setTotal();
    return result;
}

RoundResult RoundResultService::determinePayoutPlayerLoss(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const {
    RoundResult result;
    result.winner = 2;
    // even if the house does/doesn't qualify, we still lose the blind and play bets.
    result.playPayout = -playAmount;
    result.blindPayout = -blindAmount;

    result.antePayout = houseQualifies ? -anteAmount : 0;

    int tripsPayout = getTripsPayout(tripsAmount, result);
    int antePayout = houseQualifies ? 0 : anteAmount;

    player.money += tripsPayout + antePayout;

    result.setTotal();
    return result;
}

RoundResult RoundResultService::determinePayoutTie(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const {
    Q_UNUSED(houseQualifies); // In a tie, it doesn't matter if the house qualifies.

    RoundResult result;
    result.winner = 0;

    result.antePayout = result.blindPayout = result.playPayout = 0;

    // regardless of the house qualifing, all bets are pushed.
    int antePayout = anteAmount, blindPayout = blindAmount, playPayout = playAmount; // push ante, blind and play
    int tripsPayout = getTripsPayout(tripsAmount, result);

    player.money += antePayout + blindPayout + playPayout + tripsPayout;

    result.setTotal();
    return result;
}
