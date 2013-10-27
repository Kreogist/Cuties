#include "kcsettinglistitemcombo.h"

KCSettingListItemCombo::KCSettingListItemCombo(QWidget *parent) :
    KCSettingListItemBase(parent)
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
    MainLayout->addWidget(captionText);
    MainLayout->addSpacing(2);
    MainLayout->addWidget(cboList,1);
    MainLayout->addWidget(lblComboText,1);
    MainLayout->addSpacing(5);
    MainLayout->addStretch();

    connect(cboList,SIGNAL(currentIndexChanged(int)),
            this,SLOT(valueChangedEvent(int)));

    connect(this,SIGNAL(itemGetFocus()),this,SLOT(focusGetEvent()));
    connect(this,SIGNAL(itemLostFocus()),this,SLOT(focusLostEvent()));
}

void KCSettingListItemCombo::valueChangedEvent(int newValue)
{
    lblComboText->setText(cboList->itemText(newValue));
    emit valueChanged();
}

void KCSettingListItemCombo::addListItem(const QString &ItemText)
{
    cboList->addItem(ItemText);
}

void KCSettingListItemCombo::clearList()
{
    cboList->clear();
}

int KCSettingListItemCombo::getValue()
{
    return cboList->currentIndex();
}

void KCSettingListItemCombo::setValue(int Index)
{
    cboList->setCurrentIndex(Index);
}

void KCSettingListItemCombo::focusGetEvent()
{
    lblComboText->hide();
    cboList->setEnabled(true);
    cboList->show();
}

void KCSettingListItemCombo::focusLostEvent()
{
    cboList->hide();
    cboList->setEnabled(false);
    lblComboText->show();
}
