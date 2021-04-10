#include <stdexcept>
#include <QDebug>
#include "verifiers/trickverifier.h"

TrickVerifier::TrickVerifier() {

}

TrickVerifier::~TrickVerifier() {

}

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
 * @brief TrickVerifier::getTableOfSuits
 * @param hand The hand being verified
 * @return
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
