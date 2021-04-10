#include "card.h"


Card::Card(const char& suit, const int& value) {
    this->suit = std::toupper(suit);
    this->value = value;
}

Card::Card(const int& value) {
    this->value = value;
}

std::array<char, 4> Card::suits = {'C', 'S', 'D', 'H'};
std::array<unsigned short, 13> Card::values = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

/**
 * @brief Returns true if both the suit and the value of two cards are the same, false otherwise
 * @param lhs, left hand side of the operator ==, of a card object
 * @param rhs, right hand side of a card object
 * @returns boolean indication of cards are the same
*/
bool operator==(const Card& lhs, const Card& rhs) {
    return lhs.value == rhs.value && lhs.suit == rhs.suit;
}
