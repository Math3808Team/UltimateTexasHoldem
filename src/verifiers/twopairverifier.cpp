#include "verifiers/twopairverifier.h"
#include "hand.h"

TwoPairVerifier::TwoPairVerifier(){
    this->rank = 2;
}

/**
 *  @brief Verifies that a given Hand contains exactly two pairs.
 *  @param hand is a instance of Hand
 */
void TwoPairVerifier::verifyHand(Hand &hand) {
    QHash<int,int> valueTable = getTableOfValues(hand);
    QHash<int,int> ::iterator it;
    int numPairs = 0;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 2){
            numPairs++;
        }
    }
    if(numPairs == 2){
         hand.rank = rank;
    }
}


/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int TwoPairVerifier::breakTie(Player player, House house) {
    return 0;
}
