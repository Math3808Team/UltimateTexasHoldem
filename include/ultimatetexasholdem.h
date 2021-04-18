#ifndef ULTIMATETEXASHOLDEM_H
#define ULTIMATETEXASHOLDEM_H

#include <QMainWindow>
#include <QObject>
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
    void on_bet1XButton_clicked();
    void on_foldButton_clicked();
    void on_ResetMoney_clicked();
    void slotEqualAnteBlindBoxes(int arg1);

private:
    // Data members
    Deck deck;
    Player player;
    House house;
    HandRanker handRanker;
    int numOfChecks = 0;
    Ui::UltimateTexasHoldem *ui;
    FilterMouseEvents* filterMouseEvents;

    // Card variables
    QPixmap backcard;
    static constexpr int CARD_WIDTH  = 100;
    static constexpr int CARD_HEIGHT = 140;

    // UI functions
    void setUiConnections();
    void revealThreeCommunityCard();
    void revealLastTwoCommunityCard();
    void revealAllCommunityCards();
    void revealUserCards();
    void revealDealerCards();
    void hideAllCards();
    bool betPlayAmount(unsigned int playBetAmount);

    //GAME functions
    void dealCards();
    void endRound(bool folded = false);
    QPixmap getPixmapOfCard(Card card);
    RoundResult useRoundResultService(bool playerFolded = false);
};

/**
 * @brief The UltimateTexasHoldem::FilterMouseEvents class
 *  Class is a filter event object that filters all mouse events to be discarded.
 *  The object is used during a installEventFilter() and removeEventFilter() calls to allow the filter to operate
 */
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
