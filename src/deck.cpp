#include "deck.h"
#include "card.h"

void Deck::addCard(const Card& card) {
    cards.push_back(card);
}

void Deck::addCards(const std::vector<Card>& othercards) {
    for (Card card : othercards) {
        cards.push_back(card);
    }
}
