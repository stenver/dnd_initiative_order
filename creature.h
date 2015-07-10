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
    Creature(QWidget *parent = nullptr);
    ~Creature();

    void endCombat();
    void startTurn();
    void startCombat();
    void resetState();
    void delay();
    void notifyTurnEnd();

    bool isActive() const;
    bool isDelaying() const;
    bool isEnemy() const;
    QString name() const;
    double initiativeValue() const;

signals:
    void nameEdited();
    void turnStarted();
    void turnEnded();

private slots:
    void changeAlliance(int);
    void createNewStatusEffect();
    void nameEditEnded();

private:
    bool delaying = false;
    bool active = false;

    QCheckBox *enemyCheckbox;
    QHBoxLayout *mainLayout;
    QGridLayout *basicInfoLayout;
    QHBoxLayout *extraInfoLayout;
    QDoubleSpinBox *initiativeSpinBox;
    QPushButton * addStatusEffectButton;
    QLineEdit *nameEdit;

    void setupBasicInfoLayout();
    void setupExtraInfoLayout();
    void configureStylesheet();

};

#endif // CREATURE_H
