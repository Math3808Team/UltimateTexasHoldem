#include <numeric>
#include "verifiers/straightflushverifier.h"

StraightFlushVerifier::StraightFlushVerifier(){
    this->rank = 8;
}

/**
 *  @brief Verifies that a given Hand has at least 5 cards that are increasing by 1 consecutively and all 5 of those cards have the same suit.
 *  @param hand is a instance of Hand
 */
void StraightFlushVerifier::verifyHand(Hand &hand) {

    char suitOfFlush = '\0';
    QHash<char,int> suitTable = getTableOfSuits(hand);
    QHash<char,int>::iterator it;

    for(it = suitTable.begin(); it != suitTable.end(); it++){
        if(it.value() >= 5){
            suitOfFlush = it.key(); //get the suit of the cards with the highest number of the same suit
            break;
        }
    }

    int consecutiveCount = 0;
    std::vector<Card> fiveBest;

    if (hand.contains(14, suitOfFlush)) { //if the hand has an ace, add to the count (since it also acts as a 1)
        ++consecutiveCount;
        fiveBest.push_back(Card(suitOfFlush, 14));
    }

    for (int i = 2; i < 15; i++) {
        if (hand.contains(i, suitOfFlush)) { //add to the count only if the hand contains the number of in the range and is part of the flush suit
            ++consecutiveCount;
            fiveBest.push_back(Card(suitOfFlush, i));

            if (consecutiveCount == 5)
                hand.rank = rank;
            else if (consecutiveCount > 5)
                fiveBest.erase(fiveBest.begin()); // remove first

        } else {
            if (consecutiveCount >= 5) {
                break;
            }
            fiveBest.clear();
            consecutiveCount = 0;
        }
    }
    if (hand.rank == rank)
        hand.setTopFiveCards(fiveBest);
}


/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int StraightFlushVerifier::breakTie(Player player, House house) {
    return breakStraightTypeTie(player, house);
}
