#include "ultimatetexasholdem.h"
#include "ui_ultimatetexasholdem.h"

#include "handranker.h"
#include <QDebug>

UltimateTexasHoldem::UltimateTexasHoldem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UltimateTexasHoldem)
{
    ui->setupUi(this);

}

UltimateTexasHoldem::~UltimateTexasHoldem()
{
    delete ui;
}
