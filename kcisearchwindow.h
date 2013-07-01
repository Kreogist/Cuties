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
#include <QFrame>

#include "kcisearchtextbox.h"

class kciSearchWindow : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchWindow(QWidget *parent = 0);
    void setTextFocus();

signals:
    
public slots:

private:
    QHBoxLayout *searchLayout;
    QToolButton *closeButton, *upButton, *downButton;
    kciSearchTextBox *searchText;
};

#endif // KCISEARCHWINDOW_H
