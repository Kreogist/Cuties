#ifndef KCIMARKPANEL_H
#define KCIMARKPANEL_H

#include <QVector>
#include <QRect>
#include <QPoint>

#include "kcipanel.h"

class kciMarkPanel : public kciPanel
{
    Q_OBJECT
public:
    explicit kciMarkPanel(QWidget *parent = 0);
    
    QPixmap getMarkPix() const;
    void setMarkPix(const QPixmap &value);

signals:
    
public slots:

protected:
    void draw(QPainter *painter, QTextBlock *block,
              int x, int y, int w, int h,
              bool isCurrentLine);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    struct markUnit
    {
        QRect rect;
        bool marked;
        markUnit(){marked=false;}
    };

    QVector<markUnit> vecMark;
    QPixmap markPix;
    QPoint pressedPos;
    bool isPressed;
};

#endif // KCIMARKPANEL_H
