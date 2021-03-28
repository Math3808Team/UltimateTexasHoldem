#include "verifiers/trickverifier.h"


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
