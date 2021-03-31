#ifndef THREEOFAKINDVERIFIER_H
#define THREEOFAKINDVERIFIER_H

#include "trickverifier.h"

class ThreeOfAKindVerifier: public TrickVerifier {

public:
    ThreeOfAKindVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(Player player, House house) override;
};

#endif // THREEOFAKINDVERIFIER_H
