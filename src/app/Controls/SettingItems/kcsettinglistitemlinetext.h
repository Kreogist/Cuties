#ifndef KCSETTINGLISTITEMLINETEXT_H
#define KCSETTINGLISTITEMLINETEXT_H

#include <QHBoxLayout>

#include "kcsettingcontrollineedit.h"
#include "kcsettinglistitembase.h"

class KCSettingListItemLineText : public KCSettingListItemBase
{
    Q_OBJECT
public:
    explicit KCSettingListItemLineText(QWidget *parent = 0);
    void setValue(const QString &NewTextValue);
    QString getValue();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QHBoxLayout *mainLayout;
    QLabel *valueDisplayer;
    KCSettingControlLineEdit *valueEditor;
    QString itemValue;
};

#endif // KCSETTINGLISTITEMLINETEXT_H
