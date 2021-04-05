#include "verifiers/flushverifier.h"

FlushVerifier::FlushVerifier(){
    this->rank = 5;
}

/**
 *  @brief Verifies that a given Hand is a flush. That is: any 5 cards in the hand have the same suit.
 *  @param hand is a instance of Hand
 */
void FlushVerifier::verifyHand(Hand &hand) {
    vector<Card> bestFiveOfSuit;
    QHash<char,int> suitTable = getTableOfSuits(hand);
    QHash<char,int>::iterator it;
    for(it = suitTable.begin(); it != suitTable.end(); it++){
        if(it.value() >= 5){
            hand.rank = rank;
            hand.setTopFiveCards(getBestFiveCards(hand, it.key()));
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
int FlushVerifier::breakTie(Player player, House house) {
    return 0;
}


std::vector<Card> getBestFiveCards(Hand &hand, char suit) {
    //loop through all possible cards (13) of that suit in order of best to worst, seeing if the hand contains it, add it it to the result list util 5 cards have been added
}
