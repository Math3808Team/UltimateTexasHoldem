#include "verifiers/twopairverifier.h"
#include "hand.h"

TwoPairVerifier::TwoPairVerifier(){
    this->rank = 2;
}

/**
 * @brief getBestFiveCards places the value of the cards that are apart of the two pairs first in the top five and then the best next card.
 * @param hand The hand of 7 cards being considered
 * @param valueOfFirstPair The value that makes up the first found pair
 * @param valueOfSecondPair The value that makes up the second found pair
 * @return A vector of the cards which are the best five cards of the hand considering it has a two pair.
 */
std::vector<Card> getBestFiveCardsWithTwoPair(Hand &hand, unsigned int valueOfFirstPair, unsigned int valueOfSecondPair) {

    std::vector<Card> bestFive;

    //add the two pair first since they have higher priority in ties
    if (valueOfFirstPair > valueOfSecondPair) {
        bestFive.push_back(Card(valueOfFirstPair));
        bestFive.push_back(Card(valueOfFirstPair));
        bestFive.push_back(Card(valueOfSecondPair));
        bestFive.push_back(Card(valueOfSecondPair));
    } else {
        bestFive.push_back(Card(valueOfSecondPair));
        bestFive.push_back(Card(valueOfSecondPair));
        bestFive.push_back(Card(valueOfFirstPair));
        bestFive.push_back(Card(valueOfFirstPair));
    }


    //add the next highest card
    for (auto valueIt = Card::values.rbegin(); valueIt != Card::values.rend(); ++valueIt) {
        unsigned short value = *valueIt;
        if (value != valueOfFirstPair && value != valueOfSecondPair && hand.contains(value)) {
            bestFive.push_back(Card(value));

            if (bestFive.size() == 5)
                return bestFive;
        }
    }

    return bestFive;
}

/**
 *  @brief Verifies that a given Hand contains exactly two pairs.
 *  @param hand is a instance of Hand
 */
void TwoPairVerifier::verifyHand(Hand &hand) {
    QHash<int,int> valueTable = getTableOfValues(hand);
    QHash<int,int> ::iterator it;

    int firstPairValue = 0;
    int numPairs = 0;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 2){

            numPairs++;
        }
        if (numPairs == 1){
            firstPairValue = it.value();
        } else if(numPairs == 2){
             hand.setTopFiveCards(getBestFiveCardsWithTwoPair(hand, firstPairValue, it.value()));
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
int TwoPairVerifier::breakTie(Player player, House house) {
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
