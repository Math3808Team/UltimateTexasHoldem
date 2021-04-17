#include "verifiers/royalflushverifier.h"

RoyalFlushVerifier::RoyalFlushVerifier(){
    this->rank = 9;
}

/**
 *  @brief Verifies that a given Hand contains each of these cards (numerical): {10, 11, 12, 13, 14} and that they are the same suit.
 *  @param hand is a instance of Hand
 */
void RoyalFlushVerifier::verifyHand(Hand &hand) {
    std::vector<Card> cards = hand.getCards();

    for (auto suitIt = Card::suits.begin(); suitIt != Card::suits.end(); ++suitIt) {
        char suit = *suitIt;

        if (hand.contains(14, suit) && hand.contains(13, suit) && hand.contains(12, suit) && hand.contains(11, suit) && hand.contains(10, suit)) {
            hand.rank = rank;
            break;
        }

    }

}

/**
 *  @brief determines who wins a tied rank, could also be a complete tie.
 *  @param player a Player instance, contains the needed hand to compare
 *  @param house a House instance, contains the needed hand to compare
 *  @returns 1 if the player won, 2 if the house won else 0 if it was a tie.
 */
int RoyalFlushVerifier::breakTie(Player player, House house) {
    Q_UNUSED(player);
    Q_UNUSED(house);
    return 0; //will always be a tie... also this legit never happens haha.
}
