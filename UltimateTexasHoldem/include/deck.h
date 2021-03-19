#ifndef DECK_H
#define DECK_H

#include <vector>
#include <initializer_list>
#include <random>
#include "card.h"

class Deck {
public:
    Deck();
    Card getCard();
private:
    unsigned short numCards;
    std::vector<Card> cards;
    std::mt19937 rng_generator;
};

#endif // DECK_H
