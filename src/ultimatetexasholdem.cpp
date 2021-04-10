#include "ultimatetexasholdem.h"
#include "ui_ultimatetexasholdem.h"
#include <algorithm>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <string>

#include "handranker.h"

UltimateTexasHoldem::UltimateTexasHoldem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UltimateTexasHoldem)
{
    ui->setupUi(this);
    setUiConnections();

    hideAllCards();
    setUiToBetting();

    ui->money->setText(QString::number(player.money));

    Player player;
    player.hand.addCard(Card('c', 7));
    player.hand.addCard(Card('c', 10));
    House house;
    house.hand.addCard(Card('c', 14));
    house.hand.addCard(Card('c', 10));

    auto addSame = [](Hand& hand) {
      hand.addCard(Card('d', 8));
      hand.addCard(Card('c', 9));
      hand.addCard(Card('h', 11));
      hand.addCard(Card('c', 12));
      hand.addCard(Card('k', 13));
    };
    addSame(player.hand);
    addSame(house.hand);

    HandRanker ranker;
    ranker.rankHand(player.hand);
    ranker.rankHand(house.hand);
    qInfo() << player.hand.rank << " " << house.hand.rank;
    int p = ranker.breakTie(player, house);
    qInfo() << p;
}

UltimateTexasHoldem::~UltimateTexasHoldem()
{
    delete ui;
}

void UltimateTexasHoldem::setUiConnections() {
    connect(ui->anteSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotEqualAnteBlindBoxes(int)));
    connect(ui->blindSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotEqualAnteBlindBoxes(int)));

}

/**
 * @brief UltimateTexasHoldem::setUiToBetting
 * Makes the UI go to the betting stage where all cards are down
 * And the user can place bets
 * This is a hard reset of the UI
 */
void UltimateTexasHoldem::setUiToBetting() {
    // dealing buttons
    ui->dealButton->setEnabled(true);
    ui->bet1XButton->setEnabled(false);
    ui->bet2XButton->setEnabled(false);
    ui->bet3XButton->setEnabled(false);
    ui->bet4XButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->foldButton->setEnabled(false);

    // betting buttons
    ui->anteSpinBox->setEnabled(true);
    ui->blindSpinBox->setEnabled(true);
    ui->tripSpinBox->setEnabled(true);

    // reset cards here to all back cards

    numOfChecks = 0;
}

/**
 * @brief UltimateTexasHoldem::setUiToInitalDeal
 * Makes the UI go to the first stage of dealing, where all cards are down
 * But the user can now check and perform checking or betting xn amonts
 * This is a hard reset of the UI
 */
void UltimateTexasHoldem::setUiToInitalDeal() {
    ui->dealButton->setEnabled(false);
    ui->bet1XButton->setEnabled(false);
    ui->bet2XButton->setEnabled(false);
    ui->bet3XButton->setEnabled(true);
    ui->bet4XButton->setEnabled(true);
    ui->checkButton->setEnabled(true);
    ui->foldButton->setEnabled(false);

    ui->anteSpinBox->setEnabled(false);
    ui->blindSpinBox->setEnabled(false);
    ui->tripSpinBox->setEnabled(false);
}

void UltimateTexasHoldem::on_dealButton_clicked() {
    unsigned long long totalBets = ui->anteSpinBox->value() + ui->blindSpinBox->value() + ui->tripSpinBox->value();
    // may not be a good idea to have the game logic in here.
    if (totalBets > player.money) {
        QMessageBox msgBox;
        msgBox.setText("You do not have enough money!");
        msgBox.exec();
        return;
    }

    player.money -= totalBets;
    ui->money->setText(QString::number(player.money));
    setUiToInitalDeal();
    hideAllCards();
    dealCards();
    revealUserCards();
}


void UltimateTexasHoldem::on_checkButton_clicked()
{
    // At this point: Atleast the user cards are displayed.
    switch(numOfChecks) {
    case 0:
        ui->bet4XButton->setEnabled(false);
        ui->bet3XButton->setEnabled(false);
        ui->bet2XButton->setEnabled(true);
        revealThreeCommunityCard();
        ++numOfChecks;
        break;
    case 1:
        ui->bet2XButton->setEnabled(false);
        ui->bet1XButton->setEnabled(true);
        ui->foldButton->setEnabled(true);
        revealFourthCommunityCard();
        revealFifthCommunityCard();
        ++numOfChecks;
        break;
    case 2:
        revealDealerCards();
        determineWinner();
        //Create popup window that shows payouts and determine payout based on player's hand rank and who won.
        //Also update a label under player and house cards saying what hand they have
        setUiToBetting();
        deck = Deck(); //reset the containts of the deck (shuffle)
        break;

    default:
        qDebug() << "Check button pressed with more than three checks\n";
        break;
    }
}

