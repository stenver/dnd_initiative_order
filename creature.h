#ifndef CREATURE_H
#define CREATURE_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QSound>

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
    void notifyTurnEnd();
    bool isActive();
    bool isDelaying();
    bool isEnemy();
    QString name();
    double initiativeValue();

    QLineEdit *nameEdit;

private slots:
    void changeAlliance(int);
    void createNewStatusEffect();
    void deleteStatusEffect(QObject * statusEffect);

private:
    bool delaying;
    bool active;

    QCheckBox *enemyCheckbox;
    QHBoxLayout *mainLayout;
    QGridLayout *basicInfoLayout;
    QHBoxLayout *extraInfoLayout;
    QDoubleSpinBox *initiativeSpinBox;
    QList<StatusEffectBox *> *statusEffects;
    QPushButton * addStatusEffectButton;
    QSound * friendPlayer;
    QSound * foePlayer;

    void setupBasicInfoLayout();
    void setupExtraInfoLayout();
    void setupSounds();
    void configureStylesheet();

};

#endif // CREATURE_H
