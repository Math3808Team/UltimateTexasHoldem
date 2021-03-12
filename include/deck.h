#ifndef DECK_H
#define DECK_H

#include <vector>
#include <initializer_list>
#include "card.h"

class Deck {
public:
    Card getCard();
    void addCard(const Card& card);
    void addCards(const std::vector<Card>& othercards);
private:
    unsigned short numCards;
    std::vector<Card> cards;
};

#endif // DECK_H
