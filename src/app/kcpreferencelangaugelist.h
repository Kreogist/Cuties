#ifndef KCPREFERENCELANGAUGELIST_H
#define KCPREFERENCELANGAUGELIST_H

#include <QLabel>
#include <QWidget>
#include <QScrollArea>

#include "kclanguageconfigure.h"

class KCPreferenceLangaugeListItem : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceLangaugeListItem(QWidget *parent = 0);
    void setLanguageIcon(const QPixmap &languagePixmap);
    void setLanguageName(const QString &captionText);

signals:
    void requireChangeLanguage();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QLabel *languageIcon, *languageName;
};

class KCPreferenceLangaugeList : public QScrollArea
{
    Q_OBJECT
public:
    explicit KCPreferenceLangaugeList(QWidget *parent = 0);
    KCPreferenceLangaugeListItem *addLanguageItem(const QString &languageName,
                                                  const QPixmap &languageIcon);

signals:
    void requireChangeLanguage(int languageIndex);

public slots:

private:
    KCLanguageConfigure *instance;
    QList<KCPreferenceLangaugeListItem *> languageItems;
};

#endif // KCPREFERENCELANGAUGELIST_H
