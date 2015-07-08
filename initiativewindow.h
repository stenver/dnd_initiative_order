#ifndef INITIATIVEWINDOW_H
#define INITIATIVEWINDOW_H

//#include <QxtGlobalShortcut
#include <QWidget>
#include <QToolbox>

#include "creature.h"

class QVBoxLayout;

namespace Ui {
class InitiativeWindow;
}

class InitiativeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InitiativeWindow(QWidget *parent = 0);
    ~InitiativeWindow();

private slots:
    void createNewCreatureIfLast();
    void startOrEndCombat();
    void nextCreatureTurn();
    void delayCreature();
    void stopDelayAll();
    void deleteCreature();

private:
    Ui::InitiativeWindow *ui;

    int delayedCreatures;
    Creature *createCreature();
    bool isCombat;
    void setupInitialCreatures();
    void setupButtons();
    void notifyNextCreatureTurn(int nextCreatureIndex);

    void startCombat();
    void endCombat();

    QVBoxLayout *initiativeOrderLayout;
    QList<Creature *> *creatures;
//    QxtGlobalShortcut globalStartEndCombat;
//    QxtGlobalShortcut globalNextTurn;
//    QxtGlobalShortcut globalDelete;
//    QxtGlobalShortcut globalDelay;
//    QxtGlobalShortcut globalStopDelay;
};

#endif // INITIATIVEWINDOW_H
