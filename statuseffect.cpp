#include "statuseffect.h"
#include <QtWidgets>

StatusEffectBox::StatusEffectBox(QWidget *parent) : QGroupBox(parent)
{
    statusNameEdit = new QLineEdit();
    statusNameEdit->setPlaceholderText("Status name");

    initiativeSpinBox = new QSpinBox();
    initiativeSpinBox->setValue(1);

    deleteButton = new QPushButton("Delete");
    connect(deleteButton, &QPushButton::clicked, this, &StatusEffectBox::deleteButtonClicked);

    layout = new QVBoxLayout();
    layout->addWidget(statusNameEdit);
    layout->addWidget(initiativeSpinBox);
    layout->addWidget(deleteButton);
    setLayout(layout);
}

StatusEffectBox::~StatusEffectBox()
{
}

void StatusEffectBox::deleteButtonClicked(){
    deleteStatusEffect();
}

void StatusEffectBox::startTurn(){
    if(initiativeSpinBox->value() == 0){
        setObjectName("statusEndsNow");
        setStyleSheet("QGroupBox#statusEndsNow");
        show();
    }
}

void StatusEffectBox::endTurn(){
    int statusTurnsLeft = initiativeSpinBox->text().toInt();
    if (statusTurnsLeft == 0){
        deleteStatusEffect();
    }else{
        initiativeSpinBox->setValue(statusTurnsLeft - 1);

        if((statusTurnsLeft - 1) == 0){
            setObjectName("statusAboutToEnd");
            setStyleSheet("QGroupBox#statusAboutToEnd");
            show();
        }
    }
}

void StatusEffectBox::deleteStatusEffect(){
    this->destroy();
    delete this;
}
