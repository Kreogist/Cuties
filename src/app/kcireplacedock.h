#ifndef KCIREPLACEDOCK_H
#define KCIREPLACEDOCK_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimeLine>
#include <QKeyEvent>
#include <QDebug>

class kciReplaceDock : public QWidget
{
    Q_OBJECT
public:
    explicit kciReplaceDock(QWidget *parent = 0);
    ~kciReplaceDock();

signals:
    
public slots:
    void showAnime();
    void hideAnime();

private slots:
    void resizeDock(int newHeight);

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QVBoxLayout *mainLayout;
    QLineEdit *replaceText;

    enum menuItem
    {
        menuRegularExpress,
        menuMatchCase,
        menuWholeWord,
        menuItemCount
    };

    QWidget *searchText;
    QHBoxLayout *Layout, *searchLayout, *replaceLayout;
    QPushButton *SearchIcon;
    QLineEdit *SearchTexts;
    QMenu *menu;
    QAction *menuAction[menuItemCount];

    QToolButton *upButton, *downButton, *closeButton;
    QToolButton *replaceButton, *findAndReplaceButton, *replaceAllButton;
};

#endif // KCIREPLACEDOCK_H
