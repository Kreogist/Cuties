#ifndef KCISETTINGLISTITEMBOOLEAN_H
#define KCISETTINGLISTITEMBOOLEAN_H

#include <QLabel>
#include <QPixmap>
#include <QTimeLine>
#include <QHBoxLayout>

#include "kcisettinglistitembase.h"

class kciSettingListItemBooleanSwitcher : public QLabel
{
    Q_OBJECT
public:
    explicit kciSettingListItemBooleanSwitcher(QWidget *parent = 0);
    void setValue(bool NewValue);
    bool getValue();
    void setTheValue(bool NewValue);

signals:
    void valueChanged();

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
    void setEnabledText(const QString &Text);
    QString getEnabledText();
    void setDisabledText(const QString &Text);
    QString getDisabledText();
    void setValue(bool NewValue);
    void setTheValue(bool NewValue);
    bool getValue();

signals:

public slots:

private slots:
    void valueChangedEvent();
    void valueChangedAnimeEvent();
    void setValueChangedAlpha(int alpha);

protected:
    void mousePressEvent(QMouseEvent *e);
    void leaveEvent(QEvent *e);
    void enterEvent(QEvent *e);

private:
    QHBoxLayout *MainLayout;
    QString strEnabledInfo, strDisabledInfo;
    kciSettingListItemBooleanSwitcher *ValueSetter;
    bool ItemValue, blnEditMode;
    QTimeLine *ChangedAnime;
    QTimeLine *animeMouseLeaveFadeOut;
    QPalette pal;

    void refreshCaption();

    bool animeChangedBugFixed;
};

#endif // KCISETTINGLISTITEMBOOLEAN_H
