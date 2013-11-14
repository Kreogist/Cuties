#include <QDebug>

#include "kcpreferenceitemboolean.h"

KCPreferenceItemBoolean::KCPreferenceItemBoolean(QWidget *parent) :
    KCPreferenceItemBase(parent)
{
    retranslate();

    enabledColor=QColor();
    disabledColor=QColor();

    //Set Edit Mode Layout
    editLayout=new QVBoxLayout(this);
    editLayout->setContentsMargins(5,5,5,5);
    editLayout->setSpacing(2);
    setLayout(editLayout);

    booleanLayout=new QHBoxLayout();
    booleanLayout->setContentsMargins(0,0,0,0);
    booleanLayout->setSpacing(0);

    booleanCaption=new QLabel(this);
    booleanLayout->addWidget(booleanCaption);
    booleanLayout->addSpacing(2);
    booleanLayout->addWidget(valueDisplayer);
    booleanLayout->addWidget(originalValueDisplayer);
    booleanLayout->addStretch();

    editLayout->addLayout(booleanLayout);

    booleanData=new QCheckBox(this);
    booleanData->setText(booleanDataText);
    booleanData->setVisible(false);
    booleanData->setEnabled(false);
    editLayout->addWidget(booleanData);
    editLayout->addStretch();

    setExpandFinishedHeight(48);
}

KCPreferenceItemBoolean::~KCPreferenceItemBoolean()
{
    booleanLayout->deleteLater();
}

void KCPreferenceItemBoolean::setOriginalValue(const QVariant &value)
{
    booleanData->setChecked(value.toBool());
    valueDisplayer->setText(booleanStatusText[int(value.toBool())]);
    KCPreferenceItemBase::setOriginalValue(value);
}

QString KCPreferenceItemBoolean::getBooleanText() const
{
    return booleanText;
}

void KCPreferenceItemBoolean::setBooleanText(const QString &value)
{
    booleanText = value;
}

void KCPreferenceItemBoolean::setBooleanCaptionText(const QString &value)
{
    booleanCaption->setText(value);
}

void KCPreferenceItemBoolean::retranslate()
{
    booleanDataText=tr("Enabled this feature.");
    booleanStatusText[1]=tr("Enabled");
    booleanStatusText[0]=tr("Disable");
}

void KCPreferenceItemBoolean::retranslateAndSet()
{
    retranslate();
    booleanData->setText(booleanDataText);
}

void KCPreferenceItemBoolean::showEditWidget()
{
    booleanData->setVisible(true);
    booleanData->setEnabled(true);
}

void KCPreferenceItemBoolean::hideEditWidget()
{
    booleanData->setVisible(false);
    booleanData->setEnabled(false);
}

QVariant KCPreferenceItemBoolean::getUserNewValue()
{
    return booleanData->isChecked();
}

void KCPreferenceItemBoolean::refreshValueDisplay()
{
    valueDisplayer->setText(booleanStatusText[int(booleanData->isChecked())]);
    if(booleanData->isChecked() == originalValue.toBool())
    {
        setOriginalDisplayVisible(false);
        return;
    }
    originalValueDisplayer->setText(" (" +
                                    originalValueIs +
                                    booleanStatusText[int(originalValue.toBool())] +
                                    ")");
    setOriginalDisplayVisible(true)
}

void KCPreferenceItemBoolean::refreshBooleanText()
{
    booleanData->setText(booleanText);
}
