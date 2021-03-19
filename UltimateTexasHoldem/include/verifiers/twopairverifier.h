#ifndef TWOPAIRVERIFIER_H
#define TWOPAIRVERIFIER_H

#include "trickverifier.h"

class TwoPairVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // TWOPAIRVERIFIER_H
