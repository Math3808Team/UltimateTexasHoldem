#include "verifiers/trickverifier.h"


QHash<int,int> TrickVerifier::getTableOfValues(Hand &hand) {
    hand.getCards();
    return QHash<int, int>();
}
QHash<int,int> TrickVerifier::getTableOfSuits(Hand &hand) {
    return QHash<int, int>();
}
