#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

class Player {
public:
    unsigned long money = 10000;

private:
    Hand hand;
};

#endif // PLAYER_H
