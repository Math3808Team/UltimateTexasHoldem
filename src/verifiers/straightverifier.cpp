#include "verifiers/straightverifier.h"

StraightVerifier::StraightVerifier(){
    this->rank = 4;
}

/**
 *  @brief Verifies that a given Hand has at least 5 cards that are increasing by 1 consecutively.
 *  @param hand is a instance of Hand
 */
void StraightVerifier::verifyHand(Hand &hand) {
    int consecutiveCount = 0;
    std::vector<Card> fiveBest;
    if (hand.contains(14)) {//if the hand has an ace, add to the count (since it also acts as a 1)
        ++consecutiveCount;
         fiveBest.push_back(Card('s', 14)); // suit doesn't matter.
    }
    for (int i = 2; i < 15; i++) {
        if (hand.contains(i)) {
            ++consecutiveCount;
            fiveBest.push_back(Card('s', i)); // suit doesn't matter
            if (consecutiveCount == 5)
                hand.rank = rank;
            else if (consecutiveCount >  5)
                fiveBest.erase(fiveBest.begin()); // remove first

        } else {
            if (consecutiveCount >= 5 ) break;
            consecutiveCount = 0;
            fiveBest.clear();
        }
    }
    if (hand.rank == rank)
        hand.setTopFiveCards(fiveBest);

}

/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int StraightVerifier::breakTie(const Player player, const House house) const {
    return breakStraightTypeTie(player, house);
}
