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
    StatusEffectBox(QWidget *parent = nullptr);
    ~StatusEffectBox();

private slots:
    void deleteButtonClicked();

public slots:
    void startTurn();
    void endTurn();

private:
    QLineEdit *statusNameEdit;
    QSpinBox *initiativeSpinBox;
    QPushButton *deleteButton;
    QVBoxLayout *layout;

    void deleteStatusEffect();
};

#endif // STATUSEFFECT_H
