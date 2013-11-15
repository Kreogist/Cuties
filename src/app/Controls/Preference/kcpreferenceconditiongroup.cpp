#include "kcpreferenceconditiongroup.h"

KCPreferenceConditionGroup::KCPreferenceConditionGroup(KCPreferenceItemBase *condition,
                                                       QVariant establishValue,
                                                       QWidget *parent) :
    QWidget(parent)
{
    //Set condition values
    conditionItem=condition;
    conditionValue=establishValue;
    normalStatus=true;

    //Set group properties
    setContentsMargins(0,0,0,0);

    //Set condition layout
    conditionLayout=new QVBoxLayout(this);
    conditionLayout->setContentsMargins(0,0,0,0);
    conditionLayout->setSpacing(0);
    setLayout(conditionLayout);
}

void KCPreferenceConditionGroup::conditionJudge(QVariant newItemValue)
{
    if(newItemValue==conditionValue)
    {
        if(normalStatus)
        {
            //Condition established animation happend
            ;
        }
    }
    else
    {
        if(!normalStatus)
        {
            //Normal animation happend
            ;
        }
    }
}


