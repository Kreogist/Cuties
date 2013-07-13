#ifndef KCISEARCHLINETEXT_H
#define KCISEARCHLINETEXT_H

#include <QLineEdit>
#include <QIcon>
#include <QWidget>
#include <QHBoxLayout>

class kciSearchLineText : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchLineText(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    QLineEdit *searchTextBox;
    QHBoxLayout *MainLayout;

};

#endif // KCISEARCHLINETEXT_H
