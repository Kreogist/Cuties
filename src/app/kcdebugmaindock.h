#ifndef KCDEBUGMAINDOCK_H
#define KCDEBUGMAINDOCK_H

#include <QDockWidget>
#include <QMainWindow>

#include "kcdebugcontrolbuttons.h"
#include "kcdebugcommandio.h"

class KCDebugMainDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugMainDock(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QMainWindow *dockAreaContainer;
    KCDebugControlButtons *debugControlButtons;
    KCDebugCommandIO *debugCommandIO;
};

#endif // KCDEBUGMAINDOCK_H
