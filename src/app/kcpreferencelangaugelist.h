#ifndef KCPREFERENCELANGAUGELIST_H
#define KCPREFERENCELANGAUGELIST_H

#include <QWidget>

class KCPreferenceLangaugeListItem : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceLangaugeListItem(QWidget *parent = 0);

private:
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
