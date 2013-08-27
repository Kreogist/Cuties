#include "kcieditorconfigure.h"

kciEditorConfigure* kciEditorConfigure::instance=nullptr;

kciEditorConfigure::kciEditorConfigure()
{
    isUsingBlankInsteadTab=true;
    tabWidth=4;
}

kciEditorConfigure* kciEditorConfigure::getInstance()
{
    return instance==nullptr?instance=new kciEditorConfigure:instance;
}

void kciEditorConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Editor");
    tabWidth=settings.value("TabWidth",tabWidth).toInt();
    settings.endGroup();
}

void kciEditorConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(), QSettings::IniFormat);
    settings.beginGroup("Editor");
    settings.setValue("TabWidth",tabWidth);
    settings.endGroup();
}

bool kciEditorConfigure::usingBlankInsteadTab() const
{
    return isUsingBlankInsteadTab;
}

void kciEditorConfigure::setUsingBlankInsteadTab(bool enabled)
{
    isUsingBlankInsteadTab=enabled;
}

int kciEditorConfigure::getTabWidth() const
{
    return tabWidth;
}

void kciEditorConfigure::setTabWidth(const int &width)
{
    tabWidth=width;
}
