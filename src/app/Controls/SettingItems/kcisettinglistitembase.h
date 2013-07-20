#ifndef KCISETTINGLISTITEMBASE_H
#define KCISETTINGLISTITEMBASE_H

#include <QPalette>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>

class kciSettingListItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit kciSettingListItemBase(QWidget *parent = 0);
    QLabel *Caption;
    
signals:
    
public slots:

private:
};

#endif // KCISETTINGLISTITEMBASE_H
