#include "ultimatetexasholdem.h"
#include "ui_ultimatetexasholdem.h"
#include <algorithm>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <string>
#include <QTime>
#include <stdexcept>

#include "roundresultservice.h"
#include "include/handranker.h"
#include "include/endofrounddialogwindow.h"

UltimateTexasHoldem::UltimateTexasHoldem(QWidget *parent) :
    QMainWindow(parent),
    backcard((":/cards/resources/backcard.png")),
    ui(new Ui::UltimateTexasHoldem)
{
    filterMouseEvents = new FilterMouseEvents(this);
    backcard = backcard.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio);
    ui->setupUi(this);
    setUiConnections();

    hideAllCards();
    setUiToBetting();

    ui->money->setText(QString::number(player.money));
/*
    Player player;
    player.hand.addCard(Card('c', 10));
    player.hand.addCard(Card('c', 10));
    House house;
    house.hand.addCard(Card('c', 14));
    house.hand.addCard(Card('c', 10));

    auto addSame = [](Hand& hand) {
      hand.addCard(Card('d', 8));
      hand.addCard(Card('c', 8));
      hand.addCard(Card('h', 11));
      hand.addCard(Card('c', 12));
      hand.addCard(Card('k', 12));
    };
    addSame(player.hand);
    addSame(house.hand);

    HandRanker ranker;
    ranker.rankHand(player.hand);
    ranker.rankHand(house.hand);
    qInfo() << player.hand.rank << " " << house.hand.rank;
    int p = ranker.breakTie(player, house);
    qInfo() << p;*/
}

UltimateTexasHoldem::~UltimateTexasHoldem()
{
    delete ui;
}

void createEndOfRoundDialog(RoundResult roundResult) {
    EndOfRoundDialogWindow dialog(roundResult);
    dialog.setModal(true); //dont allow context switching
    dialog.exec();
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

    ui->playBet->setText("");
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
    else if (totalBets + ui->anteSpinBox->value() > player.money) {
        QMessageBox msgBox;
        msgBox.setText("You do not have enough to make a 1x Bet with the current bet setup!");
        msgBox.exec();
        return;
    }

    if (ui->tripSpinBox->value() > 0 && (ui->anteSpinBox->value()) <= 0) {
        qInfo() << "You can not only place the trips bet.";
        return;
    }

    if (totalBets <= 1) {
        qInfo() << "You must bet atleast 1 dollar.";
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
    {
        revealDealerCards();

        RoundResult roundResult = useRoundResultService();
        //determinePayout(roundResult);
        //Create popup window that shows payouts and determine payout based on player's hand rank and who won.
        //Also update a label under player and house cards saying what hand they have
        createEndOfRoundDialog(roundResult);
        setUiToBetting();
        deck = Deck(); //reset the contents of the deck
        break;
    }

    default:
        qDebug() << "Check button pressed with more than three checks\n";
        break;
    }
}

void UltimateTexasHoldem::on_bet4XButton_clicked()
{
    unsigned long playBetRequired = ui->anteSpinBox->value() * 4;
    if (playBetRequired > player.money) {
        qInfo() << "You do not have enough money to make this 4X bet!";
        return;
    }
    player.money -= playBetRequired;
    ui->playBet->setText(QString::number(ui->anteSpinBox->value() * 4));
    ui->money->setText(QString::number(player.money));
    revealAllCommunityCards();
    revealDealerCards();

    useRoundResultService();

    setUiToBetting(); // for now
}

void UltimateTexasHoldem::on_bet3XButton_clicked()
{
    unsigned long playBetRequired = ui->anteSpinBox->value() * 3;
    if (playBetRequired > player.money) {
        qInfo() << "You do not have enough money to make this 3X bet!";
        return;
    }
    player.money -= playBetRequired;
    ui->playBet->setText(QString::number(ui->anteSpinBox->value() * 3));
    ui->money->setText(QString::number(player.money));
    revealAllCommunityCards();
    revealDealerCards();

    useRoundResultService();

    setUiToBetting(); // for now
}

void UltimateTexasHoldem::on_bet2XButton_clicked()
{
    unsigned long playBetRequired = ui->anteSpinBox->value() * 2;
    if (playBetRequired > player.money) {
        qInfo() << "You do not have enough money to make this 2X bet!";
        return;
    }
    player.money -= playBetRequired;
    ui->playBet->setText(QString::number(ui->anteSpinBox->value() * 2));
    ui->money->setText(QString::number(player.money));
    revealAllCommunityCards();
    revealDealerCards();

    useRoundResultService();

    setUiToBetting(); // for now
}

