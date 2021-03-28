#include "verifiers/flushverifier.h"

FlushVerifier::FlushVerifier(){
    this->rank = 5;
}

/**
 *  @brief Verifies that a given Hand is a flush. That is: any 5 cards in the hand have the same suit.
 *  @param hand is a instance of Hand
 */
void FlushVerifier::verifyHand(Hand &hand) {
    QHash<char,int> suitTable = getTableOfSuits(hand);
    QHash<char,int>::iterator it;
    for(it = suitTable.begin(); it != suitTable.end(); it++){
        if(it.value() >= 5){
            hand.rank = rank;
            break;
        }
    }
}
