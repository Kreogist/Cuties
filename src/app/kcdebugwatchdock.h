#ifndef KCDEBUGWATCHDOCK_H
#define KCDEBUGWATCHDOCK_H

#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QToolBar>
#include <QTreeView>
#include <QDockWidget>
#include <QPalette>

class KCDebugWatchContent : public QWidget
{
    Q_OBJECT
public:
    explicit KCDebugWatchContent(QWidget *parent = 0);

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
    KCDebugWatchContent *CentralWidget;
};

#endif // KCDEBUGWATCHDOCK_H
