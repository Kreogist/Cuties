#ifndef KCISETTINGLISTITEMBOOLEAN_H
#define KCISETTINGLISTITEMBOOLEAN_H

#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>

#include "kcisettinglistitembase.h"

class kciSettingListItemBooleanSwitcher : public QLabel
{
    Q_OBJECT
public:
    explicit kciSettingListItemBooleanSwitcher(QWidget *parent = 0);
    void setValue(bool NewValue);
    bool getValue();

signals:
    void valueChanged();

protected:
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool Value;
    void setImage(bool NewValue);
    QPixmap *pxpTrue, *pxpFalse;
};

class kciSettingListItemBoolean : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemBoolean(QWidget *parent = 0);
    void setEnabledText(const QString& Text);
    QString getEnabledText();
    void setDisabledText(const QString& Text);
    QString getDisabledText();
    bool getItemValue();

signals:
    
public slots:

private slots:
    void valueChangedEvent();

private:
    QHBoxLayout *MainLayout;
    QString strEnabledInfo, strDisabledInfo;
    kciSettingListItemBooleanSwitcher *ValueSetter;
    bool ItemValue;

    void refreshCaption();

};

#endif // KCISETTINGLISTITEMBOOLEAN_H
