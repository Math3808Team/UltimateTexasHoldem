#ifndef TWOPAIRVERIFIER_H
#define TWOPAIRVERIFIER_H

#include "trickverifier.h"

class TwoPairVerifier: public TrickVerifier {

public:
    TwoPairVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(Player player, House house) override;
};

#endif // TWOPAIRVERIFIER_H