void UltimateTexasHoldem::on_bet4XButton_clicked()
{
    revealAllCommunityCards();
    revealDealerCards();
    setUiToBetting(); // for now
}

void UltimateTexasHoldem::on_bet3XButton_clicked()
{
    revealAllCommunityCards();
    revealDealerCards();
    setUiToBetting(); // for now
}

void UltimateTexasHoldem::slotEqualAnteBlindBoxes(int arg1)
{
    ui->anteSpinBox->setValue(arg1);
    ui->blindSpinBox->setValue(arg1);
}

//END OF SLOTS; START OF FUNCTIONS

void UltimateTexasHoldem::revealThreeCommunityCard() {
    ui->CommunityCard1->setPixmap(getPixmapOfCard(player.hand.getCards()[2]));
    ui->CommunityCard2->setPixmap(getPixmapOfCard(player.hand.getCards()[3]));
    ui->CommunityCard3->setPixmap(getPixmapOfCard(player.hand.getCards()[4]));
}

void UltimateTexasHoldem::revealFourthCommunityCard() {
    ui->CommunityCard4->setPixmap(getPixmapOfCard(player.hand.getCards()[5]));
}

void UltimateTexasHoldem::revealFifthCommunityCard() {
    ui->CommunityCard5->setPixmap(getPixmapOfCard(player.hand.getCards()[6]));
}

void UltimateTexasHoldem::revealAllCommunityCards() {
    revealThreeCommunityCard();
    revealFourthCommunityCard();
    revealFifthCommunityCard();

}
void UltimateTexasHoldem::revealUserCards() {
    ui->PlayerCard1->setPixmap(getPixmapOfCard(player.hand.getCards()[0]));
    ui->PlayerCard2->setPixmap(getPixmapOfCard(player.hand.getCards()[1]));
}
void UltimateTexasHoldem::revealDealerCards() {
    ui->DealerCard1->setPixmap(getPixmapOfCard(house.hand.getCards()[0]));
    ui->DealerCard2->setPixmap(getPixmapOfCard(house.hand.getCards()[1]));
}
void UltimateTexasHoldem::hideAllCards() {
    QPixmap pixmap(":/cards/resources/backcard.png");

    pixmap = pixmap.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio);

    ui->CommunityCard1->setPixmap(pixmap);
    ui->CommunityCard2->setPixmap(pixmap);
    ui->CommunityCard3->setPixmap(pixmap);
    ui->CommunityCard4->setPixmap(pixmap);
    ui->CommunityCard5->setPixmap(pixmap);
    ui->DealerCard1->setPixmap(pixmap);
    ui->DealerCard2->setPixmap(pixmap);
    ui->PlayerCard1->setPixmap(pixmap);
    ui->PlayerCard2->setPixmap(pixmap);
}

void UltimateTexasHoldem::dealCards() {

    player.hand.clear();
    house.hand.clear();
    player.hand.rank = 0;
    house.hand.rank = 0;

    //Add players's 2 unique cards
    player.hand.addCard(deck.getCard());
    player.hand.addCard(deck.getCard());

    //Add house's 2 unique cards
    house.hand.addCard(deck.getCard());
    house.hand.addCard(deck.getCard());

    //Add community cards
    for (int i = 0; i < 5; i++) {
        Card communityCard = deck.getCard();

        player.hand.addCard(communityCard);
        house.hand.addCard(communityCard);
    }
}

/**
 * @brief UltimateTexasHoldem::determineWinner determines the winner of the round.
 */
void UltimateTexasHoldem::determineWinner() {
    handRanker.rankHand(player.hand);
    handRanker.rankHand(house.hand);


    if (player.hand.rank > house.hand.rank) {
        qInfo() << "player won with a " + handRanker.rankToString(player.hand.rank) + ".";

    } else if (player.hand.rank < house.hand.rank) {
        qInfo() << "house won with a " + handRanker.rankToString(house.hand.rank) + ".";

    } else {
        qInfo() << "tie being tested: ";

        if (player.hand.rank == 0 && house.hand.rank == 0) {
            //special case where no one has anything
            qInfo() << "tie with nothing.";
            return; //dont do any tie breaking
        }


       int tieResult = handRanker.breakTie(player,house);
       if (tieResult == 1)
           qInfo() << "player won with a " + handRanker.rankToString(player.hand.rank) + ".";
       else if (tieResult == 2)
           qInfo() << "house won with a " + handRanker.rankToString(house.hand.rank) + ".";
       else
           qInfo() << "tie with a " + handRanker.rankToString(player.hand.rank) + ".";
    }

}

QPixmap UltimateTexasHoldem::getPixmapOfCard(Card card) {
    QPixmap pixmap(QStringLiteral(":/cards/resources/%1%2.png").arg(card.value).arg(card.suit));
    return pixmap.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio);
}
