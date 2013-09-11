#ifndef KCIREPLACEDOCK_H
#define KCIREPLACEDOCK_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class kciReplaceDock : public QWidget
{
    Q_OBJECT
public:
    explicit kciReplaceDock(QWidget *parent = 0);

signals:
    
public slots:

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
    QHBoxLayout *Layout;
    QPushButton *SearchIcon;
    QLineEdit *SearchTexts;
    QMenu *menu;
    QAction *menuAction[menuItemCount];
};

#endif // KCIREPLACEDOCK_H
