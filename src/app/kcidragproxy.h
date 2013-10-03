/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    virtual bool eventFilter(QObject *obj, QEvent *event);

    void MakeRegions();
    WidgetRegion HitTest(const QPoint &pos);
    void updateGeometry(int x, int y, int w, int h);

    void startCursorTimer();
    void stopCursorTimer();

private:
    QWidget *m_proxyWidget;
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
