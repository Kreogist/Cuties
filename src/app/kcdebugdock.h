#ifndef KCDEBUGDOCK_H
#define KCDEBUGDOCK_H

#include <QDockWidget>
#include <QPalette>
#include <QToolButton>
#include <QToolBar>
#include <QLabel>
#include <QComboBox>
#include <QTreeView>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "kcplaintextbrowser.h"
#include "kclanguagemode.h"
#include "gdb.h"
#include "dbgoutputreceiver.h"
#include "kcconnectionhandler.h"

class KCDebugDock;

class KCDebugWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KCDebugWidget(QWidget *parent = 0);
    ~KCDebugWidget();

    void connectGDB(gdb *instance);
    void setDbgReceiver(dbgOutputReceiver *receiver);

private slots:
    void onStartDebugButtonClicked();
    void onGDBCmdEditFinished(QString command);

private:
    QToolButton *tblStartDebug, *tblStopDebug, *tblRunToCursor,
                *tblNextLine, *tblIntoLine, *tblNextInstruction,
                *tblIntoInstruction, *tblContinue, *tblSkipFunction;

    KCPlainTextBrowser *GDBInfo;
    //Main Widget Layout.
    QHBoxLayout *MainWidgetLayout;

    //Control Panel Layout.
    QToolBar *DebugToolBar;
    QVBoxLayout *ControlPanel;

    //GDB Layout.
    QHBoxLayout *InputToGDB;
    QVBoxLayout *GDBMainLayout;
    QComboBox *GDBCmd;

    KCDebugDock *m_parent;
    gdb *gdbInstance;

    KCConnectionHandler connectionHandles;

    void createToolBar();
    void createControlPanel();
    void createStackView();
    void createGDBConversation();
    void createWatchLayout();
};

class KCDebugDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugDock(QWidget *parent = 0);
    void setDbgReceiver(dbgOutputReceiver *receiver);
    void setGdbInstance(gdb *instance);

signals:
    void requireStartDebug();

public slots:


private:
    KCDebugWidget *CentralWidget;
};

#endif // KCDEBUGDOCK_H
