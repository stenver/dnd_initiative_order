#include "statuseffect.h"
#include <QtWidgets>

StatusEffectBox::StatusEffectBox()
{
    statusNameEdit = new QLineEdit();
    statusNameEdit->setPlaceholderText("Status name");

    initiativeSpinBox = new QSpinBox();
    initiativeSpinBox->setValue(1);

    deleteButton = new QPushButton();
    deleteButton->setText("Delete");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));

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

void StatusEffectBox::notifyNewTurn(){
    if(initiativeSpinBox->text().toInt() == 1){
        setObjectName("statusAboutToEnd");
        setStyleSheet("QGroupBox#statusAboutToEnd");
        show();
    }
}

void StatusEffectBox::notifyEndTurn(){
    int statusTurnsLeft = initiativeSpinBox->text().toInt() - 1;
    initiativeSpinBox->setValue(statusTurnsLeft);
    if (statusTurnsLeft == 0){
        deleteStatusEffect();
    }
}

void StatusEffectBox::deleteStatusEffect(){
    this->destroy();
    delete this;
}
