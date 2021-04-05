#ifndef ROYALFLUSHVERIFIER_H
#define ROYALFLUSHVERIFIER_H

#include "trickverifier.h"

class RoyalFlushVerifier: public TrickVerifier {

public:
    RoyalFlushVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(Player player, House house) override;
};

#endif // ROYALFLUSHVERIFIER_H
