#ifndef KCIMESSAGEBOX_H
#define KCIMESSAGEBOX_H

#include <QDialog>
#include <QPainter>
#include <QPalette>

class kciMessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit kciMessageBox(QWidget *parent = 0);
    ~kciMessageBox();

signals:
    
protected:
    void paintEvent(QPaintEvent *e);

public slots:

private:

    
};

#endif // KCIMESSAGEBOX_H
