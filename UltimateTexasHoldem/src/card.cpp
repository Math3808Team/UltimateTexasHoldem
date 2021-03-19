#include "card.h"


Card::Card(const char& suit, const int& value) {
    this->suit = std::toupper(suit);
    this->value = value;
}

/*
 * Returns true if both the suit and the value of two cards are the same, false otherwise
 * @param lhs, left hand side of the operator ==, of a card object
 * @param rhs, right hand side of a card object
 * @returns boolean indication of cards are the same
*/
bool operator==(const Card& lhs, const Card& rhs) {
    return lhs.value == rhs.value && lhs.suit == rhs.suit;
}
