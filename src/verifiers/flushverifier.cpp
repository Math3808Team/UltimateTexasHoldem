#include "verifiers/flushverifier.h"

FlushVerifier::FlushVerifier(){
    this->rank = 5;
}

/**
 * @brief getBestFiveCards loops through all possible cards (13) of that suit in order from best to worst, seeing if the hand contains it,
 *                         adds it it to the result list util 5 cards have been added. This determines the best 5 cards in a hand which has a flush.
 * @param hand The hand of 7 cards being considered
 * @param suit The suit which was found to make a flush
 * @return A vector of the cards which are the best five cards of the hand considering it has a flush.
 */
std::vector<Card> getBestFiveCardsWithFlush(Hand &hand, char suit) {

    std::vector<Card> bestFiveOfSuit;
    std::vector<Card> cards = hand.getCards();

    for (auto valueIt = Card::values.rbegin(); valueIt != Card::values.rend(); ++valueIt) {
        unsigned short value = *valueIt;
        if (hand.contains(value,suit)) {
            bestFiveOfSuit.push_back(Card(suit, value));

            if (bestFiveOfSuit.size() == 5)
                return bestFiveOfSuit;
        }
    }

    return bestFiveOfSuit;
}

/**
 *  @brief Verifies that a given Hand is a flush. That is: any 5 cards in the hand have the same suit.
 *  @param hand is a instance of Hand
 */
void FlushVerifier::verifyHand(Hand &hand) {
    QHash<char,int> suitTable = getTableOfSuits(hand);
    QHash<char,int>::iterator it;
    for(it = suitTable.begin(); it != suitTable.end(); it++){
        if(it.value() >= 5){
            hand.rank = rank;
            hand.setTopFiveCards(getBestFiveCardsWithFlush(hand, it.key()));
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
int FlushVerifier::breakTie(const Player player, const House house) const {
    return breakNormalTypeTie(player, house);
}
