#ifndef FULLHOUSEVERIFIER_H
#define FULLHOUSEVERIFIER_H

#include "trickverifier.h"

class FullHouseVerifier: public TrickVerifier {

public:
    FullHouseVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(const Player player, const House house) const override;

};

#endif // FULLHOUSEVERIFIER_H
