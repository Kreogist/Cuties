#ifndef KCPREFERENCEITEMBOOLEANGROUP_H
#define KCPREFERENCEITEMBOOLEANGROUP_H

#include <QList>

#include "kcpreferenceitemboolean.h"

class KCPreferenceItemBooleanGroup : public KCPreferenceItemBoolean
{
    Q_OBJECT
public:
    explicit KCPreferenceItemBooleanGroup(QWidget *parent = 0);
    void addTrueValueGroupItem(KCPreferenceItemBase *newGroupItem);
    void addFalseValueGroupItem(KCPreferenceItemBase *newGroupItem);

signals:

public slots:

protected slots:
    void valueChangedEvent();

private:
    QList<KCPreferenceItemBase *> trueValueItemGroup;
    QList<KCPreferenceItemBase *> falseValueItemGroup;

};

#endif // KCPREFERENCEITEMBOOLEANGROUP_H
