#ifndef KCISETTINGLISTITEMBASE_H
#define KCISETTINGLISTITEMBASE_H

#include <QPalette>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QPropertyAnimation>

class kciSettingListItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit kciSettingListItemBase(QWidget *parent = 0);
    QLabel *Caption;
    
signals:

public slots:

private:
    QPalette pal;
};

#endif // KCISETTINGLISTITEMBASE_H
