#ifndef ENDOFROUNDDIALOGWINDOW_H
#define ENDOFROUNDDIALOGWINDOW_H

#include <QDialog>
#include "roundresult.h"
#include <QLabel>

namespace Ui {
class EndOfRoundDialogWindow;
}

class EndOfRoundDialogWindow : public QDialog
{
    Q_OBJECT

public:
    EndOfRoundDialogWindow(RoundResult roundResult);
    ~EndOfRoundDialogWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EndOfRoundDialogWindow *ui;
    void setPayout(QLabel* label, int payout);
    QString rankToString(int rank);
};

#endif // ENDOFROUNDDIALOGWINDOW_H
