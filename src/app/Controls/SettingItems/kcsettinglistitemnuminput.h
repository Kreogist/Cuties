#ifndef KCSETTINGLISTITEMNUMINPUT_H
#define KCSETTINGLISTITEMNUMINPUT_H

#include <QSpinBox>
#include <QSlider>
#include <QDial>

#include "kcsettinglistitembase.h"

class KCSettingListItemNumInput : public KCSettingListItemBase
{
    Q_OBJECT
public:
    explicit KCSettingListItemNumInput(QWidget *parent = 0);

    int getValue() const;
    int getMaxValue() const;
    void setMaxValue(int NewValue);
    int getMinValue() const;
    void setMinValue(int NewValue);

public slots:
    void setValue(int NewValue);

signals:

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QHBoxLayout *MainLayout;
    QLabel *ValueDisplayer;
    int value;
    int MinValue=0, MaxValue=100;
    QSpinBox *ValueSpin;
    QDial *ValueDial;
    QSlider *ValueSlider;
};

#endif // KCSETTINGLISTITEMNUMINPUT_H
