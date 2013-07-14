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

    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Create Buttons.
    createControlButtons();
}

void kciDebugWidget::createControlButtons()
{
    //Set New ToolButton.
    tblStartDebug=new QToolButton(this);
    tblStartDebug->setText(tr("Debug"));
    tblStartDebug->setFixedSize(110,24);
    tblStopDebug=new QToolButton(this);
    tblStopDebug->setText(tr("Stop Debug"));
    tblStopDebug->setFixedSize(110,24);
    tblRunToCursor=new QToolButton(this);
    tblRunToCursor->setText(tr("Run To Cursor"));
    tblRunToCursor->setFixedSize(110,24);

    tblNextStep=new QToolButton(this);
    tblNextStep->setText(tr("Next Step"));
    tblNextStep->setFixedSize(110,24);
    tblNextLine=new QToolButton(this);
    tblNextLine->setText(tr("Next Line"));
    tblNextLine->setFixedSize(110,24);
    tblIntoFunction=new QToolButton(this);
    tblIntoFunction->setText(tr("Go Into Function"));
    tblIntoFunction->setFixedSize(110,24);

    tblOutFunction=new QToolButton(this);
    tblOutFunction->setText(tr("Get Out Function"));
    tblOutFunction->setFixedSize(110,24);
    tblContinue=new QToolButton(this);
    tblContinue->setText(tr("Continue"));
    tblContinue->setFixedSize(110,24);

    //Set Layout.
    LeftButtonVList1=new QVBoxLayout();
    LeftButtonVList2=new QVBoxLayout();
    LeftButtonVList3=new QVBoxLayout();
    LeftButtonVList1->addWidget(tblStartDebug);
    LeftButtonVList1->addWidget(tblStopDebug);
    LeftButtonVList1->addWidget(tblRunToCursor);
    LeftButtonVList1->addStretch();

    LeftButtonVList2->addWidget(tblNextStep);
    LeftButtonVList2->addWidget(tblNextLine);
    LeftButtonVList2->addWidget(tblIntoFunction);
    LeftButtonVList2->addStretch();

    LeftButtonVList3->addWidget(tblOutFunction);
    LeftButtonVList3->addWidget(tblContinue);
    LeftButtonVList3->addStretch();

    MainLayout->addLayout(LeftButtonVList1);
    MainLayout->addLayout(LeftButtonVList2);
    MainLayout->addLayout(LeftButtonVList3);

    GDBInfo=new QPlainTextEdit(this);
    MainLayout->addWidget(GDBInfo);

}
