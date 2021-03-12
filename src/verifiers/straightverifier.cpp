#include "verifiers/straightverifier.h"

StraightVerifier::StraightVerifier(){
    this->rank = 4;
}

/*
 *  Verifies that a given Hand has at least 5 cards that are increasing by 1 consecutively.
 *  @param hand is a instance of Hand
 */
void StraightVerifier::verifyHand(Hand &hand) {
    //Go over the hand's cards and if there is a 14 (Ace) add a new instance of Card to the hand with the value 1 and with the same suit as the 14. This will account for the Ace being either 1 or 14.
    //Ensure the (up to 4) 1 value ace cards are removed afterwards.
}
