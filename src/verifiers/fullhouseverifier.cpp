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

    std::vector<Card> topTwoValues;

    bool foundTriple = false;
    bool foundDouble = false;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if (it.value() >= 3) {
            foundTriple = true;
            topTwoValues.push_back(Card(it.key()));

        }
        else if(it.value() == 2){
            foundDouble = true;
            topTwoValues.push_back(Card(it.key()));
        }
    }

    if (foundTriple && foundDouble) {
        hand.rank = rank;
        hand.setTopFiveCards(topTwoValues);
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

/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int FullHouseVerifier::breakTie(Player player, House house) {
    std::vector<Card> playersCards = player.hand.getTopFiveCards();
    std::vector<Card> housesCards = house.hand.getTopFiveCards();

    for (int i = 0; i < 2; i++) { //will only contain two cards, one for the triple and one for the double in the full house
        if (playersCards[i].value > housesCards[i].value)
            return 1;
        else if (playersCards[i].value < housesCards[i].value)
            return 2;
    }
    return 0;
}
