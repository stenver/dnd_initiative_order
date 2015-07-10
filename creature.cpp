#include <QtWidgets>

#include "creature.h"

Creature::Creature(QWidget *parent) : QGroupBox(parent)
{
    setupBasicInfoLayout();
    setupExtraInfoLayout();

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(basicInfoLayout);
    mainLayout->addLayout(extraInfoLayout);

    setLayout(mainLayout);
    setObjectName("foe");
    setStyleSheet("QGroupBox#foe");
    setFixedHeight(160);

    connect(nameEdit, &QLineEdit::editingFinished, this, &Creature::nameEditEnded);
}

Creature::~Creature()
{
}

void Creature::startTurn(){
    active = true;
    delaying = false;
    configureStylesheet();

    if(isEnemy()){
        QSound::play(QUrl::fromLocalFile(":/sounds/foe.wav").path());
    }else{
        QSound::play(QUrl::fromLocalFile(":/sounds/friend.wav").path());
    }

    emit turnStarted();
}

void Creature::startCombat(){
    initiativeSpinBox->setEnabled(false);
}

void Creature::endCombat(){
    active = false;
    delaying = false;
    configureStylesheet();
    initiativeSpinBox->setEnabled(true);
}

void Creature::delay(){
    active = false;
    delaying = true;
    configureStylesheet();
}

void Creature::resetState(){
    delaying = false;
    active = false;
    configureStylesheet();
}

void Creature::notifyTurnEnd(){
    delaying = false;
    active = false;
    configureStylesheet();

    emit turnEnded();
}

bool Creature::isActive() const{
    return active;
}

bool Creature::isDelaying() const{
    return delaying;
}

bool Creature::isEnemy() const{
    return enemyCheckbox->isChecked();
}

QString Creature::name() const{
    return nameEdit->text();
}

double Creature::initiativeValue() const{
    return initiativeSpinBox->value();
}

void Creature::changeAlliance(int state){
    configureStylesheet();
}

void Creature::createNewStatusEffect(){
    StatusEffectBox * statusEffect = new StatusEffectBox();

    connect(this, &Creature::turnStarted, statusEffect, &StatusEffectBox::startTurn);
    connect(this, &Creature::turnEnded, statusEffect, &StatusEffectBox::endTurn);

    extraInfoLayout->addWidget(statusEffect);
}

void Creature::nameEditEnded(){
    emit nameEdited();
}

void Creature::setupBasicInfoLayout(){
    nameEdit = new QLineEdit();
    nameEdit->setMaximumWidth(200);
    nameEdit->setPlaceholderText("Creature name");

    initiativeSpinBox = new QDoubleSpinBox();
    initiativeSpinBox->setMaximum(50);

    enemyCheckbox = new QCheckBox(tr("Enemy?"));
    enemyCheckbox->setChecked(true);
    connect(enemyCheckbox, &QCheckBox::stateChanged, this, &Creature::changeAlliance);

    basicInfoLayout = new QGridLayout;
    basicInfoLayout->addWidget(nameEdit);
    basicInfoLayout->addWidget(initiativeSpinBox);
    basicInfoLayout->addWidget(enemyCheckbox);
}

void Creature::setupExtraInfoLayout(){
    addStatusEffectButton = new QPushButton("Add status");
    connect(addStatusEffectButton, &QPushButton::clicked, this, &Creature::createNewStatusEffect);

    extraInfoLayout = new QHBoxLayout;
    extraInfoLayout->addWidget(addStatusEffectButton);
}

void Creature::configureStylesheet(){
    if(isEnemy() && delaying){
        setObjectName("foeDelaying");
        setStyleSheet("QGroupBox#foeDelaying");
    }else if(!isEnemy() && delaying){
        setObjectName("friendDelaying");
        setStyleSheet("QGroupBox#friendDelaying");
    }else if(isEnemy() && active){
        setObjectName("foeActive");
        setStyleSheet("QGroupBox#foeActive");
    }else if(isEnemy()){
        setObjectName("foe");
        setStyleSheet("QGroupBox#foe");
    }else if(!isEnemy() && active){
        setObjectName("friendActive");
        setStyleSheet("QGroupBox#friendActive");
    }else{
        setObjectName("friend");
        setStyleSheet("QGroupBox#friend");
    }
}

