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
    isCombat = false;
    setupInitialCreatures();
    setupButtons();
}

InitiativeWindow::~InitiativeWindow()
{
    delete ui;
}

void InitiativeWindow::setupInitialCreatures(){
    initiativeOrderLayout = new QVBoxLayout;

    creatures = new QList<Creature *>;
    creatures->append(createCreature());
    creatures->append(createCreature());

    initiativeOrderLayout->addWidget(creatures->at(0));
    initiativeOrderLayout->addWidget(creatures->at(1));

    ui->scrollAreaWidgetContents->setLayout(initiativeOrderLayout);
}

void InitiativeWindow::setupButtons(){
    ui->delayButton->setEnabled(false);
    ui->stopDelayButton->setEnabled(false);
    ui->nextCreatureButton->setEnabled(false);
    ui->deleteCreatureButton->setEnabled(false);
    ui->addNewCreature->setEnabled(false);

    connect(ui->startEndButton, SIGNAL(clicked()), this, SLOT(startOrEndCombat()));
    connect(ui->nextCreatureButton, SIGNAL(clicked(bool)), this, SLOT(nextCreatureTurn()));
    connect(ui->deleteCreatureButton, SIGNAL(clicked(bool)), this, SLOT(deleteCreature()));
    connect(ui->delayButton, SIGNAL(clicked(bool)), this, SLOT(delayCreature()));
    connect(ui->stopDelayButton, SIGNAL(clicked()), this, SLOT(stopDelayAll()));
    connect(ui->addNewCreature, SIGNAL(clicked()), this, SLOT(addNewCreature()));
}

Creature * InitiativeWindow::createCreature(){
    Creature *creature = new Creature;
    connect(creature->nameEdit, SIGNAL(editingFinished()), this, SLOT(createNewCreatureIfLast()));
    return creature;
}

void InitiativeWindow::createNewCreatureIfLast(){
    if(!isCombat && creatures->last()->name() != ""){
        Creature * new_creature = createCreature();
        creatures->append(new_creature);
        initiativeOrderLayout->addWidget(new_creature);
    }
}

void InitiativeWindow::startOrEndCombat(){
    if(isCombat){
        endCombat();
    }else{
        startCombat();
    }
}

bool static sortByInitiative(Creature * x, Creature * y){
    return (x->initiativeValue() > y->initiativeValue());
}

void InitiativeWindow::startCombat(){
    reorderCreatures();
    isCombat = true;
    for(int i = 0; i < creatures->size(); i++){
        creatures->at(i)->startCombat();
    }

    ui->startEndButton->setText("End combat");
    ui->delayButton->setEnabled(true);
    ui->nextCreatureButton->setEnabled(true);
    ui->deleteCreatureButton->setEnabled(true);
    ui->addNewCreature->setEnabled(true);

    creatures->first()->startTurn();
}

void InitiativeWindow::endCombat(){
    QList<Creature *>::iterator it = creatures->begin();
    while (it != creatures->end()) {
      Creature * creature = *it;

      if(creature->isEnemy()){
          initiativeOrderLayout->removeWidget(creature);
          it = creatures->erase(it);
          delete creature;
      }else{
          creature->endCombat();
          ++it;
      }
    }

    if(creatures->size() == 0){
        creatures->append(createCreature());
        initiativeOrderLayout->addWidget(creatures->at(0));
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
    Creature * creature = creatures->takeAt(0);
    creature->notifyTurnEnd();
    creatures->push_back(creature);
    creatures->at(0)->startTurn();
    redrawCreatures();
}

void InitiativeWindow::delayCreature(){
    Creature * creature = creatures->takeAt(0);
    if(creature->isDelaying()){
        stopDelayAll();
    }else{
        creature->delay();
        creatures->push_back(creature);
        creatures->at(0)->startTurn();
        redrawCreatures();

        ui->stopDelayButton->setEnabled(true);
    }
}

void InitiativeWindow::stopDelayAll(){
    creatures->at(0)->resetState();

    QList<Creature*> *delayingCreatures = new QList<Creature*>();
    QList<Creature *>::iterator it = creatures->begin();
    while (it != creatures->end()) {
      Creature * creature = *it;
      if(creature->isDelaying()){
          creature->resetState();
          it = creatures->erase(it);
          delayingCreatures->push_back(creature);
      }else{
          ++it;
      }
    }

    delayingCreatures->at(0)->startTurn();

    for(int i = 0; i < delayingCreatures->size(); i++){
        creatures->insert(i, delayingCreatures->at(i));
    }

    redrawCreatures();
    ui->stopDelayButton->setEnabled(false);
}

void InitiativeWindow::deleteCreature(){
    if(creatures->size() > 1){
        Creature * creature = creatures->takeAt(0);
        creatures->at(0)->startTurn();
        delete creature;
        redrawCreatures();
    }else{
        endCombat();
    }
}

void InitiativeWindow::addNewCreature(){
    creatures->at(0)->resetState();

    Creature * new_creature = createCreature();
    creatures->insert(0, new_creature);
    new_creature->startTurn();

    redrawCreatures();
}

void InitiativeWindow::reorderCreatures(){
    std::sort (creatures->begin(), creatures->end(), &sortByInitiative);

    deleteNamelessCreatures();
    redrawCreatures();
}

void InitiativeWindow::deleteNamelessCreatures(){
    QList<Creature *>::iterator it = creatures->begin();
    while (it != creatures->end()) {
      Creature * creature = *it;
      if(creature->name() != ""){
          ++it;
      }else{
          delete creature;
          it = creatures->erase(it);
      }
    }
}

void InitiativeWindow::redrawCreatures(){
    QLayoutItem *item;
    while ( (item = initiativeOrderLayout->layout()->takeAt(0))){
        // NOOP, just remove widgets
    }

    for(int i = 0; i < creatures->size(); i++){
        initiativeOrderLayout->addWidget(creatures->at(i));
    }
}

