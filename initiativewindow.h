#ifndef INITIATIVEWINDOW_H
#define INITIATIVEWINDOW_H

#include <QWidget>
#include <QToolbox>

//#include <QxtGlobalShortcut>

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
    void addNewCreature();

private:
    Ui::InitiativeWindow *ui;
    Creature *createCreature();
    QVBoxLayout *initiativeOrderLayout;
    QList<Creature *> *creatures;

    int delayedCreatures;
    bool isCombat;

    void setupInitialCreatures();
    void setupButtons();

    void reorderCreatures();
    void notifyNextCreatureTurn(int nextCreatureIndex);
    void startCombat();
    void endCombat();

//    QxtGlobalShortcut globalStartEndCombat;
//    QxtGlobalShortcut globalNextTurn;
//    QxtGlobalShortcut globalDelete;
//    QxtGlobalShortcut globalDelay;
//    QxtGlobalShortcut globalStopDelay;
//    QxtGlobalShortcut globalAddNewCreature;
};

#endif // INITIATIVEWINDOW_H
