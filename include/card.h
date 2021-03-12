#ifndef CARD_H
#define CARD_H
#include <string>
#include <array>

class Card {
public:
    Card() = delete;
    Card(const char& suit, const int& value);

    char suit;
    unsigned short value;

    static constexpr std::array<char, 4> suits = {'C', 'S', 'D', 'H'};
    static constexpr std::array<unsigned short, 13> values = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
};

bool operator==(const Card& lhs, const Card& rhs);

#endif // CARD_H
