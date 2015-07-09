#include "initiativewindow.h"

#include <QApplication>
#if __cplusplus <= 199711L
  #error This library needs at least a C++11 compliant compiler
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitiativeWindow w;
    w.show();

    return a.exec();
}
