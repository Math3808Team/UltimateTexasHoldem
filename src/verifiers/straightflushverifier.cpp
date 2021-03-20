#include "verifiers/straightflushverifier.h"

StraightFlushVerifier::StraightFlushVerifier(){
    this->rank = 8;
}

/*
 *  Verifies that a given Hand has at least 5 cards that are increasing by 1 consecutively and all 5 of those cards have the same suit.
 *  @param hand is a instance of Hand
 */
void StraightFlushVerifier::verifyHand(Hand &hand) {

    char suitOfFlush;
    QHash<char,int> suitTable = getTableOfSuits(hand);
    QHash<char,int>::iterator it;
    for(it = suitTable.begin(); it != suitTable.end(); it++){
        if(it.value() >= 5){
            suitOfFlush = it.key(); //get the suit of the cards with the highest number of the same suit
        }
    }

    int consecutiveCount = 0;

    if (hand.contains(14, suitOfFlush)) //if the hand has an ace, add to the count (since it also acts as a 1)
        consecutiveCount += 1;

    for (int i = 1; i < 15; i++) {
        if (hand.contains(i, suitOfFlush)) { //add to the count only if the hand contains the number of in the range and is part of the flush suit
            consecutiveCount += 1;

            if (consecutiveCount == 5) {
                hand.rank = rank;
                break;
            }
        } else {
            consecutiveCount = 0;
        }
    }
}
