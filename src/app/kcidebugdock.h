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
#include <QCommonStyle>

class kciDebugWidget : public QWidget
{
    Q_OBJECT
public:
    explicit kciDebugWidget(QWidget *parent = 0);
    ~kciDebugWidget();

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
    QStandardItemModel *mdlStackView;

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
    QStandardItemModel *localWatchResult;
    QLabel *lblWatch;
    QTreeView *watchView;
    QStandardItemModel *watchResult;

    //Some Control Needs Origin Style.
    QCommonStyle *DockStyle;

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
    
signals:
    
public slots:
    
private:
    kciDebugWidget *CentralWidget;
};

#endif // KCIDEBUGDOCK_H
