#-------------------------------------------------
#
# Project created by QtCreator 2018-12-05T14:28:09
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTcpFile
TEMPLATE = app


SOURCES += main.cpp\
        ServerWight.cpp \
    clientwidget.cpp

HEADERS  += ServerWight.h \
    clientwidget.h

FORMS    += serverwight.ui \
    clientwidget.ui
CONFIG +=C++11
