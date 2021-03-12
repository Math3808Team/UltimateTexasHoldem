#ifndef CARD_H
#define CARD_H
#include <string>

class Card {
public:
    Card() = delete;
    Card(const char& suit, const int& rank);

    char suit;
    unsigned short rank;

};

bool operator==(const Card& lhs, const Card& rhs);

#endif // CARD_H
