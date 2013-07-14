#ifndef KCIDEBUGDOCK_H
#define KCIDEBUGDOCK_H

#include <QDockWidget>
#include <QPalette>
#include <QGridLayout>
#include <QToolButton>
#include <QHBoxLayout>
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

    QToolButton *tblAddWatch, *tblEditWatch,* tblRemoveWatch;

    QPlainTextEdit *GDBInfo;
    QVBoxLayout *LeftButtonVList1, *LeftButtonVList2, *LeftButtonVList3;
    QHBoxLayout *MainLayout;

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
