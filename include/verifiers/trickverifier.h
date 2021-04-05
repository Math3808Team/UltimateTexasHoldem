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
    virtual int breakTie(Player player, House house) = 0;
    virtual ~TrickVerifier();

protected:
    unsigned short rank;
    QHash <int,int> getTableOfValues(Hand &hand);
    QHash <char,int> getTableOfSuits(Hand &hand);

};


#endif // TRICKVERIFIER_H
