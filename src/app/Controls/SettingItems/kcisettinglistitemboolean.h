#ifndef KCISETTINGLISTITEMBOOLEAN_H
#define KCISETTINGLISTITEMBOOLEAN_H

#include <QHBoxLayout>

#include "kcisettinglistitembase.h"

class kciSettingListItemBoolean : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemBoolean(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QHBoxLayout *MainLayout;
    
};

#endif // KCISETTINGLISTITEMBOOLEAN_H
