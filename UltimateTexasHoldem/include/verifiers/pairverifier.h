#ifndef PAIRVERIFIER_H
#define PAIRVERIFIER_H

#include "trickverifier.h"

class PairVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // PAIRVERIFIER_H
