#include "kcicontrolcenter.h"

kciControlCenterBanner::kciControlCenterBanner(QWidget *parent):
    QWidget(parent)
{
    lblBannerTitle=new QLabel(this);
    lblBannerTitle->setText(tr("Cuties Control Center"));
}

ccGeneral::ccGeneral(QWidget *parent):
    QWidget(parent)
{

}

ccEditor::ccEditor(QWidget *parent):
    QWidget(parent)
{

}

ccCompiler::ccCompiler(QWidget *parent):
    QWidget(parent)
{

}

ccDebugger::ccDebugger(QWidget *parent):
    QWidget(parent)
{

}

ccFileAssociation::ccFileAssociation(QWidget *parent):
    QWidget(parent)
{

}

ccLanguage::ccLanguage(QWidget *parent):
    QWidget(parent)
{

}

kciControlCenter::kciControlCenter(QWidget *parent) :
    QWidget(parent)
{
    setFont(QFont(QString("Hiragino Sans GB W3")));

    //Set Whole Layout
    WholeTitleBarSplit=new QVBoxLayout(this);
    setLayout(WholeTitleBarSplit);

    //Set Banner
    ccBanner=new kciControlCenterBanner(this);
    WholeTitleBarSplit->addWidget(ccBanner);

    //Set Tabs
    ccMainTabs=new QStackedWidget(this);
    tabGeneral=new ccGeneral(this);
    tabEditor=new ccEditor(this);
    tabCompiler=new ccCompiler(this);
    tabDebugger=new ccDebugger(this);
    tabFileAssociation=new ccFileAssociation(this);
    tabLanguage=new ccLanguage(this);

    WholeTitleBarSplit->addWidget(tabGeneral);
    WholeTitleBarSplit->addWidget(tabEditor);
    WholeTitleBarSplit->addWidget(tabCompiler);
    WholeTitleBarSplit->addWidget(tabDebugger);
    WholeTitleBarSplit->addWidget(tabFileAssociation);
    WholeTitleBarSplit->addWidget(tabLanguage);
}
