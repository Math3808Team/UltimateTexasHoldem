#ifndef HANDRANKER_H
#define HANDRANKER_H

#include <QList>
#include "verifiers/trickverifier.h"
#include "verifiers/pairverifier.h"
#include "verifiers/twopairverifier.h"
#include "verifiers/threeofakindverifier.h"
#include "verifiers/fourofakindverifier.h"
#include "verifiers/straightverifier.h"
#include "verifiers/flushverifier.h"
#include "verifiers/fullhouseverifier.h"
#include "verifiers/straightflushverifier.h"
#include "verifiers/royalflushverifier.h"
#include "player.h"
#include "house.h"

class Hand;

class HandRanker {

public:
    HandRanker();

    void rankHand(Hand &hand);
    int breakTie(Player player, House house);

private:
    QList<TrickVerifier*> trickVerifiers;
};

#endif // HANDRANKER_H
