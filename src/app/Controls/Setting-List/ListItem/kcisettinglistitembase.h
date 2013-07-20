#ifndef KCISETTINGLISTITEMBASE_H
#define KCISETTINGLISTITEMBASE_H

#include <QPalette>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class kciSettingListItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit kciSettingListItemBase(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QHBoxLayout *MainLayout;
    
};

#endif // KCISETTINGLISTITEMBASE_H
