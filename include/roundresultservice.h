#ifndef ROUNDRESULTSERVICE_H
#define ROUNDRESULTSERVICE_H

#include <QHash>
#include "handranker.h"
#include "roundresult.h"
#include "player.h"
#include "house.h"

class RoundResultService {
public:
    RoundResultService(Player& player, House& house);




    RoundResult determineWinners(const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount, bool = false);
private:
    Player& player;
    House& house;

    static const QHash<int, int> tripsPayoutTable;
    static const QHash<int, float> blindPayoutTable;

    HandRanker handRanker;
    RoundResult determinePayoutPlayerWon(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const;
    RoundResult determinePayoutPlayerLoss(bool houseQualifies, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const;
    RoundResult determinePayoutTie(bool, const int& anteAmount, const int& blindAmount, const int& tripsAmount, const int& playAmount) const;

    int getTripsPayout(const int& tripsAmount, RoundResult& result) const;
    int getBlindPayout(const int& blindAmount, RoundResult& result) const;
};




#endif // ROUNDRESULTSERVICE_H
