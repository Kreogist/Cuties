#ifndef KCISETTINGLISTITEMCOMBO_H
#define KCISETTINGLISTITEMCOMBO_H

#include <QComboBox>
#include "kcisettinglistitembase.h"

class kciSettingListItemCombo : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemCombo(QWidget *parent = 0);
    void addListItem(const QString &ItemText);
    void clearList();
    void setValue(int Index);
    int getValue();

private slots:
    void valueChangedEvent(int newValue);
    void focusGetEvent();
    void focusLostEvent();

private:
    QComboBox *cboList;
    QHBoxLayout *MainLayout;
    QLabel *lblComboText;
};

#endif // KCISETTINGLISTITEMCOMBO_H