void UltimateTexasHoldem::on_foldButton_clicked()
{
    revealAllCommunityCards();
    revealDealerCards();

    useRoundResultService(true);

    setUiToBetting(); // for now
}


void UltimateTexasHoldem::slotEqualAnteBlindBoxes(int arg1)
{
    ui->anteSpinBox->setValue(arg1);
    ui->blindSpinBox->setValue(arg1);
}

void sleep(int msc = 1000) {
    QTime dieTime= QTime::currentTime().addMSecs(msc);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents, 100);
}

//END OF SLOTS; START OF FUNCTIONS

void UltimateTexasHoldem::revealThreeCommunityCard() {
    const std::vector<Card>& playerCards = player.hand.getCards();

    if (ui->CommunityCard1->pixmap().cacheKey() != backcard.cacheKey()) return;

    installEventFilter(filterMouseEvents);

    ui->CommunityCard1->setPixmap(getPixmapOfCard(playerCards[2]));
    sleep();
    ui->CommunityCard2->setPixmap(getPixmapOfCard(playerCards[3]));
    sleep();
    ui->CommunityCard3->setPixmap(getPixmapOfCard(playerCards[4]));

    removeEventFilter(filterMouseEvents);
}

void UltimateTexasHoldem::revealFourthCommunityCard() {
    if (ui->CommunityCard4->pixmap().cacheKey() != backcard.cacheKey()) return;
    installEventFilter(filterMouseEvents);

    sleep();
    ui->CommunityCard4->setPixmap(getPixmapOfCard(player.hand.getCards()[5]));

    removeEventFilter(filterMouseEvents);
}

void UltimateTexasHoldem::revealFifthCommunityCard() {
    if (ui->CommunityCard5->pixmap().cacheKey() != backcard.cacheKey()) return;

    installEventFilter(filterMouseEvents);

    sleep();
    ui->CommunityCard5->setPixmap(getPixmapOfCard(player.hand.getCards()[6]));

    removeEventFilter(filterMouseEvents);
}

void UltimateTexasHoldem::revealAllCommunityCards() {
    installEventFilter(filterMouseEvents);
    revealThreeCommunityCard();
    revealFourthCommunityCard();
    revealFifthCommunityCard();
    removeEventFilter(filterMouseEvents);

}
void UltimateTexasHoldem::revealUserCards() {
    installEventFilter(filterMouseEvents);
    ui->PlayerCard1->setPixmap(getPixmapOfCard(player.hand.getCards()[0]));
    sleep();
    ui->PlayerCard2->setPixmap(getPixmapOfCard(player.hand.getCards()[1]));
    removeEventFilter(filterMouseEvents);
}
void UltimateTexasHoldem::revealDealerCards() {
    installEventFilter(filterMouseEvents);
    sleep();
    ui->DealerCard1->setPixmap(getPixmapOfCard(house.hand.getCards()[0]));
    sleep();
    ui->DealerCard2->setPixmap(getPixmapOfCard(house.hand.getCards()[1]));
    sleep();
    removeEventFilter(filterMouseEvents);
}
void UltimateTexasHoldem::hideAllCards() {
    ui->CommunityCard1->setPixmap(backcard);
    ui->CommunityCard2->setPixmap(backcard);
    ui->CommunityCard3->setPixmap(backcard);
    ui->CommunityCard4->setPixmap(backcard);
    ui->CommunityCard5->setPixmap(backcard);
    ui->DealerCard1->setPixmap(backcard);
    ui->DealerCard2->setPixmap(backcard);
    ui->PlayerCard1->setPixmap(backcard);
    ui->PlayerCard2->setPixmap(backcard);
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

RoundResult UltimateTexasHoldem::useRoundResultService(bool playFolded) {
    static RoundResultService resultService(player, house); // variable only exists(staticly) in this scope
    bool playBetExists = false;
    int playAmount = ui->playBet->text().toInt(&playBetExists);
    if (!playBetExists && ui->playBet->text() == "")
        playAmount = 0;
    else if (!playBetExists) {
        qDebug() << "No play bet? play bet should be set...";
        playAmount = 0;
    }
    RoundResult roundResult = resultService.determineWinners(ui->anteSpinBox->value(), ui->blindSpinBox->value(), ui->tripSpinBox->value(), playAmount, playFolded);
    roundResult.playerRank = player.hand.rank;
    roundResult.dealerRank = house.hand.rank;
    return roundResult;
}


QPixmap UltimateTexasHoldem::getPixmapOfCard(Card card) {
    QPixmap pixmap(QStringLiteral(":/cards/resources/%1%2.png").arg(card.value).arg(card.suit));
    return pixmap.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio);
}



