#include "verifiers/fourofakindverifier.h"

FourOfAKindVerifier::FourOfAKindVerifier(){
    this->rank = 7;
}

/**
 * @brief getBestFiveCards places the value of the cards that are apart of the four first in the top five and then the best next card.
 * @param hand The hand of 7 cards being considered
 * @param valueOfFour The value that makes up the four in the list
 * @return A vector of the cards which are the best five cards of the hand considering it has a four of a kind.
 */
std::vector<Card> getBestFiveCardsWithFour(Hand &hand, unsigned int valueOfFour) {

    std::vector<Card> bestFive;

    //add the four first since they have higher priority in ties
    bestFive.push_back(Card(valueOfFour));
    bestFive.push_back(Card(valueOfFour));
    bestFive.push_back(Card(valueOfFour));
    bestFive.push_back(Card(valueOfFour));

    //add the next highest card
    for (auto valueIt = Card::values.rbegin(); valueIt != Card::values.rend(); ++valueIt) {
        unsigned short value = *valueIt;
        if (value != valueOfFour && hand.contains(value)) {
            bestFive.push_back(Card(value));

            if (bestFive.size() == 5)
                return bestFive;
        }
    }

    return bestFive;
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
            hand.setTopFiveCards(getBestFiveCardsWithFour(hand, it.key()));
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
    std::vector<Card> playersCards = player.hand.getTopFiveCards();
    std::vector<Card> housesCards = house.hand.getTopFiveCards();

    for (int i = 0; i < 5; i++) {
        if (playersCards[i].value > housesCards[i].value)
            return 1;
        else if (playersCards[i].value < housesCards[i].value)
            return 2;
    }
    return 0;
}
