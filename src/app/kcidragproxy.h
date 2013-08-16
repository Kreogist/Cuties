#ifndef KCIDRAGPROXY_H
#define KCIDRAGPROXY_H

#include <QObject>
#include <QWidget>
#include <QEvent>
#include <QRect>
#include <QPoint>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QCursor>
#include <QDebug>

class kciDragProxy : public QObject
{
    Q_OBJECT
public:
    kciDragProxy(QWidget *parent);
    ~kciDragProxy();
protected:
    enum WidgetRegion
    {
        Right,
        RightBottom,
        Bottom,
        LeftBottom,
        Left,
        Inner,
        Unknown
    };

public:
    void setBorderWidth(int top, int right, int bottom, int left);

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event);

    void MakeRegions();
    WidgetRegion HitTest(const QPoint& pos);
    void updateGeometry(int x, int y, int w, int h);

    void startCursorTimer();
    void stopCursorTimer();

private:
    QWidget* m_proxyWidget;
    int m_top, m_right, m_bottom, m_left;
    QRect m_regions[9];

    QPoint m_originPosGlobal;
    QRect m_originGeo;

    bool m_mousePressed;
    WidgetRegion m_regionPressed;

    int m_cursorTimerId;

    //Accelerate Variables.
    int minWidth ,minHeight, maxWidth, maxHeight;
    int dX, dY;
    QPoint dXY;
    int regWidth, regHeight;
};

#endif // KCIDRAGPROXY_H
