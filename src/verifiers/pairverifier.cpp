#include "verifiers/pairverifier.h"

PairVerifier::PairVerifier(){
    this->rank = 1;
}

/**
 *  @brief Verifies that a given Hand contains exactly one pair.
 *  @param hand is a instance of Hand
 */
void PairVerifier::verifyHand(Hand &hand) {
    QHash<int,int> valueTable = getTableOfValues(hand);
    QHash<int,int>::iterator it;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 2){
            hand.rank = rank;
            break;
        }
    }
}
