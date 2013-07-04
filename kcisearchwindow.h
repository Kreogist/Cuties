#ifndef KCISEARCHWINDOW_H
#define KCISEARCHWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QPalette>
#include <QKeySequence>
#include <QGraphicsDropShadowEffect>
#include <QFrame>
#include <QTextDocument>

#include "kcisearchtextbox.h"

class kciSearchWindow : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchWindow(QWidget *parent = 0);
    void setTextFocus();
    void setDocument(QTextDocument* doc);

protected:
    void hideEvent(QHideEvent *e);

signals:
    void hideButtonPressed();

private:
    QHBoxLayout *searchLayout;
    QToolButton *closeButton, *upButton, *downButton;
    kciSearchTextBox *searchText;

};

#endif // KCISEARCHWINDOW_H
