#ifndef FULLHOUSEVERIFIER_H
#define FULLHOUSEVERIFIER_H

#include "trickverifier.h"

class FullHouseVerifier: public TrickVerifier {

public:
    FullHouseVerifier();
    virtual void verifyHand(Hand &hand) override;

};

#endif // FULLHOUSEVERIFIER_H
