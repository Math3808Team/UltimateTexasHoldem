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

    if (hand.contains(14)) //if the hand has an ace, add to the count (since it also acts as a 1)
        ++consecutiveCount;

    for (int i = 2; i < 15; i++) {
        if (hand.contains(i)) {
            ++consecutiveCount;

            if (consecutiveCount == 5) {
                hand.rank = rank;
                break;
            }
        } else {
            consecutiveCount = 0;
        }
    }
}

/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int StraightVerifier::breakTie(Player player, House house) {
    return 0;
}
