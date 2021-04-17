#ifndef FLUSHVERIFIER_H
#define FLUSHVERIFIER_H

#include "trickverifier.h"

class FlushVerifier: public TrickVerifier {

public:
    FlushVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(const Player player, const House house) const override;
};


#endif // FLUSHVERIFIER_H
