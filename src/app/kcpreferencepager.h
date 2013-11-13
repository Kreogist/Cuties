#ifndef KCPREFERENCEPAGER_H
#define KCPREFERENCEPAGER_H

#include <QList>
#include <QWidget>
#include <QResizeEvent>

#include "kcpreferencesuperlist.h"

class KCPreferencePager : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferencePager(QWidget *parent = 0);
    void addSuperList(KCPreferenceSuperList *newSuperList);

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QList<KCPreferenceSuperList *> preferenceSuperLists;
};

#endif // KCPREFERENCEPAGER_H
