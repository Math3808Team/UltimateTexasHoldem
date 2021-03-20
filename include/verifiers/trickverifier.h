#ifndef TRICKVERIFIER_H
#define TRICKVERIFIER_H

#include <QHash>

class Hand; //temp until Hand is made

class TrickVerifier {

public:
    virtual void verifyHand(Hand &hand) = 0;

protected:
    unsigned short rank;
};


#endif // TRICKVERIFIER_H
