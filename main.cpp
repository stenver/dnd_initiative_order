#include "initiativewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitiativeWindow w;
    w.show();

    return a.exec();
}
