#ifndef ULTIMATETEXASHOLDEM_H
#define ULTIMATETEXASHOLDEM_H

#include <QMainWindow>
#include <QDebug>
#include <QEvent>
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

    class FilterMouseEvents;
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

private:
    QPixmap backcard;
    const int CARD_WIDTH  = 100;
    const int CARD_HEIGHT = 140;

    Deck deck;
    Player player;
    House house;
    HandRanker handRanker;
    int numOfChecks = 0;
    Ui::UltimateTexasHoldem *ui;
    FilterMouseEvents* filterMouseEvents;

    void setUiConnections();

    // UI functions
    void revealThreeCommunityCard();
    void revealFourthCommunityCard();
    void revealFifthCommunityCard();
    void revealAllCommunityCards();
    void revealUserCards();
    void revealDealerCards();
    void hideAllCards();

    //GAME functions
    void dealCards();
    QPixmap getPixmapOfCard(Card card);

    RoundResult useRoundResultService(bool playerFolded = false);
};

class UltimateTexasHoldem::FilterMouseEvents : public QObject {
    Q_OBJECT
public:
    FilterMouseEvents(QObject* obj) : QObject(obj) {}
    ~FilterMouseEvents() {}
protected:
    virtual bool eventFilter(QObject*, QEvent* event) override {
        if (event->type() == QEvent::MouseButtonPress) return true; // ignore all mouse events
        return false;
    }
};

#endif // ULTIMATETEXASHOLDEM_H
