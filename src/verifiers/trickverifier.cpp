#include <stdexcept>
#include <QDebug>
#include "verifiers/trickverifier.h"

TrickVerifier::TrickVerifier() {

}

TrickVerifier::~TrickVerifier() {

}

/**
 * @brief TrickVerifier::getTableOfValues Helper function to get a table of values per a hand
 * @param hand A hand instance to supply to grain the table of values
 * @return A hash table of key=cardValue, data=frequency of the value in the hand
 */
QHash<int,int> TrickVerifier::getTableOfValues(Hand &hand) {

    QHash<int, int> valueTable;
    std::vector<Card> cards = hand.getCards();

    for (unsigned int i = 0; i < cards.size(); i++) {
        int cardValue = cards[i].value;

        if (valueTable.contains(cardValue))
            valueTable.insert(cardValue, *valueTable.find(cardValue) + 1);
        else
            valueTable.insert(cardValue, 1);
    }

    return valueTable;
}

/**
 * @brief TrickVerifier::getTableOfSuits Helper function to get a table of suits per a hand
 * @param hand The hand being verified
 * @return A hash table of key=suit, data=frequency of the suit in the hand
 */
QHash<char,int> TrickVerifier::getTableOfSuits(Hand &hand) {
    QHash<char, int> suitTable;
    std::vector<Card> cards = hand.getCards();

    for (unsigned int i = 0; i < cards.size(); i++) {
        char cardSuit = cards[i].suit;

        if (suitTable.contains(cardSuit))
            suitTable.insert(cardSuit, *suitTable.find(cardSuit) + 1);
        else
            suitTable.insert(cardSuit, 1);
    }

    return suitTable;
}

/**
 * @brief TrickVerifier::breakStraightTypeTie Helper function to break a tie between the player and the house
 *  under the condition that both hands are straights(4) or straight flushes(8)
 * @param player player instance to break the straight between, in where TopFiveCards are IN ORDER of best card to worst
 * @param house house instance to break the straight between, in where TopFiveCards are IN ORDER of best card to worst
 * @return 0 iff results in a complete tie, 1 if the player won, 2 if the house won
 */
int TrickVerifier::breakStraightTypeTie(const Player& player, const House& house) const {

    if (player.hand.rank != house.hand.rank ||
            (player.hand.rank != 8 && player.hand.rank != 4)) {
        qDebug() << "Bad function call, function only callable by Straight tie breaker types";
        return 0;
    }

    const std::vector<Card>& playerTop5 = player.hand.getTopFiveCards();
    const std::vector<Card>& houseTop5 = house.hand.getTopFiveCards();
    Card playerFirst = playerTop5[0], houseFirst = houseTop5[0];
    // Ace is at the front of the list, then it's actually counting as a 1 instead of an ace's 14.
    if (playerFirst.value == 14) playerFirst.value = 1;
    if (houseFirst.value == 14) houseFirst.value = 1;

    // only need to compare the first card, it's the lowest card of the straight
    if (playerFirst.value > houseFirst.value) return 1;
    else if (playerFirst.value < houseFirst.value) return 2;
    return 0;
}

/**
 * @brief Helper function for each verifier to call if their tie breaking is simple.
 *        Simply checks for who's top five cards are best from first card in list to last.
 * @param player instance with a TopFiveCards which should be IN ORDER from best card to worst based on trick it has
 * @param house  instance with a TopFiveCards which should be IN ORDER from best card to worst based on trick it has
 * @return 0 iff results in a complete tie, 1 if the player won, 2 if the house won
 */
int TrickVerifier::breakNormalTypeTie(const Player& player, const House& house) const {
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
