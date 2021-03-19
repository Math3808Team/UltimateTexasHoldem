#ifndef ULTIMATETEXASHOLDEM_H
#define ULTIMATETEXASHOLDEM_H

#include <QMainWindow>

namespace Ui {
class UltimateTexasHoldem;
}

class UltimateTexasHoldem : public QMainWindow
{
    Q_OBJECT

public:
    explicit UltimateTexasHoldem(QWidget *parent = 0);
    ~UltimateTexasHoldem();

private:
    Ui::UltimateTexasHoldem *ui;
};

#endif // ULTIMATETEXASHOLDEM_H
