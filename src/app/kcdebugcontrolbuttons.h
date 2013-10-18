#ifndef KCDEBUGCONTROLBUTTONS_H
#define KCDEBUGCONTROLBUTTONS_H

#include <QDockWidget>
#include <QToolBar>
#include <QToolButton>

#include <kccolorconfigure.h>

class KCDebugControlButtons : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugControlButtons(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    enum debugContolButtons
    {
        debugStart,
        debugStop,
        debugControlButtonCount
    };

    QToolBar *toolBar;
    QToolButton *debugControlButton[debugControlButtonCount];
};

#endif // KCDEBUGCONTROLBUTTONS_H
