#ifndef KCISIDEBAR_H
#define KCISIDEBAR_H

#include <QDockWidget>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>

class kciSideBarContent : public QWidget
{
    Q_OBJECT
public:
    explicit kciSideBarContent(QWidget *parent = 0);


};

class kciSideBarTitle : public QWidget
{
    Q_OBJECT
public:
    explicit kciSideBarTitle(QWidget *parent = 0);
    void setSidebarTitle(const QString title);

private:
    QHBoxLayout *titleMainLayout;
    QLabel *sidebarTitle;
    QToolButton *sidebarLock;
};

class kciSideBar : public QDockWidget
{
    Q_OBJECT
public:
    explicit kciSideBar(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    kciSideBarContent *CentralWidget;
    kciSideBarTitle *sidebarTitleBar;
};

#endif // KCISIDEBAR_H
