#ifndef KCILISTBUTTON_H
#define KCILISTBUTTON_H

#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>

class kciListButton : public QWidget
{
    Q_OBJECT
public:
    explicit kciListButton(QWidget *parent = 0);
    
signals:
    
protected:


public slots:

private:
    QLabel *lblButtonText;
    QHBoxLayout *mLayout;
};

#endif // KCILISTBUTTON_H
