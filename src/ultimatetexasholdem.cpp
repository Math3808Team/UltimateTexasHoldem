#include "ultimatetexasholdem.h"
#include "ui_ultimatetexasholdem.h"
#include <algorithm>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <string>
#include <QTime>

#include "roundresultservice.h"
#include "include/handranker.h"
#include "include/endofrounddialogwindow.h"
#include "warningdialog.h"

UltimateTexasHoldem::UltimateTexasHoldem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UltimateTexasHoldem)
{
    ui->setupUi(this);
    setUiConnections();

    hideAllCards();
    setUiToBetting();

    ui->money->setText(QString::number(player.money));
}

UltimateTexasHoldem::~UltimateTexasHoldem()
{
    delete ui;
}

void UltimateTexasHoldem::setUiConnections() {
    connect(ui->anteSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotEqualAnteBlindBoxes(int)));
    connect(ui->blindSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotEqualAnteBlindBoxes(int)));
}

void createEndOfRoundDialog(RoundResult roundResult) {
    EndOfRoundDialogWindow dialog(roundResult);
    dialog.setModal(true); //dont allow context switching
    dialog.exec();
}

void createWarningDialog(QString string) {
    //EndOfRoundDialogWindow dialog(roundResult);
    WarningDialog dialog(string);
    dialog.setModal(true); //dont allow context switching
    dialog.exec();
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
        createWarningDialog("You do not have enough money!");
        return;
    }
    else if (totalBets + ui->anteSpinBox->value() > player.money) {
        createWarningDialog("You do not have enough to make a 1x Bet with the current bet setup!");
        return;
    }

    if (ui->tripSpinBox->value() > 0 && (ui->anteSpinBox->value()) <= 0) {
        createWarningDialog("You can not only place the trips bet.");
        return;
    }

    if (totalBets <= 1) {
        createWarningDialog("You must bet at least 1 dollar.");
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
        revealLastTwoCommunityCard();
        ++numOfChecks;
        break;
    case 2:
    {
        endRound();
        break;
    }

    default:
        qDebug() << "Check button pressed with more than three checks\n";
        break;
    }
}

void UltimateTexasHoldem::on_bet4XButton_clicked()
{
    betPlayAmount(ui->anteSpinBox->value() * 4);
    revealAllCommunityCards();
    endRound();
}

void UltimateTexasHoldem::on_bet3XButton_clicked()
{
    betPlayAmount(ui->anteSpinBox->value() * 3);
    revealAllCommunityCards();
    endRound();
}

void UltimateTexasHoldem::on_bet2XButton_clicked()
{
    betPlayAmount(ui->anteSpinBox->value() * 2);
    revealLastTwoCommunityCard();
    endRound();
}

void UltimateTexasHoldem::on_bet1XButton_clicked()
{
    betPlayAmount(ui->anteSpinBox->value() * 1);
    endRound();
}

void UltimateTexasHoldem::on_foldButton_clicked()
{
    endRound(true);
}


void UltimateTexasHoldem::slotEqualAnteBlindBoxes(int arg1)
{
    ui->anteSpinBox->setValue(arg1);
    ui->blindSpinBox->setValue(arg1);
}

void UltimateTexasHoldem::on_pushButton_clicked()
{
    player.money = 10000;
    ui->money->setText("10000");
}


//END OF SLOTS; START OF FUNCTIONS

void UltimateTexasHoldem::betPlayAmount(unsigned int playBetAmount) {
    if (playBetAmount > player.money) {
        createWarningDialog("You do not have enough money to make this bet!");
        return;
    }

    player.money -= playBetAmount;
    ui->playBet->setText(QString::number(playBetAmount));
    ui->money->setText(QString::number(player.money));
}

void UltimateTexasHoldem::revealThreeCommunityCard() {
    ui->CommunityCard1->setPixmap(getPixmapOfCard(player.hand.getCards()[2]));
    ui->CommunityCard2->setPixmap(getPixmapOfCard(player.hand.getCards()[3]));
    ui->CommunityCard3->setPixmap(getPixmapOfCard(player.hand.getCards()[4]));
}

void UltimateTexasHoldem::revealLastTwoCommunityCard() {
    ui->CommunityCard4->setPixmap(getPixmapOfCard(player.hand.getCards()[5]));
    ui->CommunityCard5->setPixmap(getPixmapOfCard(player.hand.getCards()[6]));
}

void UltimateTexasHoldem::revealAllCommunityCards() {
    revealThreeCommunityCard();
    revealLastTwoCommunityCard();

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

void UltimateTexasHoldem::endRound(bool folded) {
    revealDealerCards();
    RoundResult roundResult = useRoundResultService(folded);
    createEndOfRoundDialog(roundResult);

    //update the ui with the player's calculated money
    ui->money->setText(QString::number(player.money));

    deck = Deck(); //reset the contents of the deck
    setUiToBetting();
}


QPixmap UltimateTexasHoldem::getPixmapOfCard(Card card) {
    QPixmap pixmap(QStringLiteral(":/cards/resources/%1%2.png").arg(card.value).arg(card.suit));
    return pixmap.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio);
}

