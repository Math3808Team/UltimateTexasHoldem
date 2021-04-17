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
std::vector<Card> getBestFiveCardsWithTwoPair(Hand &hand, unsigned int valueOfBestPair, unsigned int valueOfSecondBestPair) {

    std::vector<Card> bestFive;

    //add the two pair first since they have higher priority in ties
    bestFive.push_back(Card(valueOfBestPair));
    bestFive.push_back(Card(valueOfBestPair));
    bestFive.push_back(Card(valueOfSecondBestPair));
    bestFive.push_back(Card(valueOfSecondBestPair));

    //add the next highest card
    for (auto valueIt = Card::values.rbegin(); valueIt != Card::values.rend(); ++valueIt) {
        unsigned short value = *valueIt;
        if (value != valueOfBestPair && value != valueOfSecondBestPair && hand.contains(value)) {
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

    std::vector<unsigned int> listOfValuePairs;

    //Find the best 2 pairs in set (if they exist)
    //There could be 3 pairs, thus we must look at more than just first 2 pairs.
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 2){
            listOfValuePairs.push_back(it.key());
        }
    }

    if (listOfValuePairs.size() >= 2) {
        hand.rank = rank;

        //sort the list of pairs to pass the best 2 pairs
        std::sort(listOfValuePairs.rbegin(), listOfValuePairs.rend());
        hand.setTopFiveCards(getBestFiveCardsWithTwoPair(hand, listOfValuePairs[0], listOfValuePairs[1]));
    }

}


/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int TwoPairVerifier::breakTie(const Player player, const House house) const {
    breakNormalTypeTie(player, house);
}
