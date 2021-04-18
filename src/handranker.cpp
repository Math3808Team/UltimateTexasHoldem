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

/**
 * @brief HandRanker::breakTie Function breaks a tie between the player and the house
 *  A tie occurs when player.rank == house.rank
 * @param player The player object to break the tie between
 * @param house The house object to break the tie between
 * @return An integer indicator of who won, where 0= hands are identical, 1= player won, 2= house won
 */
int HandRanker::breakTie(Player player, House house) {

    if (player.hand.rank == 0 && house.hand.rank == 0)
        return breakRankZeroTie(player, house); //since there are no specific tie breakers for rank 0

    return trickVerifiers.at(player.hand.rank  - 1)->breakTie(player, house);
}


/**
 * @brief tie breaker for case where both player and house has nothing.
 * @param player the Player instance
 * @param house the House instance
 * @return 0 if the hands are identical in value, 1 if player won tie, 2 if the house won tie.
 */
int HandRanker::breakRankZeroTie(Player player, House house) {
    std::vector<Card> playersCards = player.hand.getCards();
    std::vector<Card> housesCards = house.hand.getCards();

    std::sort(playersCards.begin(), playersCards.end(), [](Card& cardL, Card& cardR){return cardL.value > cardR.value; });
    std::sort(housesCards.begin(), housesCards.end(), [](Card& cardL, Card& cardR){return cardL.value > cardR.value; });

    for (int i = 0; i < 5; i++) {
        if (playersCards[i].value > housesCards[i].value)
            return 1;
        else if (playersCards[i].value < housesCards[i].value)
            return 2;
    }
    return 0;
}


