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

class kciDebugWidget : public QWidget
{
    Q_OBJECT
public:
    explicit kciDebugWidget(QWidget *parent = 0);

private:
    QToolButton *tblStartDebug, *tblStopDebug, *tblRunToCursor,
                *tblNextStep, *tblNextLine, *tblIntoFunction,
                *tblOutFunction, *tblContinue;

    QToolBar *DebugToolBar;
    QToolButton *tblAddWatch, *tblEditWatch,* tblRemoveWatch;

    QPlainTextEdit *GDBInfo;
    //Main Widget Layout.
    QVBoxLayout *MainWidgetLayout;
    QHBoxLayout *MainShownLayout;

    //Control Panel Layout.
    QVBoxLayout *ControlPanel;

    //GDB Layout.
    QHBoxLayout *InputToGDB;
    QVBoxLayout *GDBMainLayout;
    QComboBox *GDBCmd;

    //Watch Layout.
    QTreeView *watchView;
    QStandardItemModel *watchResult;
    QStandardItem *LocalValueView, *CustomValueView;

    void createToolBar();
    void createControlButtons();
    void createGDBConversation();
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
