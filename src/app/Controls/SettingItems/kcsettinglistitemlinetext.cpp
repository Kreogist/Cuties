#include "kcsettinglistitemlinetext.h"

KCSettingListItemLineText::KCSettingListItemLineText(QWidget *parent) :
    KCSettingListItemBase(parent)
{
    //New Layout Sets.
    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Clear Item Value;
    itemValue="";

    //Set Caption.
    mainLayout->addSpacing(5);
    mainLayout->addWidget(captionText);
    mainLayout->addSpacing(3);

    //Set Value Displayer.
    valueDisplayer=new QLabel(this);
    mainLayout->addWidget(valueDisplayer);

    //Set Text Editor.
    valueEditor=new KCSettingControlLineEdit(this);
    valueEditor->setEnabled(false);
    valueEditor->hide();
    mainLayout->addWidget(valueEditor,1);
    mainLayout->addSpacing(5);
    mainLayout->addStretch();
}

void KCSettingListItemLineText::setValue(const QString &NewTextValue)
{
    itemValue=NewTextValue;
    valueEditor->setText(itemValue);
    valueDisplayer->setText(itemValue);
}

QString KCSettingListItemLineText::getValue()
{
    return itemValue;
}

void KCSettingListItemLineText::mousePressEvent(QMouseEvent *e)
{
    valueDisplayer->hide();
    valueEditor->setEnabled(true);
    valueEditor->show();
    e->accept();
}
