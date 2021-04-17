#ifndef THREEOFAKINDVERIFIER_H
#define THREEOFAKINDVERIFIER_H

#include "trickverifier.h"

class ThreeOfAKindVerifier: public TrickVerifier {

public:
    ThreeOfAKindVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(const Player player, const House house) const override;
};

#endif // THREEOFAKINDVERIFIER_H
