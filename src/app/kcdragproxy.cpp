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

#include "kcdragproxy.h"

KCDragProxy::KCDragProxy(QWidget *parent)
    : QObject((QObject *)parent)
{
    proxyWidget = parent;
    m_top = m_right = m_bottom = m_left = 0;

    proxyWidget->setMouseTracking(true);
    proxyWidget->installEventFilter(this);

    m_mousePressed=false;
    m_regionPressed=Unknown;

    m_cursorTimerId = 0;

    enabled=true;
}

KCDragProxy::~KCDragProxy()
{
}

void KCDragProxy::setEnabled(bool value)
{
    enabled=value;
}

void KCDragProxy::setBorderWidth(int top, int right, int bottom, int left)
{
    m_top = top;
    m_right = right;
    m_bottom = bottom;
    m_left = left;

    MakeRegions();
}

void KCDragProxy::updateGeometry(int x, int y, int w, int h)
{
    minWidth = proxyWidget->minimumWidth();
    minHeight = proxyWidget->minimumHeight();
    maxWidth = proxyWidget->maximumWidth();
    maxHeight = proxyWidget->maximumHeight();

    if(w < minWidth || w > maxWidth || h < minHeight || h > maxHeight)
    {
        return;
    }

    proxyWidget->setGeometry(x, y, w, h);
}

bool KCDragProxy::eventFilter(QObject *obj, QEvent *event)
{
    if(!enabled)
    {
        return false;
    }
    QEvent::Type eventType = event->type();
    if(eventType==QEvent::HoverMove)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        QPoint curPosLocal = mouseEvent->pos();
        KCDragProxy::WidgetRegion regionType = HitTest(curPosLocal);

        QPoint curPosGlobal = proxyWidget->mapToGlobal(curPosLocal);

        if(!m_mousePressed)
        {
            switch(regionType)
            {
            case Bottom:
                proxyWidget->setCursor(Qt::SizeVerCursor);
                break;
            case LeftBottom:
                proxyWidget->setCursor(Qt::SizeBDiagCursor);
                break;
            case Right:
            case Left:
                proxyWidget->setCursor(Qt::SizeHorCursor);
                break;
            case RightBottom:
                proxyWidget->setCursor(Qt::SizeFDiagCursor);
                break;
            default:
                proxyWidget->setCursor(Qt::ArrowCursor);
                break;
            }

            startCursorTimer();
        }
        else
        {
            if(m_regionPressed == Right)
            {
                dX = curPosGlobal.x() - m_originPosGlobal.x();
                updateGeometry(m_originGeo.x(), m_originGeo.y(), m_originGeo.width() + dX, m_originGeo.height());
            }
            else if(m_regionPressed == RightBottom)
            {
                dXY = curPosGlobal - m_originPosGlobal;
                updateGeometry(m_originGeo.x(), m_originGeo.y(), m_originGeo.width() + dXY.x(), m_originGeo.height() + dXY.y());
            }
            else if(m_regionPressed == Bottom)
            {
                dY = curPosGlobal.y() - m_originPosGlobal.y();
                updateGeometry(m_originGeo.x(), m_originGeo.y(), m_originGeo.width(), m_originGeo.height() + dY);
            }
            else if(m_regionPressed == LeftBottom)
            {
                dXY = curPosGlobal - m_originPosGlobal;
                updateGeometry(m_originGeo.x() + dXY.x(), m_originGeo.y(), m_originGeo.width() - dXY.x(), m_originGeo.height() + dXY.y());
            }
            else if(m_regionPressed == Left)
            {
                dX = curPosGlobal.x() - m_originPosGlobal.x();
                updateGeometry(m_originGeo.x() + dX, m_originGeo.y(), m_originGeo.width() - dX, m_originGeo.height());
            }
        }
    }
    else if(eventType == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if(mouseEvent->button() == Qt::LeftButton)
        {
            m_mousePressed = true;

            QPoint curPos = mouseEvent->pos();
            m_regionPressed = HitTest(curPos);

            m_originPosGlobal = proxyWidget->mapToGlobal(curPos);
            m_originGeo = proxyWidget->geometry();

            stopCursorTimer();
        }
    }
    else if(eventType == QEvent::MouseButtonRelease)
    {
        m_mousePressed = false;
        m_regionPressed = Unknown;

        proxyWidget->setCursor(Qt::ArrowCursor);
    }
    else if(eventType == QEvent::Resize)
    {
        MakeRegions();
    }
    else if(eventType == QEvent::Leave)
    {
        proxyWidget->setCursor(Qt::ArrowCursor);
        stopCursorTimer();
    }
    else if(eventType == QEvent::Timer)
    {
        QTimerEvent *timerEvent = (QTimerEvent *)event;
        if(timerEvent->timerId() == m_cursorTimerId)
        {
            if(m_regions[Inner].contains(proxyWidget->mapFromGlobal(QCursor::pos())))
            {
                proxyWidget->setCursor(Qt::ArrowCursor);
                stopCursorTimer();
            }
        }
    }

    return QObject::eventFilter(obj, event);
}

void KCDragProxy::startCursorTimer()
{
    stopCursorTimer();
    m_cursorTimerId = proxyWidget->startTimer(50);
}

void KCDragProxy::stopCursorTimer()
{
    if(m_cursorTimerId != 0)
    {
        proxyWidget->killTimer(m_cursorTimerId);
        m_cursorTimerId = 0;
    }
}

void KCDragProxy::MakeRegions()
{
    regWidth = proxyWidget->width();
    regHeight = proxyWidget->height();

    m_regions[Right]        = QRect(regWidth - m_right, m_top, m_right, regHeight - m_top - m_bottom);
    m_regions[RightBottom]  = QRect(regWidth - m_right, regHeight - m_bottom, m_right, m_bottom);
    m_regions[Bottom]       = QRect(m_left, regHeight - m_bottom, regWidth - m_left - m_right, m_bottom);
    m_regions[LeftBottom]   = QRect(0, regHeight - m_bottom, m_left, m_bottom);
    m_regions[Left]         = QRect(0, m_top, m_left, regHeight - m_top - m_bottom);
    m_regions[Inner]        = QRect(m_left, m_top, regWidth - m_left - m_right, regHeight - m_top - m_bottom);
}

KCDragProxy::WidgetRegion KCDragProxy::HitTest(const QPoint &pos)
{
    for(int i = Right; i < Unknown; i++)
    {
        const QRect rect = m_regions[i];
        if(rect.contains(pos))
        {
            return KCDragProxy::WidgetRegion(i);
        }
    }

    return Unknown;
}
