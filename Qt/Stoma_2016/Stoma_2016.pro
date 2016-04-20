#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T16:08:03
#
#-------------------------------------------------

QT       += core gui sql
#QMAKE_LFLAGS += -static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Stoma_2016
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogsearchpacient.cpp \
    dialogadddateview.cpp \
    mysortfilterproxymodel.cpp \
    myqlabel.cpp \
    myqtextedit.cpp

HEADERS  += mainwindow.h \
    dialogsearchpacient.h \
    dialogadddateview.h \
    mysortfilterproxymodel.h \
    myqlabel.h \
    myqtextedit.h

FORMS    += mainwindow.ui \
    dialogsearchpacient.ui \
    dialogadddateview.ui

RESOURCES += \
    imgs.qrc
