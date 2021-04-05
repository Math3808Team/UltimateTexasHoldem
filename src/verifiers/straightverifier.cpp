#include "verifiers/straightverifier.h"

StraightVerifier::StraightVerifier(){
    this->rank = 4;
}

/**
 *  @brief Verifies that a given Hand has at least 5 cards that are increasing by 1 consecutively.
 *  @param hand is a instance of Hand
 */
void StraightVerifier::verifyHand(Hand &hand) {
    int consecutiveCount = 0;
    std::vector<Card> fiveBest;
    const std::vector<Card>& cards = hand.getCards();
    if (hand.contains(14)) //if the hand has an ace, add to the count (since it also acts as a 1)
        ++consecutiveCount;

    for (int i = 2; i < 15; i++) {
        if (hand.contains(i)) {
            ++consecutiveCount;
            fiveBest.push_back(*std::find_if(cards.cbegin(), cards.cend(), [&](const Card& c ){return c.value == i;}));
            if (consecutiveCount == 5) {
                hand.rank = rank;
                hand.setFiveBestCards(fiveBest);
                break;
            }
        } else {
            consecutiveCount = 0;
            fiveBest.clear();
        }
    }

}

/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int StraightVerifier::breakTie(Player player, House house) {
    // same code as in StraightFlushVerifier::breakTie
    auto acumCards = [&](const Hand& hand) -> int {
        const std::vector<Card>& cards = hand.getFiveBestCards();
        int sum = std::accumulate(cards.cbegin(), cards.cend(), 0, [](int accumulator, const Card& card){
            return accumulator + card.value;
        });
        return sum;
    };
    int playerSum = acumCards(player.hand), houseSum = acumCards(house.hand);

    if (playerSum > houseSum) return 1;
    else if (houseSum > playerSum) return 2;
    return 0;
    return 0;
}
