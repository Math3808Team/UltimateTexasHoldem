#include "verifiers/fullhouseverifier.h"

FullHouseVerifier::FullHouseVerifier(){
    this->rank = 6;
}

/**
 *  @brief Verifies that a given Hand contains one pair and a three of a kind.
 *  @param hand is a instance of Hand
 */
void FullHouseVerifier::verifyHand(Hand &hand) {
    QHash<int,int> valueTable = getTableOfValues(hand);
    QHash<int,int> ::iterator it;

    bool foundTriple = false;
    bool foundDouble = false;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 2){
            foundDouble = true;
        } else if (it.value() >= 3) {
            foundTriple = true;
        }
    }

    if (foundTriple && foundDouble) {
        hand.rank = rank;
    }

    //check for case where extra cards mean there could be 3 of each suit
    int greaterThanThree = 0;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() >= 3){
            ++greaterThanThree;
        }
    }

    if (greaterThanThree >= 2) {
        hand.rank = rank;
    }

}
