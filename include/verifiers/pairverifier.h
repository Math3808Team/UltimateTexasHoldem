#ifndef PAIRVERIFIER_H
#define PAIRVERIFIER_H

#include "trickverifier.h"

class PairVerifier: public TrickVerifier {

public:
    PairVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(const Player player, const House house) const override;
};

#endif // PAIRVERIFIER_H
