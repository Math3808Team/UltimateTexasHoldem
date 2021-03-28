#ifndef CARD_H
#define CARD_H
#include <string>
#include <array>
#include <cctype>

class Card {
public:
    Card() = delete;
    Card(const char& suit, const int& value);

    char suit;
    unsigned short value;

    static std::array<char, 4> suits;
    static std::array<unsigned short, 13> values;
};

bool operator==(const Card& lhs, const Card& rhs);

#endif // CARD_H
