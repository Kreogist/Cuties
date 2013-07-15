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

    MainWidgetLayout=new QVBoxLayout(this);
    MainWidgetLayout->setContentsMargins(0,0,0,0);
    MainWidgetLayout->setSpacing(0);
    setLayout(MainWidgetLayout);

    //Create Buttons.
    createToolBar();

    //Set Sub Layout.
    MainShownLayout=new QHBoxLayout();
    MainShownLayout->setContentsMargins(0,0,0,0);
    MainShownLayout->setSpacing(5);
    MainWidgetLayout->addLayout(MainShownLayout);

    //Add Widgets to Sub Layout.
    ControlPanel=new QVBoxLayout();
    ControlPanel->setContentsMargins(0,0,0,0);
    ControlPanel->setSpacing(0);
    MainShownLayout->addLayout(ControlPanel);
    createControlButtons();

    //Add Widget to GDB Layout.
    createGDBConversation();

    //Create Watch TreeView.
    watchView=new QTreeView(this);
    watchResult=new QStandardItemModel();
    watchView->setHeaderHidden(true);
    watchView->setModel(watchResult);
    LocalValueView=new QStandardItem(QString(tr("Local Value")));
    LocalValueView->setEditable(false);
    watchResult->appendRow(LocalValueView);
    CustomValueView=new QStandardItem(QString(tr("Custom Value")));
    CustomValueView->setEditable(false);
    watchResult->appendRow(CustomValueView);
    MainShownLayout->addWidget(watchView);
}

void kciDebugWidget::createGDBConversation()
{
    GDBMainLayout=new QVBoxLayout();
    GDBMainLayout->setContentsMargins(0,0,0,0);
    GDBMainLayout->setSpacing(5);
    MainShownLayout->addLayout(GDBMainLayout);
    //Create Input Box.
    InputToGDB=new QHBoxLayout();
    InputToGDB->setContentsMargins(0,0,0,0);
    InputToGDB->setSpacing(2);
    QLabel *InputTag=new QLabel(this);
    InputTag->setText(tr("Send command to GDB:"));
    InputToGDB->addWidget(InputTag);
    GDBCmd=new QComboBox(this);
    GDBCmd->setEditable(true);
    InputToGDB->addWidget(GDBCmd,1);
    GDBMainLayout->addLayout(InputToGDB);
    GDBInfo=new QPlainTextEdit(this);
    GDBMainLayout->addWidget(GDBInfo,1);
}

void kciDebugWidget::createToolBar()
{
    QString tmpToolTip;
    //Init ToolBar.
    DebugToolBar=new QToolBar(this);
    DebugToolBar->setContentsMargins(0,0,0,0);
    //Set New ToolButton.
    //Set Debug Main Control Buttons.
    tblStartDebug=new QToolButton(this);
    tblStartDebug->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/StartDebug.png"));
    tblStartDebug->setFixedSize(26,26);
    tmpToolTip=tr("Start debugging.");
    tblStartDebug->setToolTip(tmpToolTip);
    DebugToolBar->addWidget(tblStartDebug);
    tblStopDebug=new QToolButton(this);
    tblStopDebug->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/StopDebug.png"));
    tblStopDebug->setFixedSize(26,26);
    DebugToolBar->addWidget(tblStopDebug);
    DebugToolBar->addSeparator();
    //Set Debug Control Buttons.
    tblRunToCursor=new QToolButton(this);
    tblRunToCursor->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/RunToCursor.png"));
    tblRunToCursor->setFixedSize(26,26);
    DebugToolBar->addWidget(tblRunToCursor);
    DebugToolBar->addSeparator();
    //Set Debug Watch Buttons.
    tblAddWatch=new QToolButton(this);
    tblAddWatch->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/AddWatch.png"));
    tblAddWatch->setFixedSize(26,26);
    DebugToolBar->addWidget(tblAddWatch);
    tblRemoveWatch=new QToolButton(this);
    tblRemoveWatch->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/RemoveWatch.png"));
    tblRemoveWatch->setFixedSize(26,26);
    DebugToolBar->addWidget(tblRemoveWatch);
    tblEditWatch=new QToolButton(this);
    tblEditWatch->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/ModifyWatch.png"));
    tblEditWatch->setFixedSize(26,26);
    DebugToolBar->addWidget(tblEditWatch);

    MainWidgetLayout->addWidget(DebugToolBar);
}

void kciDebugWidget::createControlButtons()
{
    //Set New ToolButton.
    tblNextStep=new QToolButton(this);
    tblNextStep->setText(QString(" " + tr("Next Step")));
    tblNextStep->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/NextStep.png"));
    tblNextStep->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblNextStep->setFixedSize(140,30);
    ControlPanel->addWidget(tblNextStep);
    tblNextLine=new QToolButton(this);
    tblNextLine->setText(QString(" " + tr("Next Line")));
    tblNextLine->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/NextLine.png"));
    tblNextLine->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblNextLine->setFixedSize(140,30);
    ControlPanel->addWidget(tblNextLine);
    tblIntoFunction=new QToolButton(this);
    tblIntoFunction->setText(QString(" " + tr("Go Into Function")));
    tblIntoFunction->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/GetIntoFuntion.png"));
    tblIntoFunction->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblIntoFunction->setFixedSize(140,30);
    ControlPanel->addWidget(tblIntoFunction);
    tblOutFunction=new QToolButton(this);
    tblOutFunction->setText(QString(" " + tr("Get Out Function")));
    tblOutFunction->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/GetOutOfFuntion.png"));
    tblOutFunction->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblOutFunction->setFixedSize(140,30);
    ControlPanel->addWidget(tblOutFunction);
    ControlPanel->addSpacing(3);
    tblContinue=new QToolButton(this);
    tblContinue->setText(QString(" " + tr("Continue")));
    tblContinue->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/Continue.png"));
    tblContinue->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblContinue->setFixedSize(140,30);
    ControlPanel->addWidget(tblContinue);
    ControlPanel->addStretch();
}
