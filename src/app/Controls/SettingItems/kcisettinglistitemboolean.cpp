#include "kcisettinglistitemboolean.h"

kciSettingListItemBooleanSwitcher::kciSettingListItemBooleanSwitcher(QWidget *parent) :
    QLabel(parent)
{
    //Cache Image Control.
    pxpTrue=new QPixmap(":/Controls/image/Controls/BooleanTrue.png");
    pxpFalse=new QPixmap(":/Controls/image/Controls/BooleanFalse.png");
    //Set Default Value.
    setValue(false);
}

void kciSettingListItemBooleanSwitcher::setValue(bool NewValue)
{
    Value=NewValue;
    setImage(Value);
}

void kciSettingListItemBooleanSwitcher::setImage(bool NewValue)
{
    if(NewValue)
    {
        setPixmap(*pxpTrue);
    }
    else
    {
        setPixmap(*pxpFalse);
    }
    emit valueChanged();
}

bool kciSettingListItemBooleanSwitcher::getValue()
{
    return Value;
}

void kciSettingListItemBooleanSwitcher::mouseReleaseEvent(QMouseEvent *e)
{
    setValue(!getValue());
    e->accept();
}

kciSettingListItemBoolean::kciSettingListItemBoolean(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    //Set Layout.
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);
    //Set Widget.
    MainLayout->addWidget(Caption);

    //Set Value Setter.
    ValueSetter=new kciSettingListItemBooleanSwitcher(this);
    MainLayout->addWidget(ValueSetter);
}

void kciSettingListItemBoolean::valueChangedEvent()
{
    refreshCaption();
}

void kciSettingListItemBoolean::refreshCaption()
{
    if(ValueSetter->getValue())
    {
        Caption->setText(strEnabledInfo);
    }
    else
    {
        Caption->setText(strDisabledInfo);
    }
}

void kciSettingListItemBoolean::setEnabledText(const QString &Text)
{
    strEnabledInfo=Text;
    refreshCaption();
}

QString kciSettingListItemBoolean::getEnabledText()
{
    return strEnabledInfo;
}

void kciSettingListItemBoolean::setDisabledText(const QString &Text)
{
    strDisabledInfo=Text;
    refreshCaption();
}

QString kciSettingListItemBoolean::getDisabledText()
{
    return strDisabledInfo;
}

bool kciSettingListItemBoolean::getItemValue()
{
    return ValueSetter->getValue();
}
