#include "kcdebugcontrolbuttons.h"

KCDebugControlButtons::KCDebugControlButtons(QWidget *parent) :
    QDockWidget(parent)
{
    //Set properties.
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setObjectName("Debug Controller");
    //QWidget *blankTitleWidget=new QWidget(this);
    //setTitleBarWidget(blankTitleWidget);

    //Set compile dock palette
    QPalette pal=this->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    setPalette(pal);

    toolBar=new QToolBar(tr("Debug Controls"), this);
    toolBar->setContentsMargins(0,0,0,0);
    setWidget(toolBar);

    QString debugControlIconPath[debugControlButtonCount],
            debugControlToolTips[debugControlButtonCount];
    debugControlIconPath[debugStart]=QString(":/DebugToolBar/image/Debug Docks/StartDebug.png");
    debugControlIconPath[debugStop]=QString(":/DebugToolBar/image/Debug Docks/StopDebug.png");

    debugControlToolTips[debugStart]=tr("Start Debug");
    debugControlToolTips[debugStop]=tr("Stop Debug");

    for(int i=debugStart; i<debugControlButtonCount; i++)
    {
        debugControlButton[i]=new QToolButton(this);
        debugControlButton[i]->setFixedSize(25,25);
        debugControlButton[i]->setIcon(QIcon(debugControlIconPath[i]));
        debugControlButton[i]->setToolTip(debugControlToolTips[i]);
        toolBar->addWidget(debugControlButton[i]);
    }
}

