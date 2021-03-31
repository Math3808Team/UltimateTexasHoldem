#include "verifiers/fourofakindverifier.h"

FourOfAKindVerifier::FourOfAKindVerifier(){
    this->rank = 7;
}

/**
 *  @brief Verifies that a given Hand contains 4 cards with the same face value regardless of suit.
 *  @param hand is a instance of Hand
 */
void FourOfAKindVerifier::verifyHand(Hand &hand) {
    QHash<int,int> valueTable = getTableOfValues(hand);
    QHash<int,int> ::iterator it;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 4){
            hand.rank = rank;
            break;
        }
    }
}

/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int FourOfAKindVerifier::breakTie(Player player, House house) {
    return 0;
}
