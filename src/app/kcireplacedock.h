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
#include <QTimeLine>
#include <QDebug>

#include "kcisearchwidget.h"

class kciReplaceDock : public kciSearchWidget
{
    Q_OBJECT
public:
    explicit kciReplaceDock(QWidget *parent = 0);

public slots:
    void showAnime();
    void hideAnime();

private slots:
    void resizeDock(int newHeight);

private:
    QGridLayout *mainLayout;
    QLineEdit *replaceText;
    QToolButton *replaceButton, *findAndReplaceButton, *replaceAllButton;
    QToolButton *closeButton;
};

#endif // KCIREPLACEDOCK_H
