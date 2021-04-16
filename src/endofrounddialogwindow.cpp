#include "endofrounddialogwindow.h"
#include "ui_endofrounddialogwindow.h"
#include "roundresult.h"

EndOfRoundDialogWindow::EndOfRoundDialogWindow(RoundResult roundResult) :
    ui(new Ui::EndOfRoundDialogWindow)
{
    ui->setupUi(this);
    setPayout(ui->AntePayout,roundResult.antePayout);
    setPayout(ui->BlindPayout,roundResult.blindPayout);
    setPayout(ui->TripsPayout,roundResult.tripsPayout);
    setPayout(ui->PlayPayout,roundResult.playPayout);
    setPayout(ui->TotalResult,roundResult.totalPayout);
    ui->PlayerResult->setText(QStringLiteral("%1 $%2").arg("Player has ").arg(rankToString(roundResult.playerRank)));
    ui->DealerResult->setText(QStringLiteral("%1 $%2").arg("Dealer has ").arg(rankToString(roundResult.dealerRank)));

    switch (roundResult.winner) {
        case 0:
            ui->ResultLabel->setText("You Tie");

            break;
        case 1:
            ui->ResultLabel->setText("YOU WIN!");

            break;
        case 2:
            ui->ResultLabel->setText("You Lose");

            break;
    }
}

EndOfRoundDialogWindow::~EndOfRoundDialogWindow()
{
    delete ui;
}

void EndOfRoundDialogWindow::on_pushButton_clicked()
{
    this->close();
}

void EndOfRoundDialogWindow :: setPayout(QLabel* label, int payout){
    if(payout > 0){
        label->setStyleSheet("color: rgb(7,121,55); font: 14pt 'URW Bookman L';");
        label->setText(QStringLiteral("%1 $%2").arg('+').arg(std::abs(payout)));
    }
    else if(payout < 0){
        //we make the payout red and then put a negative sign on it
        label->setStyleSheet("color: rgb(239,41,41); font: 14pt 'URW Bookman L';");
        label->setText(QStringLiteral("%1 $%2").arg('-').arg(std::abs(payout)));
    }
    else{
        //we make the payout white and put nothing on it
        label->setStyleSheet("color: rgb(255,255,255); font: 14pt 'URW Bookman L';");
        label->setText(QStringLiteral("%1").arg(std::abs(payout)));
    }
}

QString EndOfRoundDialogWindow::rankToString(int rank) {
    switch(rank) {
        case 1:
           return "pair";
        case 2:
           return "two pair";
        case 3:
           return "three of a kind";
        case 4:
           return "straight";
        case 5:
           return "flush";
        case 6:
           return "full house";
        case 7:
           return "four of a kind";
        case 8:
           return "straight flush";
        case 9:
           return "royal flush";
    }
    return "";
}
