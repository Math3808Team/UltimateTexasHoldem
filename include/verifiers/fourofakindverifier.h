#ifndef FOUROFAKINDVERIFIER_H
#define FOUROFAKINDVERIFIER_H

#include "trickverifier.h"

class FourOfAKindVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // FOUROFAKINDVERIFIER_H
