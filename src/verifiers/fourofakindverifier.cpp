#include "verifiers/fourofakindverifier.h"

FourOfAKindVerifier::FourOfAKindVerifier(){
    this->rank = 7;
}

/*
 *  Verifies that a given Hand contains 4 cards with the same face value regardless of suit.
 *  @param hand is a instance of Hand
 */
void FourOfAKindVerifier::verifyHand(Hand &hand) {
    QHash<int,int> valueTable = getTableOfValues(hand);
    QHash<int,int> ::iterator it;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 4){
            hand.rank = rank;
        }
    }
}
