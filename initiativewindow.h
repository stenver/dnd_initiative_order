#ifndef INITIATIVEWINDOW_H
#define INITIATIVEWINDOW_H

#include <QWidget>
#include <QToolbox>

#include "creature.h"
#include "qxtglobalshortcut.h"

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
    void deleteActiveCreature();
    void addNewCreature();

private:
    Ui::InitiativeWindow *ui;
    Creature *createCreature(bool enemy = true);
    QVBoxLayout *initiativeOrderLayout;
    QList<Creature *> creatures;
    QxtGlobalShortcut * globalStartEndCombat;
    QxtGlobalShortcut * globalNextTurn;
    QxtGlobalShortcut * globalDelete;
    QxtGlobalShortcut * globalDelay;
    QxtGlobalShortcut * globalStopDelay;
    QxtGlobalShortcut * globalAddNewCreature;

    bool isCombat = false;

    void setupInitialCreatures();
    void setupButtons();

    void startCombat();
    void endCombat();
    void reorderCreatures();
    void deleteNamelessCreatures();
    void redrawCreatures();
};

#endif // INITIATIVEWINDOW_H
