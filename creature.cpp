#include <QtWidgets>

#include "creature.h"

Creature::Creature()
{
    active = false;
    delaying = false;
    statusEffects = new QList<StatusEffectBox *>();

    nameEdit = new QLineEdit();
    nameEdit->setMaximumWidth(200);
    nameEdit->setFixedWidth(200);
    nameEdit->setPlaceholderText("Creature name");

    initiativeSpinBox = new QDoubleSpinBox();
    initiativeSpinBox->setMaximum(50);

    enemyCheckbox = new QCheckBox(tr("Enemy?"));
    enemyCheckbox->setChecked(true);
    connect(enemyCheckbox, SIGNAL(stateChanged(int)), this, SLOT(changeAlliance(int)));

    basicInfoLayout = new QGridLayout;
    basicInfoLayout->addWidget(nameEdit);
    basicInfoLayout->addWidget(initiativeSpinBox);
    basicInfoLayout->addWidget(enemyCheckbox);

    QPushButton * addStatusEffectButton = new QPushButton();
    addStatusEffectButton->setText("+");
    connect(addStatusEffectButton, SIGNAL(clicked()), this, SLOT(createNewStatusEffect()));

    extraInfoLayout = new QHBoxLayout;
    extraInfoLayout->addWidget(addStatusEffectButton);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(basicInfoLayout);
    mainLayout->addLayout(extraInfoLayout);

    setLayout(mainLayout);
    setObjectName("foe");
    setStyleSheet("QGroupBox#foe");
}

Creature::~Creature()
{
}

void Creature::changeAlliance(int state){
    configureStylesheet();
}

void Creature::notifyTurnStart(){
    active = true;
    delaying = false;
    configureStylesheet();
    for(int i = 0; i < statusEffects->size(); i++){
        statusEffects->at(i)->notifyNewTurn();
    }
}

void Creature::notifyCombatOver(){
    active = false;
    delaying = false;
    configureStylesheet();
}

void Creature::delay(){
    active = false;
    delaying = true;
    configureStylesheet();
}

void Creature::endCreatureTurn(){
    delaying = false;
    active = false;
    configureStylesheet();
}

bool Creature::isActive(){
    return active;
}

bool Creature::isDelaying(){
    return delaying;
}

bool Creature::isEnemy(){
    return enemyCheckbox->isChecked();
}

QString Creature::name(){
    return nameEdit->text();
}

int Creature::initiativeValue(){
    return initiativeSpinBox->text().toDouble();
}

void Creature::createNewStatusEffect(){
    StatusEffectBox * statusEffect = new StatusEffectBox();
    connect(statusEffect, SIGNAL(expireStatusEffect(StatusEffectBox*)), this, SLOT(deleteStatusEffect(StatusEffectBox*)));
    extraInfoLayout->addWidget(statusEffect);
    statusEffects->append(statusEffect);
}

void Creature::configureStylesheet(){
    if(delaying){
        setObjectName("delaying");
        setStyleSheet("QGroupBox#delaying");
        show();
    }else if(enemyCheckbox->checkState() == 2 && active){
        setObjectName("foeActive");
        setStyleSheet("QGroupBox#foeActive");
        show();
    }else if(enemyCheckbox->checkState() == 2){
        setObjectName("foe");
        setStyleSheet("QGroupBox#foe");
        show();
    }else if(enemyCheckbox->checkState() == 0 && active){
        setObjectName("friendActive");
        setStyleSheet("QGroupBox#friendActive");
        show();
    }else{
        setObjectName("friend");
        setStyleSheet("QGroupBox#friend");
        show();
    }
}

void Creature::deleteStatusEffect(StatusEffectBox *statusEffect){
    statusEffects->removeOne(statusEffect);
    extraInfoLayout->removeWidget(statusEffect);
    delete statusEffect;
}
