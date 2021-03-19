#ifndef HANDRANKER_H
#define HANDRANKER_H

#include <vector>
#include "verifiers/trickverifier.h"
#include "verifiers/pairverifier.h"
#include "verifiers/twopairverifier.h"
#include "verifiers/threeofakindverifier.h"
#include "verifiers/fourofakindverifier.h"
#include "verifiers/straightverifier.h"
#include "verifiers/flushverifier.h"
#include "verifiers/fullhouseverifier.h"
#include "verifiers/straightflushverifier.h"
#include "verifiers/royalflushverifier.h"

class Hand;

class HandRanker {

public:
    void rankHand(Hand hand);

private:
    std::vector<TrickVerifier> trickVerifiers;
}

#endif // HANDRANKER_H
