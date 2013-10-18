#include "kcdebugmaindock.h"

KCDebugMainDock::KCDebugMainDock(QWidget *parent) :
    QDockWidget(parent)
{
    //Set Properties;
    setContentsMargins(0,0,0,0);
    setObjectName("Debug Dock");
    setWindowTitle("Debugger");

    //Set deubg dock palette
    QPalette pal=this->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    setPalette(pal);

    //Set QMainWindow Widget for central widget.
    dockAreaContainer=new QMainWindow(this);
    dockAreaContainer->setContentsMargins(0,0,0,0);
    dockAreaContainer->setWindowFlags(dockAreaContainer->windowFlags() &
                                      Qt::Widget);
    dockAreaContainer->setDockOptions(QMainWindow::AllowNestedDocks);

    QWidget *y=new QWidget(this);
    dockAreaContainer->setCentralWidget(y);

    pal=dockAreaContainer->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    dockAreaContainer->setPalette(pal);
    setWidget(dockAreaContainer);

    //Set Debug Controls
    debugControlButtons=new KCDebugControlButtons(dockAreaContainer);
    dockAreaContainer->addDockWidget(Qt::TopDockWidgetArea, debugControlButtons);

    debugCommandIO=new KCDebugCommandIO(dockAreaContainer);
    dockAreaContainer->addDockWidget(Qt::BottomDockWidgetArea, debugCommandIO);
}
