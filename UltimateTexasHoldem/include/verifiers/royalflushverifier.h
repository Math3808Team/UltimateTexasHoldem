#ifndef ROYALFLUSHVERIFIER_H
#define ROYALFLUSHVERIFIER_H

#include "trickverifier.h"

class RoyalFlushVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // ROYALFLUSHVERIFIER_H
