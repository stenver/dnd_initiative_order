#include <QtWidgets>

#include "creature.h"

Creature::Creature()
{
    active = false;
    delaying = false;
    statusEffects = new QList<StatusEffectBox *>();

    setupBasicInfoLayout();
    setupExtraInfoLayout();
    setupSounds();

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

void Creature::notifyTurnStart(){
    active = true;
    delaying = false;
    configureStylesheet();

    if(enemyCheckbox->isChecked()){
        foePlayer->play();
    }else{
        friendPlayer->play();
    }

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

void Creature::notifyTurnEnd(){
    delaying = false;
    active = false;
    configureStylesheet();

    QList<StatusEffectBox *>::iterator it = statusEffects->begin();
    while(it != statusEffects->end()){
        StatusEffectBox * statusEffect = *it;
        statusEffect->notifyEndTurn();
        // Notify end turn might delete some status effects, recheck iterators
        if(it != statusEffects->end()){
            ++it;
        }else{
            break;
        }
    }
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

double Creature::initiativeValue(){
    return initiativeSpinBox->value();
}

void Creature::changeAlliance(int state){
    configureStylesheet();
}

void Creature::createNewStatusEffect(){
    StatusEffectBox * statusEffect = new StatusEffectBox();
    connect(statusEffect, SIGNAL(destroyed(QObject*)), this, SLOT(deleteStatusEffect(QObject*)));
    extraInfoLayout->addWidget(statusEffect);
    statusEffects->append(statusEffect);
}

void Creature::deleteStatusEffect(QObject *statusEffect){
    QList<StatusEffectBox *>::iterator it = statusEffects->begin();
    while(it != statusEffects->end()){
        StatusEffectBox * s = *it;
        if(s == statusEffect){
            it = statusEffects->erase(it);
            extraInfoLayout->removeWidget(s);
            break;
        }else{
            ++it;
        }
    }
}

void Creature::setupBasicInfoLayout(){
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
}

void Creature::setupExtraInfoLayout(){
    addStatusEffectButton = new QPushButton();
    addStatusEffectButton->setText("Add status");
    connect(addStatusEffectButton, SIGNAL(clicked()), this, SLOT(createNewStatusEffect()));

    extraInfoLayout = new QHBoxLayout;
    extraInfoLayout->addWidget(addStatusEffectButton);
}

void Creature::setupSounds(){
    // TODO set proper relative path
    friendPlayer = new QSound(QUrl::fromLocalFile("/Users/stenver/cpp/dnd_initatives/friend.wav").path());
    foePlayer = new QSound(QUrl::fromLocalFile("/Users/stenver/cpp/dnd_initatives/foe.wav").path());
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

