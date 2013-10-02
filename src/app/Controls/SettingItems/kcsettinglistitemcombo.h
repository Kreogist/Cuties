#ifndef KCSETTINGLISTITEMCOMBO_H
#define KCSETTINGLISTITEMCOMBO_H

#include <QComboBox>
#include "kcsettinglistitembase.h"

class KCSettingListItemCombo : public KCSettingListItemBase
{
    Q_OBJECT
public:
    explicit KCSettingListItemCombo(QWidget *parent = 0);
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

#endif // KCSETTINGLISTITEMCOMBO_H
