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
    void setTextValue(const QString& NewTextValue);
    QString getTextValue();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QLineEdit *ValueEditor;
    QHBoxLayout *MainLayout;
    QLabel *ValueDisplayer;
    QString ItemValue;
};

#endif // KCISETTINGLISTITEMLINETEXT_H
