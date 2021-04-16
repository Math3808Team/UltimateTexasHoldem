#include "warningdialog.h"
#include "ui_warningdialog.h"

WarningDialog::WarningDialog(QString message) :
    ui(new Ui::WarningDialog)
{
    ui->setupUi(this);
    ui->warningMessage->setText(message);
}

WarningDialog::~WarningDialog()
{
    delete ui;
}

void WarningDialog::on_pushButton_clicked()
{
    this->close();
}
