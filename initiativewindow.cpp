#include <QtWidgets>
#include <algorithm>
#include <QListIterator>
#include <QAbstractEventDispatcher>

#include "initiativewindow.h"
#include "ui_initiativewindow.h"

InitiativeWindow::InitiativeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InitiativeWindow)
{
    ui->setupUi(this);
    setupInitialCreatures();
    setupButtons();
}

InitiativeWindow::~InitiativeWindow()
{
    delete ui;
}

void InitiativeWindow::setupInitialCreatures(){
    initiativeOrderLayout = new QVBoxLayout;
    initiativeOrderLayout->setAlignment(Qt::AlignTop);

    creatures.append(createCreature(false));
    creatures.append(createCreature(false));

    initiativeOrderLayout->addWidget(creatures.at(0));
    initiativeOrderLayout->addWidget(creatures.at(1));

    ui->scrollAreaWidgetContents->setLayout(initiativeOrderLayout);
}

void InitiativeWindow::setupButtons(){
    ui->delayButton->setEnabled(false);
    ui->stopDelayButton->setEnabled(false);
    ui->nextCreatureButton->setEnabled(false);
    ui->deleteCreatureButton->setEnabled(false);
    ui->addNewCreature->setEnabled(false);

    connect(ui->startEndButton, &QPushButton::clicked, this, &InitiativeWindow::startOrEndCombat);
    connect(ui->nextCreatureButton, &QPushButton::clicked, this, &InitiativeWindow::nextCreatureTurn);
    connect(ui->deleteCreatureButton, &QPushButton::clicked, this, &InitiativeWindow::deleteActiveCreature);
    connect(ui->delayButton, &QPushButton::clicked, this, &InitiativeWindow::delayCreature);
    connect(ui->stopDelayButton, &QPushButton::clicked, this, &InitiativeWindow::stopDelayAll);
    connect(ui->addNewCreature, &QPushButton::clicked, this, &InitiativeWindow::addNewCreature);

    globalStartEndCombat = new QxtGlobalShortcut (this);
    globalStartEndCombat->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
    connect(globalStartEndCombat, &QxtGlobalShortcut::activated, this, &InitiativeWindow::startOrEndCombat);

    globalNextTurn = new QxtGlobalShortcut (this);
    globalNextTurn->setShortcut(QKeySequence (Qt::CTRL + Qt::Key_F1));
    connect(globalNextTurn, &QxtGlobalShortcut::activated, this, &InitiativeWindow::nextCreatureTurn);

    globalDelay = new QxtGlobalShortcut (this);
    globalDelay->setShortcut(QKeySequence (Qt::CTRL + Qt::Key_F2));
    connect(globalDelay, &QxtGlobalShortcut::activated, this, &InitiativeWindow::delayCreature);

    globalStopDelay = new QxtGlobalShortcut (this);
    globalStopDelay->setShortcut(QKeySequence (Qt::CTRL + Qt::Key_F3));
    connect(globalStopDelay, &QxtGlobalShortcut::activated, this, &InitiativeWindow::stopDelayAll);

    globalDelete = new QxtGlobalShortcut (this);
    globalDelete->setShortcut(QKeySequence (Qt::CTRL + Qt::Key_F11));
    connect(globalDelete, &QxtGlobalShortcut::activated, this, &InitiativeWindow::deleteActiveCreature);

    globalAddNewCreature = new QxtGlobalShortcut (this);
    globalAddNewCreature->setShortcut(QKeySequence (Qt::CTRL + Qt::Key_F12));
    connect(globalAddNewCreature, &QxtGlobalShortcut::activated, this, &InitiativeWindow::addNewCreature);
}

Creature * InitiativeWindow::createCreature(bool enemy){
    Creature *creature = new Creature(enemy);
    connect(creature, &Creature::nameEdited, this, &InitiativeWindow::createNewCreatureIfLast);
    return creature;
}

void InitiativeWindow::createNewCreatureIfLast(){
    if(!isCombat && creatures.last()->name() != ""){
        Creature * new_creature = createCreature();
        creatures.append(new_creature);
        initiativeOrderLayout->addWidget(new_creature);
    }
}

void InitiativeWindow::startOrEndCombat(){
    isCombat ? endCombat() : startCombat();
}

