#include <stdexcept>
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
            (player.hand.rank != 8 && player.hand.rank != 4))
        throw std::runtime_error("Bad function call, function only callable by Straight tie breaker types");

    auto acumCards = [&](const Hand& hand) -> int {
        const std::vector<Card>& cards = hand.getTopFiveCards();
        int sum = std::accumulate(cards.cbegin(), cards.cend(), 0, [](int accumulator, const Card& card){
            return accumulator + card.value;
        });
        return sum;
    };
    int playerSum = acumCards(player.hand), houseSum = acumCards(house.hand);

    if (playerSum > houseSum) return 1;
    else if (houseSum > playerSum) return 2;
    return 0;
}
