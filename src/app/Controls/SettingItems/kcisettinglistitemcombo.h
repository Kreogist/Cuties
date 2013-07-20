#ifndef KCISETTINGLISTITEMCOMBO_H
#define KCISETTINGLISTITEMCOMBO_H

#include <QComboBox>
#include "kcisettinglistitembase.h"

class kciSettingListItemCombo : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemCombo(QWidget *parent = 0);
    void addListItem(const QString& ItemText);
    void clearList();

private:
    QComboBox *cboList;
};

#endif // KCISETTINGLISTITEMCOMBO_H
