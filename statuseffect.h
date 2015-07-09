#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H

#include <QGroupBox>
#include <QHBoxLayout>

class QLineEdit;
class QSpinBox;
class QPushButton;

class StatusEffectBox : public QGroupBox
{
    Q_OBJECT
public:
    StatusEffectBox();
    ~StatusEffectBox();

    void notifyEndTurn();
    void notifyNewTurn();

private slots:
    void deleteButtonClicked();

private:
    QLineEdit *statusNameEdit;
    QSpinBox *initiativeSpinBox;
    QPushButton *deleteButton;
    QVBoxLayout *layout;

    void deleteStatusEffect();
};

#endif // STATUSEFFECT_H
