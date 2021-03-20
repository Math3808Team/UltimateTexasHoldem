#ifndef TRICKVERIFIER_H
#define TRICKVERIFIER_H

#include <QHash>

class Hand; //temp until Hand is made

class TrickVerifier {

public:
    virtual void verifyHand(const Hand &hand) = 0;

protected:
    const unsigned short rank;
    QHash <int,int> getTableOfValues(Hand &hand);
    QHash <int,int> getTableOfSuits(Hand &hand);
};


#endif // TRICKVERIFIER_H
