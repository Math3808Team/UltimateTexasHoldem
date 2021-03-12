#ifndef STRAIGHTFLUSHVERIFIER_H
#define STRAIGHTFLUSHVERIFIER_H

#include "trickverifier.h"

class StraightRoyalFlushVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // STRAIGHTFLUSHVERIFIER_H
