#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T21:16:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StackAttack
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    presenter.cpp \
    iview.cpp \
    dialog.cpp \
    personaj.cpp \
    game.cpp \
    block.cpp

HEADERS  += mainwindow.h \
    presenter.h \
    iview.h \
    dialog.h \
    personaj.h \
    game.h \
    block.h

FORMS    += mainwindow.ui \
    dialog.ui
