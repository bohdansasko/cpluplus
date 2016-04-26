#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T02:52:30
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleCity
TEMPLATE = app


SOURCES += main.cpp\
        battlecityview.cpp \
    battlecitymap.cpp \
    tank.cpp \
    tankforplayer.cpp \
    bullet.cpp \
    parsing.cpp \
    redwall.cpp \
    sprite.cpp \
    tankbot.cpp \
    algorithmli.cpp \
    udpclient.cpp \
    mainmenu.cpp \
    bonus.cpp

HEADERS  += battlecityview.h \
    battlecitymap.h \
    tank.h \
    tankforplayer.h \
    bullet.h \
    parsing.h \
    constants.h \
    redwall.h \
    sprite.h \
    tankbot.h \
    algorithmli.h \
    udpclient.h \
    mainmenu.h \
    bonus.h

RESOURCES += \
    tanks.qrc \
    walls.qrc \
    map.qrc \
    explosion.qrc \
    imgs.qrc \
    imgsforgameover.qrc \
    fonts.qrc \
    bonuses.qrc \
    sounds.qrc
