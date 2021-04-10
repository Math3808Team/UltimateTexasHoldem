#include "handranker.h"

HandRanker::HandRanker(){
    trickVerifiers.append(new PairVerifier());
    trickVerifiers.append(new TwoPairVerifier());
    trickVerifiers.append(new ThreeOfAKindVerifier());
    trickVerifiers.append(new StraightVerifier());
    trickVerifiers.append(new FlushVerifier());
    trickVerifiers.append(new FullHouseVerifier());
    trickVerifiers.append(new FourOfAKindVerifier());
    trickVerifiers.append(new StraightFlushVerifier());
    trickVerifiers.append(new RoyalFlushVerifier());
}

/**
 *  @brief Gives the proper rank to the hand passed in.
 *  @param hand is a instance of Hand
 */
void HandRanker::rankHand(Hand &hand) {
    //Go through each verifier in-order to override the rank of the hand to the highest one.
    QListIterator<TrickVerifier*> i(trickVerifiers);
    while(i.hasNext()) {
        i.next()->verifyHand(hand);
    }   

}

int HandRanker::breakTie(Player player, House house) {
    return trickVerifiers.at(player.hand.rank  - 1)->breakTie(player, house);
}

QString HandRanker::rankToString(int rank) {
    switch(rank) {
        case 1:
           return "pair";
        case 2:
           return "two pair";
        case 3:
           return "three of a kind";
        case 4:
           return "straight";
        case 5:
           return "flush";
        case 6:
           return "full house";
        case 7:
           return "four of a kind";
        case 8:
           return "straight flush";
        case 9:
           return "royal flush";
    }
    return "";
}
