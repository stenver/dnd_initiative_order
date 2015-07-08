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

}

void StatusEffectBox::notifyNewTurn(){
    int statusTurnsLeft = initiativeSpinBox->text().toInt();
    initiativeSpinBox->setValue(statusTurnsLeft - 1);
    if (statusTurnsLeft < 0){
        delete this;
    }
}
