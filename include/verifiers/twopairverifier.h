#ifndef TWOPAIRVERIFIER_H
#define TWOPAIRVERIFIER_H

#include "trickverifier.h"

class TwoPairVerifier: public TrickVerifier {

public:
    TwoPairVerifier();
    virtual void verifyHand(Hand &hand) override;
};

#endif // TWOPAIRVERIFIER_H
