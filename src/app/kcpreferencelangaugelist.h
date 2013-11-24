#ifndef KCPREFERENCELANGAUGELIST_H
#define KCPREFERENCELANGAUGELIST_H

#include <QLabel>
#include <QWidget>

class KCPreferenceLangaugeListItem : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceLangaugeListItem(QWidget *parent = 0);
    void setLanguageIcon(const QString &iconPath);
    void setLanguageName(const QString &captionText);

private:
    QLabel *languageIcon, *languageName;
};

class KCPreferenceLangaugeList : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceLangaugeList(QWidget *parent = 0);

signals:

public slots:

};

#endif // KCPREFERENCELANGAUGELIST_H
