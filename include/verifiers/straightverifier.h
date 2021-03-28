#ifndef STRAIGHTVERIFIER_H
#define STRAIGHTVERIFIER_H

#include "trickverifier.h"

class StraightVerifier: public TrickVerifier {

public:
    StraightVerifier();
    virtual void verifyHand(Hand &hand) override;
};

#endif // STRAIGHTVERIFIER_H
