#include "hand.h"
#include <algorithm>

Hand::Hand() {
    cards.reserve(7);
}

/**
 * @brief Function returns the cards from the hand
 * @return a vector of all cards from this hand
*/
const std::vector<Card>& Hand::getCards() const {
    return cards;
}

/**
 * @brief Hand::setTopFiveCards Function sets the top five cards
 * @param topFive The top 5 cards to set
 */
void Hand::setTopFiveCards(std::vector<Card> topFive) {
    // copy swap idiom
    std::swap(topFiveCards, topFive);
}

/**
 * @brief Function returns the top 5 cards
 * @return The top 5 cards
*/
const std::vector<Card>& Hand::getTopFiveCards() const {
    return topFiveCards;
}

/**
 * @brief Function adds a card to a deck
 * @param card, the card to add to the deck
 */
void Hand::addCard(const Card& card) {
    cards.push_back(card);
}

/**
 * @brief Function clears all cards in hand
 */
void Hand::clear() {
    cards.clear();
}

/**
 * @brief Function that returns true if the int value is a value in the deck
 * @param v, The value of the card to search for
 */
bool Hand::contains(int v) {
    return std::find_if(cards.begin(),cards.end(), [v](Card c){return c.value == v;} ) != cards.end();
}

/**
 * @brief Function that returns true if the int value is a value in the deck and the s is a suit of the same card
 * @param v, The value of the card to search for
 * @param v, The suit of the card to search for
 */
bool Hand::contains(int v, char s) {
    return std::find_if(cards.begin(),cards.end(), [v,s](Card c){return c.value == v && c.suit == s;} ) != cards.end();
}
