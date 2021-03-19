#include "handranker.h"

HandRanker::HandRanker(){
    trickVerifiers.push_back(PairVerifier());
    trickVerifiers.push_back(TwoPairVerifier());
    trickVerifiers.push_back(ThreeOfAKindVerifier());
    trickVerifiers.push_back(StraightVerifier());
    trickVerifiers.push_back(FlushVerifier());
    trickVerifiers.push_back(FullHouseVerifier());
    trickVerifiers.push_back(FourOfAKindVerifier());
    trickVerifiers.push_back(StraightFlushVerifier());
    trickVerifiers.push_back(RoyalFlushVerifier());
}

/*
 *  Gives the proper rank to the hand passed in.
 *  @param hand is a instance of Hand
 */
void HandRanker::rankHand(Hand &hand) {
    //Go through each verifier in-order to override the rank of the hand to the highest one.
    for(Hand curHand : trickVerifiers) {
        curHand.verifyHand(hand);
    }
}
