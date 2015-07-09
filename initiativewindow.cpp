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
    delayedCreatures = 0;
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

    ui->startEndButton->setText("End combat");
    ui->delayButton->setEnabled(true);
    ui->nextCreatureButton->setEnabled(true);
    ui->deleteCreatureButton->setEnabled(true);
    ui->addNewCreature->setEnabled(true);

    creatures->first()->notifyTurnStart();
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
          creature->notifyCombatOver();
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
    for(int i = delayedCreatures; i < creatures->size(); i++){
        Creature *creature = creatures->at(i);
        if (creature->isActive()){
            creature->notifyTurnEnd();
            notifyNextCreatureTurn(i + 1);
            break;
        }
    }
    QLayoutItem* item = initiativeOrderLayout->takeAt(delayedCreatures);
    initiativeOrderLayout->addItem(item);
}

void InitiativeWindow::delayCreature(){
    if(delayedCreatures + 1 == creatures->size()){
        stopDelayAll();
    }else{
        for(int i = 0; i < creatures->size(); i++){
            Creature * c = creatures->at(i);
            if (creatures->at(i)->isActive()){
                c->delay();
                delayedCreatures += 1;
                notifyNextCreatureTurn(i + 1);
                break;
            }
        }
        ui->stopDelayButton->setEnabled(true);
    }
}

void InitiativeWindow::stopDelayAll(){
    ui->stopDelayButton->setEnabled(false);
    delayedCreatures = 0;
    bool firstDelay = true;

    for(int i = 0; i < creatures->size(); i++){
        Creature * c = creatures->at(i);
        bool delaying = c->isDelaying();
        c->notifyTurnEnd();
        if (delaying && firstDelay){
            c->notifyTurnStart();
            firstDelay = false;
        }
    }
}

void InitiativeWindow::deleteCreature(){
    if(creatures->size() > 1){
        initiativeOrderLayout->takeAt(delayedCreatures);
        for(int i = 0; i < creatures->size(); i++){
           Creature * creature = creatures->at(i);
           if(creature->isActive()){
               notifyNextCreatureTurn(i + 1);
               creatures->removeAt(i);
               delete creature;
               break;
           }
        }
    }else{
        endCombat();
    }
}

void InitiativeWindow::addNewCreature(){
    Creature * new_creature = createCreature();
    creatures->at(delayedCreatures)->notifyTurnEnd();

    // Clean up layout
    for(int i = 0; i < creatures->size(); i++){
        initiativeOrderLayout->removeWidget(creatures->at(i));
    }

    creatures->insert(delayedCreatures, new_creature);
    new_creature->notifyTurnStart();

    // Redraw the creatures
    for(int i = 0; i < creatures->size(); i++){
        initiativeOrderLayout->addWidget(creatures->at(i));
    }
}

void InitiativeWindow::reorderCreatures(){
    std::sort (creatures->begin(), creatures->end(), &sortByInitiative);

    QList<Creature *>::iterator it = creatures->begin();
    while (it != creatures->end()) {
      Creature * creature = *it;

      initiativeOrderLayout->removeWidget(creature);

      if(creature->name() != ""){
          initiativeOrderLayout->addWidget(creature);
          ++it;
      }else{
          delete creature;
          it = creatures->erase(it);
      }
    }
}

void InitiativeWindow::notifyNextCreatureTurn(int nextCreatureIndex){
    if(nextCreatureIndex == creatures->size()){
        creatures->at(delayedCreatures)->notifyTurnStart();
    }else{
        creatures->at(nextCreatureIndex)->notifyTurnStart();
    }
}

