#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H

#include <QGroupBox>
#include <QHBoxLayout>

class QLineEdit;
class QSpinBox;
class QPushButton;

class StatusEffectBox : public QGroupBox
{
public:
    StatusEffectBox();
    ~StatusEffectBox();

    void notifyNewTurn();

signals:
    void ExpireStatusEffect(StatusEffectBox*);

private slots:
    void deleteButtonClicked();

private:
    QLineEdit *statusNameEdit;
    QSpinBox *initiativeSpinBox;
    QPushButton *deleteButton;
    QVBoxLayout *layout;
};

#endif // STATUSEFFECT_H
