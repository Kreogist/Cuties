#ifndef KCIDEBUGDOCK_H
#define KCIDEBUGDOCK_H

#include <QDockWidget>
#include <QPalette>
#include <QToolButton>
#include <QToolBar>
#include <QLabel>
#include <QComboBox>
#include <QTreeView>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "kciplaintextbrowser.h"
#include "kcilanguagemode.h"
#include "gdb.h"
#include "dbgoutputreceiver.h"
#include "connectionhandler.h"

class KCIDebugDock;

class kciDebugWidget : public QWidget
{
    Q_OBJECT
public:
    explicit kciDebugWidget(QWidget *parent = 0);
    ~kciDebugWidget();

    void connectGDB(gdb *instance);
    void setDbgReceiver(dbgOutputReceiver *receiver);

private slots:
    void onStartDebugButtonClicked();
    void onGDBCmdEditFinished(QString command);

private:
    QToolButton *tblStartDebug, *tblStopDebug, *tblRunToCursor,
                *tblNextLine, *tblIntoLine, *tblNextInstruction,
                *tblIntoInstruction, *tblContinue, *tblSkipFunction;

    kciPlainTextBrowser *GDBInfo;
    //Main Widget Layout.
    QHBoxLayout *MainWidgetLayout;

    //Control Panel Layout.
    QToolBar *DebugToolBar;
    QVBoxLayout *ControlPanel;

    //GDB Layout.
    QHBoxLayout *InputToGDB;
    QVBoxLayout *GDBMainLayout;
    QComboBox *GDBCmd;

    KCIDebugDock *m_parent;
    gdb *gdbInstance;

    connectionHandler connectionHandles;

    void createToolBar();
    void createControlPanel();
    void createStackView();
    void createGDBConversation();
    void createWatchLayout();
};

class KCIDebugDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCIDebugDock(QWidget *parent = 0);
    void setDbgReceiver(dbgOutputReceiver *receiver);
    void setGdbInstance(gdb* instance);

signals:
    void requireStartDebug();
    
public slots:


private:
    kciDebugWidget *CentralWidget;
};

#endif // KCIDEBUGDOCK_H
