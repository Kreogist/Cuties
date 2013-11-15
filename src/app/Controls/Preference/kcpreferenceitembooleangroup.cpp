#include "kcpreferenceitembooleangroup.h"

KCPreferenceItemBooleanGroup::KCPreferenceItemBooleanGroup(QWidget *parent) :
    KCPreferenceItemBoolean(parent)
{
    ;
}

void KCPreferenceItemBooleanGroup::addTrueValueGroupItem(KCPreferenceItemBase *newGroupItem)
{
    trueValueItemGroup.append(newGroupItem);
}

void KCPreferenceItemBooleanGroup::addFalseValueGroupItem(KCPreferenceItemBase *newGroupItem)
{
    falseValueItemGroup.append(newGroupItem);
}

void KCPreferenceItemBooleanGroup::valueChangedEvent()
{
    KCPreferenceItemBoolean::valueChangedEvent();
    if(getCurrentValue().toBool())
    {
        for(int i=0; i<falseValueItemGroup.count(); i++)
        {
            falseValueItemGroup.at(i)->animateHide();
        }
        for(int i=0; i<trueValueItemGroup.count(); i++)
        {
            trueValueItemGroup.at(i)->animateShow();
        }
    }
    else
    {
        for(int i=0; i<trueValueItemGroup.count(); i++)
        {
            trueValueItemGroup.at(i)->animateHide();
        }
        for(int i=0; i<falseValueItemGroup.count(); i++)
        {
            falseValueItemGroup.at(i)->animateShow();
        }
    }
}

