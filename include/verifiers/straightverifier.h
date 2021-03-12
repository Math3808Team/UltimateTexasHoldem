#ifndef STRAIGHTVERIFIER_H
#define STRAIGHTVERIFIER_H

#include "trickverifier.h"

class StraightVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // STRAIGHTVERIFIER_H
