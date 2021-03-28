#include "ultimatetexasholdem.h"
#include "ui_ultimatetexasholdem.h"
#include <algorithm>
#include <QMessageBox>
#include <QDebug>

UltimateTexasHoldem::UltimateTexasHoldem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UltimateTexasHoldem)
{
    ui->setupUi(this);
    setUiConnections();

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

    // Show the cards of the player's cards
    // Tell them what type of hand they have right now
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
}


void UltimateTexasHoldem::on_checkButton_clicked()
{
    setUiToBetting(); // for now
}

void UltimateTexasHoldem::on_bet4XButton_clicked()
{
    setUiToBetting(); // for now
}

void UltimateTexasHoldem::on_bet3XButton_clicked()
{
    setUiToBetting(); // for now
}

void UltimateTexasHoldem::slotEqualAnteBlindBoxes(int arg1)
{
    ui->anteSpinBox->setValue(arg1);
    ui->blindSpinBox->setValue(arg1);
}


void UltimateTexasHoldem::revealOneCommunityCard() {

}
void UltimateTexasHoldem::revealAllCommunityCards() {

}
void UltimateTexasHoldem::revealUserCards() {

}
void UltimateTexasHoldem::revealDealerCards() {

}
