#ifndef KCSETTINGLISTITEMBOOLEAN_H
#define KCSETTINGLISTITEMBOOLEAN_H

#include <QLabel>
#include <QPixmap>
#include <QTimeLine>
#include <QHBoxLayout>

#include "kcsettinglistitembase.h"

class KCSettingListItemBooleanSwitcher : public QLabel
{
    Q_OBJECT
public:
    explicit KCSettingListItemBooleanSwitcher(QWidget *parent = 0);
    void setValue(bool NewValue);
    bool getValue();
    void setTheValue(bool NewValue);

signals:
    void valueChanged();

private:
    bool switcherValue;
    void setImage(bool NewValue);
    QPixmap *switcherPixmapTrue;
    QPixmap *switcherPixmapFalse;
};

class KCSettingListItemBoolean : public KCSettingListItemBase
{
    Q_OBJECT
public:
    explicit KCSettingListItemBoolean(QWidget *parent = 0);
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
    QHBoxLayout *mainLayout;
    QString enabledText, disabledText;
    KCSettingListItemBooleanSwitcher *valueSetter;
    bool itemValue;
    QTimeLine *ChangedAnime;
    QTimeLine *animeMouseLeaveFadeOut;
    QPalette pal;

    void refreshCaption();

    bool animeChangedBugFixed;
};

#endif // KCSETTINGLISTITEMBOOLEAN_H
