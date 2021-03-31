#ifndef STRAIGHTFLUSHVERIFIER_H
#define STRAIGHTFLUSHVERIFIER_H

#include "trickverifier.h"

class StraightFlushVerifier: public TrickVerifier {

public:
    StraightFlushVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(Player player, House house) override;
};

#endif // STRAIGHTFLUSHVERIFIER_H
