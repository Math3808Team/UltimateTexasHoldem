#include "verifiers/threeofakindverifier.h"
#include "hand.h"

ThreeOfAKindVerifier::ThreeOfAKindVerifier(){
    this->rank = 3;
}

/**
 * @brief getBestFiveCards places the value of the cards that are apart of the triple first in the top five and then the best next 2 cards.
 * @param hand The hand of 7 cards being considered
 * @param valueOfTriple The value that makes up the triple in the list
 * @return A vector of the cards which are the best five cards of the hand considering it has a triple.
 */
std::vector<Card> getBestFiveCardsWithTriple(Hand &hand, unsigned int valueOfTriple) {

    std::vector<Card> bestFive;

    //add the triple first since they have higher priority in ties
    bestFive.push_back(Card(valueOfTriple));
    bestFive.push_back(Card(valueOfTriple));
    bestFive.push_back(Card(valueOfTriple));

    //add the next highest 2 cards
    for (auto valueIt = Card::values.rbegin(); valueIt != Card::values.rend(); ++valueIt) {
        unsigned short value = *valueIt;
        if (value != valueOfTriple && hand.contains(value)) {
            bestFive.push_back(Card(value));

            if (bestFive.size() == 5)
                return bestFive;
        }
    }

    return bestFive;
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
            hand.setTopFiveCards(getBestFiveCardsWithTriple(hand, it.value()));
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
int ThreeOfAKindVerifier::breakTie(const Player player, const House house) const {
    return breakNormalTypeTie(player, house);
}
