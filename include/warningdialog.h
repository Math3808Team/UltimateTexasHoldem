#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QDialog>

namespace Ui {
class WarningDialog;
}

class WarningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WarningDialog(QString message ="An error has occured");
    ~WarningDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WarningDialog *ui;
};

#endif // WARNINGDIALOG_H
