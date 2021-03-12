#ifndef TRICKVERIFIER_H
#define TRICKVERIFIER_H

class Hand; //temp until Hand is made

class TrickVerifier {

public:
    virtual void verifyHand(const Hand &hand) = 0;

protected:
    const unsigned short rank;
};


#endif // TRICKVERIFIER_H
