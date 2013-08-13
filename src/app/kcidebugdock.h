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
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QPlainTextEdit>

#include "kcilanguagemode.h"
#include "gdb.h"
#include "dbgoutputreceiver.h"

class kciDebugDock;

class kciDebugWidget : public QWidget
{
    Q_OBJECT
public:
    explicit kciDebugWidget(QWidget *parent = 0);
    ~kciDebugWidget();

    void connectGDB(gdb *instance);
    void setDbgReceiver(dbgOutputReceiver *receiver);

private slots:
    void onGDBCmdEditFinished(QString command);

private:
    QToolButton *tblStartDebug, *tblStopDebug, *tblRunToCursor,
                *tblNextStep, *tblNextLine, *tblIntoInstruction,
                *tblNextInstruction, *tblSkipInstruction, *tblContinue;

    QToolBar *DebugToolBar;
    QToolButton *tblAddWatch, *tblEditWatch,* tblRemoveWatch;

    QPlainTextEdit *GDBInfo;
    //Main Widget Layout.
    QVBoxLayout *MainWidgetLayout;
    QHBoxLayout *MainShownLayout;

    //Control Panel Layout.
    QVBoxLayout *ControlPanel1, *ControlPanel2;
    QHBoxLayout *ControlPanelM;

    //Stack View.
    QVBoxLayout *stackMain;
    QLabel *lblStackView;
    QTreeView *trevwStackView;

    //Combine.
    QVBoxLayout *CombinePanelStack;

    //GDB Layout.
    QHBoxLayout *InputToGDB;
    QVBoxLayout *GDBMainLayout;
    QComboBox *GDBCmd;

    //Watch Layout.
    QVBoxLayout *WatchLayout;
    QLabel *lblLocalWatch;
    QTreeView *localWatchView;
    QLabel *lblWatch;
    QTreeView *watchView;

    kciDebugDock *m_parent;
    gdb *gdbInstance;

    void createToolBar();
    void createControlButtons();
    void createStackView();
    void createGDBConversation();
    void createWatchLayout();
};

class kciDebugDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit kciDebugDock(QWidget *parent = 0);
    void connectCurrEditorLangMode(kciLanguageMode *mode);
    
signals:
    void requireStartDebug();
    
public slots:
    
private:
    kciDebugWidget *CentralWidget;
};

#endif // KCIDEBUGDOCK_H
