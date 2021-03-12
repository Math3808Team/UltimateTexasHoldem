#ifndef STRAIGHTFLUSHVERIFIER_H
#define STRAIGHTFLUSHVERIFIER_H

#include "trickverifier.h"

class StraightFlushVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // STRAIGHTFLUSHVERIFIER_H
