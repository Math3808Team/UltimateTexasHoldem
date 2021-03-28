#include "verifiers/threeofakindverifier.h"
#include "hand.h"

ThreeOfAKindVerifier::ThreeOfAKindVerifier(){
    this->rank = 3;
}

/**
 *  @brief Verifies that a given Hand contains 3 cards with the same face value (regardless of suit)
 *  @param hand is a instance of Hand
 */
void ThreeOfAKindVerifier::verifyHand(Hand &hand) {
    QHash<int,int> valueTable = getTableOfValues(hand);
    QHash<int,int> ::iterator it;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 3){
            hand.rank = rank;
            break;
        }
    }
}
