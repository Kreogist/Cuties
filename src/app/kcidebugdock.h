#ifndef KCIDEBUGDOCK_H
#define KCIDEBUGDOCK_H

#include <QDockWidget>
#include <QPalette>
#include <QGridLayout>
#include <QToolButton>

class kciDebugWidget : public QWidget
{
    Q_OBJECT
public:
    explicit kciDebugWidget(QWidget *parent = 0);

private:
    QToolButton *tblStartDebug, *tblStopDebug, *tblRunToBreakPoint,
                *tblNextStep, *tblNextLine, *tblIntoFunction,
                *tblOutFunction, *tblContinue;

    QToolButton *tblAddWatch, *tblEditWatch,* tblRemoveWatch;

    QGridLayout *PanelLayout;

    void createControlButtons();
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
