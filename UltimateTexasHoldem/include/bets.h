#ifndef BETS_H
#define BETS_H

#include <QObject>

class Bets : QObject {
public:
    unsigned long tripsBet;
    unsigned long blindBet;
    unsigned long playBet;

    void clearBets();
public slots:
    void playBetSlot();
    void blindBetSlot();
    void tripBetSlot();
};

#endif // BETS_H
