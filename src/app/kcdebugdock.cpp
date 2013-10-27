#include "kcdebugdock.h"

KCDebugDock::KCDebugDock(QWidget *parent) :
    QDockWidget(parent)
{
    //Set ObjectName
    setObjectName("Debug Dock");

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
    setWindowTitle(" " + tr("Debug") + " ");

    //New Central Widget
    CentralWidget=new KCDebugWidget(this);
    setWidget(CentralWidget);
}

KCDebugWidget::KCDebugWidget(QWidget *parent) :
    QWidget(parent)
{   
    m_parent=qobject_cast<KCDebugDock *>(parent);
    setContentsMargins(0,0,0,0);

    //Main Layout.
    MainWidgetLayout=new QHBoxLayout;
    MainWidgetLayout->setContentsMargins(0,0,0,0);
    //MainWidgetLayout->setSpacing(0);
    setLayout(MainWidgetLayout);

    //Add Widgets to Sub Layout.
    createControlPanel();
    MainWidgetLayout->addLayout(ControlPanel);

    //Add Widget to GDB Layout.
    createGDBConversation();
    gdbInstance=NULL;
}

KCDebugWidget::~KCDebugWidget()
{
    MainWidgetLayout->deleteLater();
    ControlPanel->deleteLater();
    InputToGDB->deleteLater();
    GDBMainLayout->deleteLater();
}

void KCDebugWidget::createGDBConversation()
{
    GDBMainLayout=new QVBoxLayout;
    GDBMainLayout->setContentsMargins(0,0,0,0);
    GDBMainLayout->setSpacing(5);
    //Create Input Box.
    InputToGDB=new QHBoxLayout;
    InputToGDB->setContentsMargins(0,0,0,0);
    InputToGDB->setSpacing(2);
    QLabel *InputTag=new QLabel(this);
    InputTag->setText(tr("Send command to GDB:"));
    InputToGDB->addWidget(InputTag);

    GDBCmd=new QComboBox(this);
    GDBCmd->setEditable(true);
    connect(GDBCmd,SIGNAL(activated(QString)),
            this,SLOT(onGDBCmdEditFinished(QString)));

    InputToGDB->addWidget(GDBCmd,1);
    GDBMainLayout->addLayout(InputToGDB);
    GDBInfo=new KCPlainTextBrowser(this);
    GDBMainLayout->addWidget(GDBInfo,1);

    //Add To MainLayout.
    MainWidgetLayout->addLayout(GDBMainLayout,1);
}

void KCDebugWidget::createToolBar()
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
    connect(tblStartDebug,SIGNAL(clicked()),
            this,SLOT(onStartDebugButtonClicked()));

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

    ControlPanel->addWidget(DebugToolBar);
}

void KCDebugWidget::createControlPanel()
{
    //Control Panel Main Layout.
    ControlPanel=new QVBoxLayout;
    ControlPanel->setContentsMargins(0,0,0,0);
    ControlPanel->setSpacing(0);

    //Create Buttons.
    createToolBar();

    //Set New ToolButton.
    tblNextLine=new QToolButton(this);
    tblNextLine->setText(QString(" " + tr("Next Step")));
    tblNextLine->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/NextStep.png"));
    tblNextLine->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblNextLine->setFixedSize(160,30);
    ControlPanel->addWidget(tblNextLine);
    tblIntoLine=new QToolButton(this);
    tblIntoLine->setText(QString(" " + tr("Into Line")));
    tblIntoLine->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/NextLine.png"));
    tblIntoLine->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblIntoLine->setFixedSize(160,30);
    ControlPanel->addWidget(tblIntoLine);
    tblContinue=new QToolButton(this);
    tblContinue->setText(QString(" " + tr("Continue")));
    tblContinue->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/Continue.png"));
    tblContinue->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblContinue->setFixedSize(160,30);
    ControlPanel->addWidget(tblContinue);
    tblNextInstruction=new QToolButton(this);
    tblNextInstruction->setText(QString(" " + tr("Next Instruction")));
    tblNextInstruction->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/JumpFunction.png"));
    tblNextInstruction->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblNextInstruction->setFixedSize(160,30);
    ControlPanel->addWidget(tblNextInstruction);
    tblIntoInstruction=new QToolButton(this);
    tblIntoInstruction->setText(QString(" " + tr("Into Instruction")));
    tblIntoInstruction->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/GetIntoFuntion.png"));
    tblIntoInstruction->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblIntoInstruction->setFixedSize(160,30);
    ControlPanel->addWidget(tblIntoInstruction);
    tblSkipFunction=new QToolButton(this);
    tblSkipFunction->setText(QString(" " + tr("Skip Function")));
    tblSkipFunction->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/GetOutOfFuntion.png"));
    tblSkipFunction->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tblSkipFunction->setFixedSize(160,30);
    ControlPanel->addWidget(tblSkipFunction);
    ControlPanel->addStretch();
}

void KCDebugWidget::setDbgReceiver(dbgOutputReceiver *receiver)
{
    Q_ASSERT(receiver!=NULL);

    //watchView->setModel(receiver->getWatchModel());
    //localWatchView->setModel(receiver->getLocalVarModel());
    GDBInfo->setDocument(receiver->getTextStreamOutput());
}

void KCDebugWidget::connectGDB(gdb *instance)
{
    if(gdbInstance!=NULL)
    {
        connectionHandles.disConnectAll();
    }

    gdbInstance=instance;
    connectionHandles+=connect(tblNextLine,SIGNAL(clicked()),
                               gdbInstance,SLOT(execNext()));
    connectionHandles+=connect(tblIntoLine,SIGNAL(clicked()),
                               gdbInstance,SLOT(execStepi()));
    connectionHandles+=connect(tblNextInstruction,SIGNAL(clicked()),
                               gdbInstance,SLOT(execStepi()));
    connectionHandles+=connect(tblContinue,SIGNAL(clicked()),
                               gdbInstance,SLOT(execContinue()));
    connectionHandles+=connect(tblStopDebug,SIGNAL(clicked()),
                               gdbInstance,SLOT(execAbort()));
    connectionHandles+=connect(tblSkipFunction,SIGNAL(clicked()),
                               gdbInstance,SLOT(execReturn()));
}

void KCDebugWidget::onGDBCmdEditFinished(QString command)
{
    qDebug()<<command;
    gdbInstance->write(qPrintable(command+"\n"));
}

void KCDebugWidget::onStartDebugButtonClicked()
{
    if(gdbInstance == NULL)
    {
        emit m_parent->requireStartDebug();
    }

    Q_ASSERT(gdbInstance!=NULL);

    gdbInstance->execRun();
}

void KCDebugDock::setDbgReceiver(dbgOutputReceiver *receiver)
{
    Q_ASSERT(receiver!=NULL);
    CentralWidget->setDbgReceiver(receiver);
}

void KCDebugDock::setGdbInstance(gdb *instance)
{
    Q_ASSERT(instance!=NULL);
    CentralWidget->connectGDB(instance);
}
