#include "kcdebugwatchdock.h"

KCDebugWatchContent::KCDebugWatchContent(QWidget *parent) :
    QWidget(parent)
{
    //Create Watch Layout.
    WatchLayout=new QVBoxLayout;
    WatchLayout->setContentsMargins(0,0,0,0);
    WatchLayout->setSpacing(5);
    setLayout(WatchLayout);

    watchToolBar=new QToolBar(this);
    //Set Debug Watch Buttons.
    tblAddWatch=new QToolButton(this);
    tblAddWatch->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/AddWatch.png"));
    tblAddWatch->setFixedSize(26,26);
    watchToolBar->addWidget(tblAddWatch);

    tblRemoveWatch=new QToolButton(this);
    tblRemoveWatch->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/RemoveWatch.png"));
    tblRemoveWatch->setFixedSize(26,26);
    watchToolBar->addWidget(tblRemoveWatch);

    tblEditWatch=new QToolButton(this);
    tblEditWatch->setIcon(QIcon(":/DebugToolBar/image/Debug Docks/ModifyWatch.png"));
    tblEditWatch->setFixedSize(26,26);
    watchToolBar->addWidget(tblEditWatch);
    WatchLayout->addWidget(watchToolBar);

    //Add Label Widget.
    lblLocalWatch=new QLabel(this);
    lblLocalWatch->setText(" " + tr("Local Watch"));
    WatchLayout->addWidget(lblLocalWatch);
    //Add TreeView
    localWatchView=new QTreeView(this);
    QPalette pal=localWatchView->palette();
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    localWatchView->setPalette(pal);
    localWatchView->setHeaderHidden(true);
    WatchLayout->addWidget(localWatchView);

    //Add New Label Widget.
    lblWatch=new QLabel(this);
    lblWatch->setText(" " + tr("Custom Watch"));
    WatchLayout->addWidget(lblWatch);
    //Add TreeView
    watchView=new QTreeView(this);
    watchView->setPalette(pal);
    watchView->setHeaderHidden(true);
    WatchLayout->addWidget(watchView);
}

KCDebugWatchDock::KCDebugWatchDock(QWidget *parent) :
    QDockWidget(parent)
{
    //Set ObjectName
    setObjectName("Watch Dock");

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
    setWindowTitle(" " + tr("Watch Dock") + " ");

    //New Central Widget
    CentralWidget=new KCDebugWatchContent(this);
    setWidget(CentralWidget);
}
