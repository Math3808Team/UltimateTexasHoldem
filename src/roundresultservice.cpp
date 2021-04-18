#include <QDebug>
#include "roundresultservice.h"


// For both the trips and blind table payouts:
// {Hand's rank, Ratio payout}
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

/**
 * @brief RoundResultService::getTripsPayout Function sets the trips payout based on the player's hand/rank
 * @param tripsAmount The amount of the trips bet the player initally set
 * @param result Result object to store the trip's payback
 * @return Returns the trips payoff of the player's hand/rank
 */
int RoundResultService::getTripsPayout(const int& tripsAmount, RoundResult& result) const {
    if (tripsPayoutTable.contains(player.hand.rank)) {
        result.tripsPayout = tripsAmount*tripsPayoutTable[player.hand.rank];
        return tripsAmount + result.tripsPayout;
    }
    result.tripsPayout = -tripsAmount; // payback (we lost the trips bet)
    return 0; // payoff
}

/**
 * @brief RoundResultService::getBlindPayout Function sets the blind payout based on the player's hand/rank
 * @param blindAmount The amount of the blind bet the player initally set
 * @param result Result object to store the blind's payback
 * @return Returns the blind payoff of the player's hand/rank
 */
int RoundResultService::getBlindPayout(const int& blindAmount, RoundResult& result) const {
    if (blindPayoutTable.contains(player.hand.rank)) {
        result.blindPayout = blindAmount*blindPayoutTable[player.hand.rank];
        return blindAmount + result.blindPayout;
    }
    result.blindPayout = 0; // push
    return blindAmount;
}

/**
 * @brief RoundResultService::determineWinners Function determines the winner of two hands, namely the player's and dealer's hand,
 *   This function returns a Roundresult object describing who won and the respective paybacks of winning/losing. After calling this function,
 *   the player's money is set to the true amount after winning/losing.
 * @param anteAmount The ante amount the player initally placed
 * @param blindAmount The blind amount the player initally placed
 * @param tripsAmount The trips amount the player initally placed
 * @param playAmount The play amount the player initally placed
 * @param playerFolded An indicator if the player folded his hand or not.
 * @return A RoundResult object describing the result of who won and the payback of the player.
 */
RoundResult RoundResultService::determineWinners(const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount, bool playerFolded) {
    RoundResult result;
    handRanker.rankHand(player.hand);
    handRanker.rankHand(house.hand);

    // House qualifies only if his hand is at least a pair
    bool houseQualifies = true;
    if (house.hand.rank < 1)
        houseQualifies = false;

    if (playerFolded) {// then player loses no matter what
        determinePayoutPlayerLoss(true, anteAmount, blindAmount, tripsAmount, playAmount);
    }

    if (player.hand.rank > house.hand.rank) {      
        result = determinePayoutPlayerWon(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
    } else if (player.hand.rank < house.hand.rank) {
        result = determinePayoutPlayerLoss(houseQualifies, anteAmount, blindAmount, tripsAmount, playAmount);
    } else {
       // Both hands have same rank, try breaking the tie by using top 5 cards
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

/**
 * @brief RoundResultService::determinePayoutPlayerWon Function computes the RoundResult object with information that the player won
 * @param houseQualifies Boolean indicating if the house qualified(house.rank >= 1)
 * @param anteAmount The ante amount the player initally placed
 * @param blindAmount The blind amount the player initally placed
 * @param tripsAmount The trips amount the player initally placed
 * @param playAmount The play amount the player initally placed
 * @return The completed RoundResult object representing paybacks respective of the player winning
 */
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

/**
 * @brief RoundResultService::determinePayoutPlayerLoss Function computes the RoundResult object with information that the player lost
 * @param houseQualifies Boolean indicating if the house qualified(house.rank >= 1)
 * @param anteAmount The ante amount the player initally placed
 * @param blindAmount The blind amount the player initally placed
 * @param tripsAmount The trips amount the player initally placed
 * @param playAmount The play amount the player initally placed
 * @return The completed RoundResult object representing paybacks respective of the player losing
 */
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

/**
 * @brief RoundResultService::determinePayoutTie Function computes the RoundResult object with information that the player tied with the house
 * @param houseQualifies Boolean indicating if the house qualified(house.rank >= 1)
 * @param anteAmount The ante amount the player initally placed
 * @param blindAmount The blind amount the player initally placed
 * @param tripsAmount The trips amount the player initally placed
 * @param playAmount The play amount the player initally placed
 * @return The completed RoundResult object representing paybacks respective of the player having a tie with the house
 */
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
