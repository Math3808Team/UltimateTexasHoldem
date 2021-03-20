#include "verifiers/twopairverifier.h"

TwoPairVerifier::TwoPairVerifier(){
    this->rank = 2;
}

/*
 *  Verifies that a given Hand contains exactly two pairs.
 *  @param hand is a instance of Hand
 */
void TwoPairVerifier::verifyHand(Hand &hand) {
    QHash valueTable = getTableOfValues(hand);
    QHash<int,int> ::iterator it;
    int numPairs = 0;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 2){
            numPairs++;
        }
    }
    if(numPairs == 2){
         hand->rank = rank;
    }
}
