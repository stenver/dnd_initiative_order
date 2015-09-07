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

contains(QMAKE_LFLAGS, "-Wl,--no-undefined"):LIBS += $${QMAKE_LIBS_X11}

!qws:!symbian {
    HEADERS  += qxtglobalshortcut.h
    HEADERS  += qxtglobalshortcut_p.h
    HEADERS  += qxtglobal.h
    SOURCES  += qxtglobalshortcut.cpp

    macx {
        SOURCES += qxtglobalshortcut_mac.cpp
        LIBS += -framework Carbon
    }
    unix:!macx {
        INCLUDEPATH += /usr/include/qt/QtGui/5.4.0/QtGui
        LIBS += -lX11
        SOURCES += x11/qxtglobalshortcut_x11.cpp
    }
    win32 {
        LIBS += -luser32
        SOURCES += win/qxtglobalshortcut_win.cpp
    }
}

FORMS += \
    initiativewindow.ui

RESOURCES += \
    sounds.qrc
