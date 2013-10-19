#ifndef KCDEBUGCONTROLBUTTONS_H
#define KCDEBUGCONTROLBUTTONS_H

#include <QDockWidget>
#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include <QVBoxLayout>

#include "kccolorconfigure.h"

class KCDebugControlPanel : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugControlPanel(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    enum debugContolButtons
    {
        debugStart,
        debugStop,
        debugRunToCursor,
        debugControlButtonCount
    };

    enum debugCursorControlButtons
    {
        debugNextLine,
        debugContinue,
        debugIntoFunction,
        debugNextInstruction,
        debugIntoInstruction,
        debugSkipFunction,
        debugCursorControlButtonCount
    };

    QToolBar *toolBar;
    QToolButton *debugControlButton[debugControlButtonCount];
    QToolButton *debugCursorControlButton[debugCursorControlButtonCount];
};

#endif // KCDEBUGCONTROLBUTTONS_H
