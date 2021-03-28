#include "ultimatetexasholdem.h"
#include "ui_ultimatetexasholdem.h"
#include <algorithm>
#include <QMessageBox>
#include <QDebug>

#include "handranker.h"
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
    connect(ui->anteSpinBox, &QSpinBox::valueChanged, this, &UltimateTexasHoldem::on_anteorblindSpinBox_valueChanged);
    connect(ui->blindSpinBox, &QSpinBox::valueChanged, this, &UltimateTexasHoldem::on_anteorblindSpinBox_valueChanged);
}

void UltimateTexasHoldem::setUiToBetting() {
    state = State::BETTING;
    // dealing buttons
    ui->dealButton->setEnabled(true);
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

void UltimateTexasHoldem::setUiToInitalDeal() {
    state = State::INITALDEAL;

    ui->dealButton->setEnabled(false);
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

void UltimateTexasHoldem::on_anteorblindSpinBox_valueChanged(int arg1)
{
    ui->anteSpinBox->setValue(arg1);
    ui->blindSpinBox->setValue(arg1);
}
