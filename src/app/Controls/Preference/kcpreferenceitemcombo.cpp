#include <QDebug>

#include "kcpreferenceitemcombo.h"

KCPreferenceItemCombo::KCPreferenceItemCombo(QWidget *parent) :
    KCPreferenceItemBase(parent)
{
    //Set Edit Mode Layout
    editLayout=new QVBoxLayout(this);
    editLayout->setContentsMargins(5,5,5,5);
    editLayout->setSpacing(2);
    setLayout(editLayout);

    comboLayout=new QHBoxLayout();
    comboLayout->setContentsMargins(0,0,0,0);
    comboLayout->setSpacing(0);

    comboCaption=new QLabel(this);
    comboLayout->addWidget(comboCaption);
    comboLayout->addSpacing(2);
    comboLayout->addWidget(valueDisplayer);
    comboLayout->addWidget(originalValueDisplayer);
    comboLayout->addStretch();

    editLayout->addLayout(comboLayout);

    comboData=new QComboBox(this);
    setEditWidgetStatus(false);
    editLayout->addWidget(comboData);
    editLayout->addStretch();

    setExpandFinishedHeight(52);
}

KCPreferenceItemCombo::~KCPreferenceItemCombo()
{
    comboLayout->deleteLater();
}

void KCPreferenceItemCombo::refreshComboText()
{
    comboData->clear();
    for(int i=0; i<comboTextList.count(); i++)
    {
        comboData->addItem(comboTextList.at(i));
    }
}

QList<QString> KCPreferenceItemCombo::getComboTextList() const
{
    return comboTextList;
}

void KCPreferenceItemCombo::setComboTextList(const QList<QString> &value)
{
    comboTextList = value;
}

void KCPreferenceItemCombo::setComboCaptionText(const QString &value)
{
    comboCaption->setText(value);
}

void KCPreferenceItemCombo::setEditWidgetStatus(bool states)
{
    comboData->setVisible(states);
    comboData->setEnabled(states);
}

QVariant KCPreferenceItemCombo::getUserNewValue()
{
    return comboData->currentIndex();
}

void KCPreferenceItemCombo::refreshValueDisplay()
{
    valueDisplayer->setText(comboData->currentText());
    if(comboData->currentIndex() == originalValue.toInt())
    {
        setOriginalDisplayVisible(false);
        return;
    }
    originalValueDisplayer->setText(QString(" (" +
                                    originalValueIs +
                                    comboTextList.at(originalValue.toInt()) +
                                    ")"));
    setOriginalDisplayVisible(true);
}

void KCPreferenceItemCombo::setOriginalValue(const QVariant &value)
{
    comboData->setCurrentIndex(value.toInt());
    valueDisplayer->setText(comboTextList.at(value.toInt()));
    KCPreferenceItemBase::setOriginalValue(value);
}
