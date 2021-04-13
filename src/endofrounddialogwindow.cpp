#include "endofrounddialogwindow.h"
#include "ui_endofrounddialogwindow.h"
#include "roundresult.h"

EndOfRoundDialogWindow::EndOfRoundDialogWindow(RoundResult roundResult) :
    ui(new Ui::EndOfRoundDialogWindow)
{
    ui->setupUi(this);

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
