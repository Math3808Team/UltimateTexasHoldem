#ifndef FULLHOUSEVERIFIER_H
#define FULLHOUSEVERIFIER_H

#include "trickverifier.h"

class FullHouseVerifier: public TrickVerifier {

public:
    FullHouseVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(Player player, House house) override;

};

#endif // FULLHOUSEVERIFIER_H
