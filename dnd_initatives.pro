#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T13:38:39
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=c++11
TARGET = dnd_initatives
TEMPLATE = app

SOURCES += main.cpp\
        initiativewindow.cpp \
        creature.cpp \
        statuseffect.cpp

HEADERS  += initiativewindow.h \
    creature.h \
    statuseffect.h

#win32:SOURCES += / qxtglobalshortcut_win.cpp

#unix:! macx {
#    INCLUDEPATH += /usr/include/qt/QtGui/5.4.0/QtGui
#    LIBS += -lX11
#    SOURCES += / qxtglobalshortcut_x11.cpp
#}

unix: macx {
    SOURCES += / qxtglobalshortcut_mac.cpp
}

FORMS += \
    initiativewindow.ui

RESOURCES += \
    sounds.qrc
