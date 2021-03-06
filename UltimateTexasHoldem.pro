#-------------------------------------------------
#
# Project created by QtCreator 2021-03-11T15:49:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UltimateTexasHoldem
TEMPLATE = app

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/bets.cpp \
        src/card.cpp \
        src/deck.cpp \
        src/hand.cpp \
        src/main.cpp \
        src/handranker.cpp \
        src/roundresultservice.cpp \
        src/ultimatetexasholdem.cpp \
        src/verifiers/pairverifier.cpp \
        src/verifiers/twopairverifier.cpp \
        src/verifiers/threeofakindverifier.cpp \
        src/verifiers/flushverifier.cpp \
        src/verifiers/fourofakindverifier.cpp \
        src/verifiers/fullhouseverifier.cpp \
        src/verifiers/royalflushverifier.cpp \
        src/verifiers/straightverifier.cpp \
        src/verifiers/straightflushverifier.cpp \
        src/verifiers/trickverifier.cpp \
        src/endofrounddialogwindow.cpp \
        src/warningdialog.cpp

HEADERS += \
        include/bets.h \
        include/card.h \
        include/deck.h \
        include/hand.h \
        include/house.h \
        include/player.h \
        include/roundresultservice.h \
        include/ultimatetexasholdem.h \
        include/verifiers/trickverifier.h \
        include/verifiers/pairverifier.h \
        include/verifiers/twopairverifier.h \
        include/verifiers/threeofakindverifier.h \
        include/verifiers/straightverifier.h \
        include/verifiers/flushverifier.h \
        include/verifiers/fullhouseverifier.h \
        include/verifiers/fourofakindverifier.h \
        include/verifiers/straightflushverifier.h \
        include/verifiers/royalflushverifier.h \
        include/handranker.h \
        include/endofrounddialogwindow.h \
        include/roundresult.h \
        include/warningdialog.h

FORMS += \
        forms/ultimatetexasholdem.ui \
        forms/endofrounddialogwindow.ui \
        forms/warningdialog.ui

INCLUDEPATH += include/

RESOURCES += \
    resources.qrc

RC_ICONS = resources/UltimateTexasHoldem-icon.ico
