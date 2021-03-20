#include "verifiers/royalflushverifier.h"

RoyalFlushVerifier::RoyalFlushVerifier(){
    this->rank = 9;
}

/*
 *  Verifies that a given Hand contains each of these cards (numerical): {10, 11, 12, 13, 14} and that they are the same suit.
 *  @param hand is a instance of Hand
 */
void RoyalFlushVerifier::verifyHand(Hand &hand) {
    std::vector<Card> cards = hand.getCards();
    std::sort(cards.begin(),cards.end(), [](Card c1, Card c2){return c1.value > c2.value;} );

    //make all 4 royal flushes and then check if the hand is a subset of any of em
}