void InitiativeWindow::startCombat(){
    reorderCreatures();
    isCombat = true;
    for(int i = 0; i < creatures.size(); i++){
        creatures.at(i)->startCombat();
    }

    ui->startEndButton->setText("End combat");
    ui->delayButton->setEnabled(true);
    ui->nextCreatureButton->setEnabled(true);
    ui->deleteCreatureButton->setEnabled(true);
    ui->addNewCreature->setEnabled(true);

    creatures.first()->startTurn();
}

void InitiativeWindow::endCombat(){
    QList<Creature *>::iterator it = creatures.begin();
    while (it != creatures.end()) {
      Creature * creature = *it;

      if(creature->isEnemy()){
          initiativeOrderLayout->removeWidget(creature);
          it = creatures.erase(it);
          delete creature;
      }else{
          creature->endCombat();
          ++it;
      }
    }

    if(creatures.size() == 0){
        creatures.append(createCreature());
        initiativeOrderLayout->addWidget(creatures.at(0));
    }

    isCombat = false;
    ui->startEndButton->setText("Start combat");

    ui->delayButton->setEnabled(false);
    ui->stopDelayButton->setEnabled(false);
    ui->nextCreatureButton->setEnabled(false);
    ui->deleteCreatureButton->setEnabled(false);
    ui->addNewCreature->setEnabled(false);
}

void InitiativeWindow::nextCreatureTurn(){
    if(!isCombat) return;
    Creature * creature = creatures.takeAt(0);
    creature->notifyTurnEnd();
    creatures.push_back(creature);
    creatures.at(0)->startTurn();
    redrawCreatures();
}

void InitiativeWindow::delayCreature(){
    if(!isCombat) return;
    Creature * creature = creatures.takeAt(0);
    if(creature->isDelaying()){
        stopDelayAll();
    }else{
        creature->delay();
        creatures.push_back(creature);
        creatures.at(0)->startTurn();
        redrawCreatures();

        ui->stopDelayButton->setEnabled(true);
    }
}

void InitiativeWindow::stopDelayAll(){
    if(!isCombat) return;

    QList<Creature*> delayingCreatures;
    QList<Creature *>::iterator it = creatures.begin();
    while (it != creatures.end()) {
      Creature * creature = *it;
      if(creature->isDelaying()){
          creature->resetState();
          it = creatures.erase(it);
          delayingCreatures.push_back(creature);
      }else{
          ++it;
      }
    }

    if(delayingCreatures.size() > 0){
        creatures.at(0)->resetState();
        delayingCreatures.at(0)->startTurn();

        for(int i = 0; i < delayingCreatures.size(); i++){
            creatures.insert(i, delayingCreatures.at(i));
        }

        redrawCreatures();
    }
    ui->stopDelayButton->setEnabled(false);
}

void InitiativeWindow::deleteActiveCreature(){
    if(!isCombat) return;
    if(creatures.size() > 1){
        Creature * creature = creatures.takeAt(0);
        creatures.at(0)->startTurn();
        delete creature;
        redrawCreatures();
    }else{
        endCombat();
    }
}

void InitiativeWindow::addNewCreature(){
    if(!isCombat) return;
    creatures.at(0)->resetState();

    Creature * new_creature = createCreature();
    creatures.insert(0, new_creature);
    new_creature->startTurn();

    redrawCreatures();
}

void InitiativeWindow::reorderCreatures(){
    std::sort(creatures.begin(), creatures.end(),
        [](Creature* x, Creature* y) {
         return x->initiativeValue() > y->initiativeValue();
    });

    deleteNamelessCreatures();
    redrawCreatures();
}

void InitiativeWindow::deleteNamelessCreatures(){
    QList<Creature *>::iterator it = creatures.begin();
    while (it != creatures.end()) {
      Creature * creature = *it;
      if(creature->name() != ""){
          ++it;
      }else{
          delete creature;
          it = creatures.erase(it);
      }
    }
}

void InitiativeWindow::redrawCreatures(){
    QLayoutItem *item;
    while ( (item = initiativeOrderLayout->layout()->takeAt(0))){
        qt_noop(); // NOOP, just remove widgets
    }

    for(int i = 0; i < creatures.size(); i++){
        initiativeOrderLayout->addWidget(creatures.at(i));
    }
}

