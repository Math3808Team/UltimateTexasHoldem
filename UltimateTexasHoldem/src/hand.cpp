#include "hand.h"

Hand::Hand() {
    cards.reserve(7);
}

/*
 * Function returns the cards from the hand
 * @return a vector of all cards from this hand
*/
std::vector<Card> Hand::getCards() const {
    return cards;
}

/*
 * Function adds a card to a deck
 * @param card, the card to add to the deck
 */
void Hand::addCard(const Card& card) {
    cards.push_back(card);
}
