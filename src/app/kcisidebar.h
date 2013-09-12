#ifndef KCISIDEBAR_H
#define KCISIDEBAR_H

#include <QDockWidget>
#include <QLabel>
#include <QTimeLine>
#include <QIcon>
#include <QToolButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStackedWidget>
#include <QListView>

class kciSideBarContent : public QWidget
{
    Q_OBJECT
public:
    explicit kciSideBarContent(QWidget *parent = 0);
    ~kciSideBarContent();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonGroupLayout;
    QToolButton *buttonRecent;

    QStackedWidget *contents;
    QListView *historyStack;
};

class kciSideBarTitle : public QWidget
{
    Q_OBJECT
public:
    explicit kciSideBarTitle(QWidget *parent = 0);
    void setSidebarTitle(const QString title);

signals:
    void closePressed();

private:
    QHBoxLayout *titleMainLayout;
    QLabel *sidebarTitle;
    QToolButton *sidebarClose;
};

class kciSideBar : public QDockWidget
{
    Q_OBJECT
public:
    explicit kciSideBar(QWidget *parent = 0);
    
signals:
    
public slots:
    void showAnime();
    void hideAnime();

private slots:
    void resizeDock(int newWidth);

private:
    kciSideBarContent *CentralWidget;
    kciSideBarTitle *sidebarTitleBar;
};

#endif // KCISIDEBAR_H
