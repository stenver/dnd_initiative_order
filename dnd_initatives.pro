#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T13:38:39
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dnd_initatives
TEMPLATE = app


#CONFIG  += qxt

#QXT     += core gui

SOURCES += main.cpp\
        initiativewindow.cpp \
    creature.cpp \
    statuseffect.cpp

HEADERS  += initiativewindow.h \
    creature.h \
    statuseffect.h

FORMS += \
    initiativewindow.ui


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Qxt/lib/release/ -lQxtCore
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Qxt/lib/debug/ -lQxtCore
#else:mac: LIBS += -F$$PWD/../../../../usr/local/Qxt/lib/ -framework QxtCore
#else:unix: LIBS += -L$$PWD/../../../../usr/local/Qxt/lib/ -lQxtCore

#INCLUDEPATH += $$PWD/../../../../usr/local/Qxt/include/QxtCore
#DEPENDPATH += $$PWD/../../../../usr/local/Qxt/include/QxtCore

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Qxt/lib/release/ -lQxtWidgets
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Qxt/lib/debug/ -lQxtWidgets
#else:mac: LIBS += -F$$PWD/../../../../usr/local/Qxt/lib/ -framework QxtWidgets
#else:unix: LIBS += -L$$PWD/../../../../usr/local/Qxt/lib/ -lQxtWidgets

#INCLUDEPATH += $$PWD/../../../../usr/local/Qxt/include
#DEPENDPATH += $$PWD/../../../../usr/local/Qxt/include

RESOURCES += \
    sounds.qrc
