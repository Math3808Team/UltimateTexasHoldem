#include "card.h"


Card::Card(const char& suit, const int& rank) {
    this->suit = suit;
    this->rank = rank;
}

bool operator==(const Card& lhs, const Card& rhs) {
    return lhs.rank == rhs.rank && lhs.suit == rhs.suit;
}
