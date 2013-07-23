#include "kcisettinglistitemcombo.h"

kciSettingListItemCombo::kciSettingListItemCombo(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    cboList=new QComboBox(this);
    cboList->setEnabled(false);
    cboList->hide();
    lblComboText=new QLabel(this);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(Caption);
    MainLayout->addSpacing(2);
    MainLayout->addWidget(cboList,1);
    MainLayout->addWidget(lblComboText,1);
    MainLayout->addSpacing(5);
    MainLayout->addStretch();

    connect(cboList,SIGNAL(currentIndexChanged(int)),
            this,SLOT(valueChangedEvent(int)));

    connect(this,SIGNAL(ItemGetFocus()),this,SLOT(focusGetEvent()));
    connect(this,SIGNAL(ItemLostFocus()),this,SLOT(focusLostEvent()));
}

void kciSettingListItemCombo::valueChangedEvent(int newValue)
{
    lblComboText->setText(cboList->itemText(newValue));
    emit ValueChanged();
}

void kciSettingListItemCombo::addListItem(const QString &ItemText)
{
    cboList->addItem(ItemText);
}

void kciSettingListItemCombo::clearList()
{
    cboList->clear();
}

int kciSettingListItemCombo::getCurrentItemIndex()
{
    return cboList->currentIndex();
}

void kciSettingListItemCombo::setCurrentItemIndex(int Index)
{
    cboList->setCurrentIndex(Index);
}

void kciSettingListItemCombo::focusGetEvent()
{
    lblComboText->hide();
    cboList->setEnabled(true);
    cboList->show();
}

void kciSettingListItemCombo::focusLostEvent()
{
    cboList->hide();
    cboList->setEnabled(false);
    lblComboText->show();
}
