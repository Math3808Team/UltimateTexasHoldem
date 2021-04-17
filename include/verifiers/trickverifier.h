#ifndef TRICKVERIFIER_H
#define TRICKVERIFIER_H

#include <QHash>
#include "hand.h"
#include "player.h"
#include "house.h"

class TrickVerifier {

public:
    TrickVerifier();
    virtual void verifyHand(Hand &hand) = 0;
    virtual int breakTie(const Player player, const House house) const = 0;
    virtual ~TrickVerifier();
protected:
    unsigned short rank;
    QHash <int,int> getTableOfValues(Hand &hand);
    QHash <char,int> getTableOfSuits(Hand &hand);

    int breakStraightTypeTie(const Player& player, const House& house) const;
    int breakNormalTypeTie(const Player& player, const House& house) const;
};


#endif // TRICKVERIFIER_H
