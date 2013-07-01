#ifndef KCISEARCHTEXTBOX_H
#define KCISEARCHTEXTBOX_H

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPalette>
#include <QWidget>

class kciSearchTextBox : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchTextBox(QWidget *parent = 0);
    void setTheFocus();
    
signals:
    
public slots:

private:
    QLineEdit *SearchTexts;
    QHBoxLayout *Layout;
    QPushButton *SearchIcon;
};

#endif // KCISEARCHTEXTBOX_H
