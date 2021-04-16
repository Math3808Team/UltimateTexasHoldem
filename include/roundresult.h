#ifndef ROUNDRESULT_H
#define ROUNDRESULT_H

#include <QString>

struct RoundResult {
    int winner = -1;
    int antePayout = 0;
    int blindPayout = 0;
    int playPayout = 0;
    int tripsPayout = 0;
    int totalPayout = 0;
    int playerRank = 0;
    int dealerRank = 0;
    inline operator QString() const;
    constexpr inline void setTotal();

};

inline RoundResult::operator QString() const {
    QString ret;
    ret.append("winner: " + QString::number(winner) + "\n");
    ret.append("antePayout: " + QString::number(antePayout) + "\n");
    ret.append("blindPayout: " + QString::number(blindPayout) + "\n");
    ret.append("playPayout: " + QString::number(playPayout) + "\n");
    ret.append("tripsPayout: " + QString::number(tripsPayout) + "\n");
    ret.append("totalPayout: " + QString::number(totalPayout) + "\n");
    return ret;
}

constexpr inline void RoundResult::setTotal() {
    totalPayout = antePayout + blindPayout + playPayout + tripsPayout;
}

#endif // ROUNDRESULT_H
