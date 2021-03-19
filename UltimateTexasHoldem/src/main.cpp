#include "ultimatetexasholdem.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UltimateTexasHoldem w;
    w.show();

    return a.exec();
}
