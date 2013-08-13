#include "kcisettinglistitemfoldertext.h"

kciSettingListItemFolderText::kciSettingListItemFolderText(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    //New Layout Sets.
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Clear Item Value;
    ItemValue="";

    //Set Caption.
    MainLayout->addSpacing(5);
    MainLayout->addWidget(Caption);
    MainLayout->addSpacing(3);

    //Set Value Displayer.
    ValueDisplayer=new QLabel(this);
    MainLayout->addWidget(ValueDisplayer);

    //Set Text Editor.
    ValueEditor=new QLineEdit(this);
    ValueEditor->setEnabled(false);
    ValueEditor->hide();
    MainLayout->addWidget(ValueEditor,1);
    MainLayout->addSpacing(5);
    MainLayout->addStretch();
}

void kciSettingListItemFolderText::setTextValue(const QString &NewTextValue)
{
    ItemValue=NewTextValue;
    ValueEditor->setText(ItemValue);
    ValueDisplayer->setText(ItemValue);
}

QString kciSettingListItemFolderText::getTextValue()
{
    return ItemValue;
}

void kciSettingListItemFolderText::mousePressEvent(QMouseEvent *e)
{
    ValueDisplayer->hide();
    ValueEditor->setEnabled(true);
    ValueEditor->show();
    e->accept();
}
