#ifndef ULTIMATETEXASHOLDEM_H
#define ULTIMATETEXASHOLDEM_H

#include <QMainWindow>
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
    void revealFourthCommunityCard();
    void revealFifthCommunityCard();
    void revealAllCommunityCards();
    void revealUserCards();
    void revealDealerCards();
    void hideAllCards();

    //GAME functions
    void dealCards();
    void endRound(bool folded = false);
    QPixmap getPixmapOfCard(Card card);

    RoundResult useRoundResultService(bool playerFolded = false);

};

/*
// Sequence:
// BETTING -> INITALDEAL always, then
//  if Betx3 or Bet4x -> Done
//  if Check (3 card on community shown)
//        if Bet2X -> Done
//        if Check ->
//                5 community cards shown
//                if Fold -> Done
//                if Bet1X -> Done
// Then Done -> Betting
//
// Class represents states that the UI and the game can take on
enum class UltimateTexasHoldem::State {
    BETTING = 0, // where the user can place bets, can set trips, ante and blind
    INITALDEAL = 0, // where the user is dealt the first two cards with both community and dealer cards down.
};
*/
#endif // ULTIMATETEXASHOLDEM_H
