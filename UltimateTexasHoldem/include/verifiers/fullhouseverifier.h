#ifndef FULLHOUSEVERIFIER_H
#define FULLHOUSEVERIFIER_H

#include "trickverifier.h"

class FullHouseVerifier: TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) override;

}

#endif // FULLHOUSEVERIFIER_H
