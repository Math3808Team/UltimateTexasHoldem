#ifndef ROYALFLUSHVERIFIER_H
#define ROYALFLUSHVERIFIER_H

#include "trickverifier.h"

class RoyalFlushVerifier: public TrickVerifier {

public:
    RoyalFlushVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(const Player player, const House house) const override;
};

#endif // ROYALFLUSHVERIFIER_H
