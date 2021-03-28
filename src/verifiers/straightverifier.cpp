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
