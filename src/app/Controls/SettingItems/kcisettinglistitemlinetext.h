#ifndef KCISETTINGLISTITEMLINETEXT_H
#define KCISETTINGLISTITEMLINETEXT_H

#include <QLineEdit>
#include <QHBoxLayout>

#include "kcisettinglistitembase.h"

class kciSettingListItemLineText : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemLineText(QWidget *parent = 0);
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

#endif // KCISETTINGLISTITEMLINETEXT_H
