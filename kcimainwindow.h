#ifndef KCIMAINWINDOW_H
#define KCIMAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QCursor>
#include <QPoint>
#include <QDebug>

#include "kcititlebar.h"

class kciMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit kciMainWindow(QWidget *parent = 0);
    
    kciTitleBar *titleBar() const;
    void setTitleBar(kciTitleBar *titleBar);
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString& mainIcon);
    void setWindowTitle(const QString &title);

signals:
    
public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    enum pressType
    {
        none,
        left_frame,
        right_frame,
        bottom_frame
    };

    kciTitleBar *m_titleBar;
    static int range;
    int pressed;
    QPoint startPos;
};

#endif // KCIMAINWINDOW_H
