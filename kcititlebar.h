#ifndef KCITITLEBAR_H
#define KCITITLEBAR_H

#include <QToolBar>
#include <QPoint>
#include <QMouseEvent>

class kciTitleBar : public QToolBar
{
    Q_OBJECT
public:
    explicit kciTitleBar(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool hasPressed;
    QPoint mousePosStart;
    QWidget *mainWindow;
};

#endif // KCITITLEBAR_H
