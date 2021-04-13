#ifndef ENDOFROUNDDIALOGWINDOW_H
#define ENDOFROUNDDIALOGWINDOW_H

#include <QDialog>
#include "roundresult.h"

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
};

#endif // ENDOFROUNDDIALOGWINDOW_H
