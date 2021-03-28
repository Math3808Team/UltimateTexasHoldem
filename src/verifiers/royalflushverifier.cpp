#include "verifiers/royalflushverifier.h"

RoyalFlushVerifier::RoyalFlushVerifier(){
    this->rank = 9;
}

/**
 *  @brief Verifies that a given Hand contains each of these cards (numerical): {10, 11, 12, 13, 14} and that they are the same suit.
 *  @param hand is a instance of Hand
 */
void RoyalFlushVerifier::verifyHand(Hand &hand) {
    std::vector<Card> cards = hand.getCards();

    for (auto suitIt = Card::suits.begin(); suitIt != Card::suits.end(); ++suitIt) {
        char suit = *suitIt;

        if (hand.contains(14, suit) && hand.contains(13, suit) && hand.contains(12, suit) && hand.contains(11, suit) && hand.contains(10, suit)) {
            hand.rank = rank;
            break;
        }

    }

}
