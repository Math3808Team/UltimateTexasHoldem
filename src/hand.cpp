#include "hand.h"

Hand::Hand() {
    cards.reserve(7);
}

std::vector<Card> Hand::getCards() const {
    return cards;
}

void Hand::addCard(const Card& card) {
    cards.push_back(card);
}
