#ifndef TRICKVERIFIER_H
#define TRICKVERIFIER_H

class Hand; //temp until Hand is made

class TrickVerifier {

public:
    virtual bool verifyHand(const Hand &hand) = 0;

protected:
    const int rank;
};


#endif // TRICKVERIFIER_H
