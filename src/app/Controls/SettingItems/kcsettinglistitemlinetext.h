#ifndef KCSETTINGLISTITEMLINETEXT_H
#define KCSETTINGLISTITEMLINETEXT_H

#include <QLineEdit>
#include <QHBoxLayout>

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
    QHBoxLayout *MainLayout;
    QLabel *ValueDisplayer;
    QLineEdit *ValueEditor;
    QString ItemValue;
};

#endif // KCSETTINGLISTITEMLINETEXT_H
