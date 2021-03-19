#ifndef FLUSHVERIFIER_H
#define FLUSHVERIFIER_H

#include "trickverifier.h"

class FlushVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;
}

#endif // FLUSHVERIFIER_H
