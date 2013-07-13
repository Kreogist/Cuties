#include "kcidebugdock.h"

kciDebugDock::kciDebugDock(QWidget *parent) :
    QDockWidget(parent)
{
    //Set ObjectName
    setObjectName(tr("Debug Dock"));

    //Set Style
    setContentsMargins(0,0,0,0);
    QPalette pal=this->palette();
    pal.setBrush(QPalette::Window, QBrush(QColor(83,83,83)));
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    setPalette(pal);
    setWindowTitle(tr("Debug"));

    //New Central Widget
    CentralWidget=new kciDebugWidget(this);
    setWidget(CentralWidget);

}

kciDebugWidget::kciDebugWidget(QWidget *parent) :
    QWidget(parent)
{

    setContentsMargins(0,0,0,0);

    //Set New Layout.
    PanelLayout=new QGridLayout(this);
    PanelLayout->setContentsMargins(0,0,0,0);
    PanelLayout->setSpacing(0);
    setLayout(PanelLayout);

    //Create Buttons.
    createControlButtons();
}

void kciDebugWidget::createControlButtons()
{
    //Set New ToolButton.
    tblStartDebug=new QToolButton(this);
    tblStartDebug->setText(tr("Debug"));
    tblStopDebug=new QToolButton(this);
    tblStopDebug->setText(tr("Stop Debug"));
    tblRunToBreakPoint=new QToolButton(this);
    tblRunToBreakPoint->setText(tr("Run to Break Point"));

    tblNextStep=new QToolButton(this);
    tblNextStep->setText(tr("Next Step"));
    tblNextLine=new QToolButton(this);
    tblNextLine->setText(tr("Next Line"));
    tblIntoFunction=new QToolButton(this);
    tblIntoFunction->setText(tr("Go Into Function"));

    tblOutFunction=new QToolButton(this);
    tblOutFunction->setText(tr("Get Out Function"));
    tblContinue=new QToolButton(this);
    tblContinue->setText(tr("Continue Running"));

    //Set Layout.
    PanelLayout->addWidget(tblStartDebug,1,1);
    PanelLayout->addWidget(tblStopDebug,2,1);
    PanelLayout->addWidget(tblRunToBreakPoint,3,1);

    PanelLayout->addWidget(tblNextStep,1,2);
    PanelLayout->addWidget(tblNextLine,2,2);
    PanelLayout->addWidget(tblIntoFunction,3,2);

    PanelLayout->addWidget(tblOutFunction,1,3);
    PanelLayout->addWidget(tblContinue,2,3);

}
