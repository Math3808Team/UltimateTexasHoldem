#ifndef FOUROFAKINDVERIFIER_H
#define FOUROFAKINDVERIFIER_H

#include "trickverifier.h"

class FourOfAKindVerifier: public TrickVerifier {

public:
    FourOfAKindVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(const Player player, const House house) const override;
};

#endif // FOUROFAKINDVERIFIER_H
