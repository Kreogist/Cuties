#ifndef KCPREFERENCECONDITIONGROUP_H
#define KCPREFERENCECONDITIONGROUP_H

#include <QWidget>
#include <QVariant>

#include "kcpreferenceitembase.h"
#include "kcpreferencesuperlist.h"

class KCPreferenceConditionGroup : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceConditionGroup(KCPreferenceItemBase *condition,
                                        QVariant establishValue,
                                        QWidget *parent = 0);

signals:

public slots:

private slots:
    void conditionJudge(QVariant newItemValue);

private:
    KCPreferenceItemBase *conditionItem;
    QVBoxLayout *conditionLayout;
    QVariant conditionValue;

    KCPreferenceSuperList *normalList;
    KCPreferenceSuperList *conditionList;

    bool normalStatus;
};

#endif // KCPREFERENCECONDITIONGROUP_H
