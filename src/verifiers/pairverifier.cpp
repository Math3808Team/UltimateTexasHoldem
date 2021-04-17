#include "verifiers/pairverifier.h"

PairVerifier::PairVerifier() {
    this->rank = 1;
}

/**
 * @brief getBestFiveCards places the value of the cards that are apart of the pair first in the top five and then the best next 3 cards.
 * @param hand The hand of 7 cards being considered
 * @param valueOfPair The value that makes up the pair in the list (assuming only one since the twoPair will pick up 2 pair case next)
 * @return A vector of the cards which are the best five cards of the hand considering it has a single pair.
 */
std::vector<Card> getBestFiveCardsWithPair(Hand &hand, unsigned int valueOfPair) {

    std::vector<Card> bestFive;

    //add the pair first since they have higher priority in ties
    bestFive.push_back(Card(valueOfPair));
    bestFive.push_back(Card(valueOfPair));

    //add the next highest 3 cards
    for (auto valueIt = Card::values.rbegin(); valueIt != Card::values.rend(); ++valueIt) {
        unsigned short value = *valueIt;
        if (value != valueOfPair && hand.contains(value)) {
            bestFive.push_back(Card(value));

            if (bestFive.size() == 5)
                return bestFive;
        }
    }

    return bestFive;
}

/**
 *  @brief Verifies that a given Hand contains exactly one pair.
 *  @param hand is a instance of Hand
 */
void PairVerifier::verifyHand(Hand &hand) {
    QHash<int,int> valueTable = getTableOfValues(hand);
    QHash<int,int>::iterator it;
    for(it = valueTable.begin(); it != valueTable.end(); it++){
        if(it.value() == 2){
            hand.setTopFiveCards(getBestFiveCardsWithPair(hand, it.key()));
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
int PairVerifier::breakTie(const Player player, const House house) const {
    return breakNormalTypeTie(player, house);
}
