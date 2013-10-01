#ifndef KCIDEBUGWATCHDOCK_H
#define KCIDEBUGWATCHDOCK_H

#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QToolBar>
#include <QTreeView>
#include <QDockWidget>
#include <QPalette>

class kciDebugWatchContent : public QWidget
{
    Q_OBJECT
public:
    explicit kciDebugWatchContent(QWidget *parent = 0);

private:
    //Watch Layout.
    QToolBar *watchToolBar;
    QToolButton *tblAddWatch, *tblEditWatch,* tblRemoveWatch;
    QVBoxLayout *WatchLayout;
    QLabel *lblLocalWatch;
    QTreeView *localWatchView;
    QLabel *lblWatch;
    QTreeView *watchView;
};

class KCIDebugWatchDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCIDebugWatchDock(QWidget *parent = 0);
    
signals:

public slots:

private:
    kciDebugWatchContent *CentralWidget;
};

#endif // KCIDEBUGWATCHDOCK_H
