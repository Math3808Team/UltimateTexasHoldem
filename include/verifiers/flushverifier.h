#ifndef FLUSHVERIFIER_H
#define FLUSHVERIFIER_H

#include "trickverifier.h"

class FlushVerifier: public TrickVerifier {

public:
    FlushVerifier();
    virtual void verifyHand(Hand &hand) override;
    virtual int breakTie(Player player, House house) override;
};


#endif // FLUSHVERIFIER_H
