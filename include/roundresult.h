#ifndef ROUNDRESULT_H
#define ROUNDRESULT_H

#include <QString>

struct RoundResult {
    int winner;
    int antePayout;
    int blindPayout;
    int playPayout;
    int tripsPayout;
    int totalPayout;
    operator QString() const;

};

RoundResult::operator QString() const {
    QString ret;
    ret.append("winner: " + QString::number(winner) + "\n");
    ret.append("antePayout: " + QString::number(antePayout) + "\n");
    ret.append("blindPayout: " + QString::number(blindPayout) + "\n");
    ret.append("playPayout: " + QString::number(playPayout) + "\n");
    ret.append("tripsPayout: " + QString::number(tripsPayout) + "\n");
    ret.append("totalPayout: " + QString::number(totalPayout) + "\n");
    return ret;
}

#endif // ROUNDRESULT_H
