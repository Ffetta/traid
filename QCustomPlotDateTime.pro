#-------------------------------------------------
#
# Project created by QtCreator 2015-12-27T17:19:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT +=  widgets printsupport

TARGET = QCustomPlotDateTime
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    downloader.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    downloader.h

FORMS    += mainwindow.ui
