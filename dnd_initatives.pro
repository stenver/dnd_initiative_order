#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T13:38:39
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dnd_initatives
TEMPLATE = app

SOURCES += main.cpp\
        initiativewindow.cpp \
    creature.cpp \
    statuseffect.cpp

HEADERS  += initiativewindow.h \
    creature.h \
    statuseffect.h

FORMS += \
    initiativewindow.ui

RESOURCES += \
    sounds.qrc
