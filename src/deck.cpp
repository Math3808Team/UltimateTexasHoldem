#include <random>
#include <array>
#include <exception>
#include "deck.h"
#include "card.h"

/**
 * @brief First initalizes our random generator by a random seed(by a random device)
 *        Our deck is filled with 52 cards
*/
Deck::Deck() : rng_generator(std::random_device()()) {
    // add all 52 cards here.
    for (auto suitIt = Card::suits.begin(); suitIt != Card::suits.end(); ++suitIt) {
        char suit = *suitIt;
        for (auto valueIt = Card::values.begin(); valueIt != Card::values.end(); ++valueIt) {
            unsigned short value = *valueIt;
            cards.emplace_back(suit, value);
        }
    }
}

/**
 * @brief Function gets a random card from the list of cards
 * @returns a Card object taken from the list; removes the card from the list
 */
Card Deck::getCard() {
    std::uniform_int_distribution<> distr(0, static_cast<int>(cards.size()));
    int k = distr(rng_generator);
    // note we don't have checks for when the deck is empty, okay for now
    Card card = cards.at(k);
    cards.erase(cards.begin() + k);
    return card;
}

