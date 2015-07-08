#ifndef CREATURE_H
#define CREATURE_H

#include <QGroupBox>
#include <QHBoxLayout>

#include "statuseffect.h"

class QDoubleSpinBox;
class QLineEdit;
class QGridLayout;
class QCheckBox;
class QSlider;
class QPushButton;

class Creature : public QGroupBox
{
    Q_OBJECT
public:
    Creature();
    ~Creature();

    void notifyTurnStart();
    void notifyCombatOver();
    void delay();
    void endCreatureTurn();
    bool isActive();
    bool isDelaying();
    bool isEnemy();
    QString name();
    int initiativeValue();

    QLineEdit *nameEdit;

private slots:
    void changeAlliance(int);
    void createNewStatusEffect();

private:
    bool delaying;
    bool active;

    QCheckBox *enemyCheckbox;
    QHBoxLayout *mainLayout;
    QGridLayout *basicInfoLayout;
    QHBoxLayout *extraInfoLayout;
    QDoubleSpinBox *initiativeSpinBox;
    QList<StatusEffectBox *> *statusEffects;

    void deleteStatusEffect(StatusEffectBox * statusEffect);
    void configureStylesheet();
};

#endif // CREATURE_H
