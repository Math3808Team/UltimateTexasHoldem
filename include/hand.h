#ifndef HAND_H
#define HAND_H

#include <vector>
#include <algorithm>
#include <card.h>

class Hand {
public:
    Hand();

    std::vector<Card> getCards() const;
    void addCard(const Card& card);
    void clear();
    bool contains(int v);
    bool contains(int v, char s);

    unsigned short rank = 0;
private:
    std::vector<Card> cards;
};

#endif // HAND_H
