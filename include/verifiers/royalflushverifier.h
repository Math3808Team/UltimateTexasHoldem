#ifndef ROYALFLUSHVERIFIER_H
#define ROYALFLUSHVERIFIER_H

#include "trickverifier.h"

class RoyalFlushVerifier: public TrickVerifier {

public:
    RoyalFlushVerifier();
    virtual void verifyHand(Hand &hand) override;
};

#endif // ROYALFLUSHVERIFIER_H
