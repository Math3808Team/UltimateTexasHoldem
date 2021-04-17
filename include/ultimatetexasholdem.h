#ifndef ULTIMATETEXASHOLDEM_H
#define ULTIMATETEXASHOLDEM_H

#include <QMainWindow>
#include <QObject>
#include "player.h"
#include "house.h"
#include "deck.h"
#include "handranker.h"
#include "roundresult.h"

namespace Ui {
class UltimateTexasHoldem;
}

class UltimateTexasHoldem : public QMainWindow
{
    Q_OBJECT

public:
    explicit UltimateTexasHoldem(QWidget *parent = 0);
    ~UltimateTexasHoldem();


    void setUiToBetting();
    void setUiToInitalDeal();
private slots:
    void on_dealButton_clicked();
    void on_checkButton_clicked();
    void on_bet4XButton_clicked();
    void on_bet3XButton_clicked();
    void on_bet2XButton_clicked();
    void slotEqualAnteBlindBoxes(int arg1);



    void on_foldButton_clicked();

    void on_bet1XButton_clicked();

    void on_pushButton_clicked();

private:

    const int CARD_WIDTH  = 100;
    const int CARD_HEIGHT = 140;

    Deck deck;
    Player player;
    House house;
    HandRanker handRanker;
    int numOfChecks = 0;
    Ui::UltimateTexasHoldem *ui;

    void setUiConnections();

    // UI functions
    void revealThreeCommunityCard();
    void revealLastTwoCommunityCard();
    void revealAllCommunityCards();
    void revealUserCards();
    void revealDealerCards();
    void hideAllCards();
    void betPlayAmount(unsigned int playBetAmount);

    //GAME functions
    void dealCards();
    void endRound(bool folded = false);
    QPixmap getPixmapOfCard(Card card);

    RoundResult useRoundResultService(bool playerFolded = false);

};
#endif // ULTIMATETEXASHOLDEM_H
