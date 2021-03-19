#ifndef THREEOFAKINDVERIFIER_H
#define THREEOFAKINDVERIFIER_H

#include "trickverifier.h"

class ThreeOfAKindVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // THREEOFAKINDVERIFIER_H
