#ifndef HAND_H
#define HAND_H

#include <vector>
#include <algorithm>
#include <card.h>

class Hand {
public:
    Hand();

    const std::vector<Card>& getCards() const;
    const std::vector<Card>& getFiveBestCards() const;
    void addCard(const Card& card);
    void setFiveBestCards(std::vector<Card> cards);
    void clear();
    bool contains(int v);
    bool contains(int v, char s);

    unsigned short rank = 0;
private:
    std::vector<Card> cards;
    std::vector<Card> fiveBestCards;
};

#endif // HAND_H
