/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *
 *  kcimainwindow.h is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kcimainwindow.h"

static const int we=3;

int kciMainWindow::range=3;
bool pressflag=false,isleft=false,istop=false,isright=false,isbottom=false;
QPoint newpos;

kciMainWindow::kciMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_titleBar=new kciTitleBar(this);
    setMenuWidget(m_titleBar);
    setMouseTracking(true);

    setContentsMargins(0,0,0,0);
    pressed=none;

    setWindowFlags(Qt::FramelessWindowHint);

    qApp->installEventFilter(this);
}

void kciMainWindow::setWindowTitle(const QString &title)
{
    m_titleBar->setTitle(title);
    QMainWindow::setWindowTitle(title);
}

kciTitleBar *kciMainWindow::titleBar() const
{
    return m_titleBar;
}

void kciMainWindow::setTitleBar(kciTitleBar *titleBar)
{
    m_titleBar = titleBar;
}

void kciMainWindow::setMainButtonIcon(const QString &mainIcon)
{
    if(m_titleBar)
        m_titleBar->setMainButtonIcon(mainIcon);
}

void kciMainWindow::setMenu(QMenu *menu)
{
    if(m_titleBar)
        m_titleBar->setMenu(menu);
}

void kciMainWindow::mousePressEvent(QMouseEvent *e)
{
    pressflag=true;
    int w_x,w_y,w_w,w_h,m_x,m_y;
    m_x=e->globalX();
    m_y=e->globalY();
    w_x=this->x();
    w_y=this->y();
    w_w=this->width();
    w_h=this->height();

    qDebug()<<w_x<<w_y<<w_w<<w_h<<m_x<<m_y;

    if(m_x>=w_x && m_x<=(w_x+w_w) && m_y>=(w_y-we+w_h) && m_y<=(w_y+we+w_h))
    {
        isbottom=true;
        qDebug()<<"top";
    }

    else if(m_x>=(w_x-we) && m_x<=(w_x+we) && m_y>=w_y && m_y<=(w_y+w_h))
    {
        isleft=true;
        qDebug()<<"left";
    }

    else if(m_x>=(w_x+w_w-we) && m_x<=(w_x+w_w+we) && m_y>=w_y && m_y<=(w_y+w_h))
    {
        isright=true;
        qDebug()<<"right";
    }


    qDebug()<<"press";
}


void kciMainWindow::mouseMoveEvent(QMouseEvent *e)
{
    newpos=e->pos();
    QRect g;
    g=this->geometry();

    if(pressflag==true)
    {
        if(isbottom)
        {
            g.setHeight(e->y());
        }
        else if(isright)
        {
            g.setWidth(e->x());
        }
        else if(isleft)
        {
            //g.setWidth(this->width()-e->x());
            g.setX(this->x()+e->x());
        }
        this->setGeometry(g);
    }
}

void kciMainWindow::mouseReleaseEvent(QMouseEvent *)
{
    pressflag=false;
    isleft=false;
    istop=false;
    isright=false;
    isbottom=false;
    qDebug()<<"release";
}
/*bool kciMainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(e);
        QCursor _cursor=cursor();
        if(!pressed)
        {
            if(x()-range <= mouseEvent->globalX() &&
               x()+range >= mouseEvent->globalX())
            {
                _cursor.setShape(Qt::SizeHorCursor);
            }
            else if(x()+width()-range <= mouseEvent->globalX() &&
                    x()+width()+range >= mouseEvent->globalX())
            {
                _cursor.setShape(Qt::SizeHorCursor);
            }
            else if(y()+height()-range <= mouseEvent->globalY()&&
                    y()+height()+range >=mouseEvent->globalY())
            {
                _cursor.setShape(Qt::SizeVerCursor);
            }
            else
            {
                _cursor.setShape(Qt::ArrowCursor);
                setCursor(_cursor);
                return false;
            }
        }
        else
        {
            switch(pressed)
            {
            case left_frame:
            {
                int _move=mouseEvent->globalX()-startPos.x();
                resize(width()-_move,height());
                move(x()+_move,y());
                startPos.setX(mouseEvent->globalX());
                break;
            }
            case right_frame:
            {
                int _move=mouseEvent->globalX()-startPos.x();
                resize(width()+_move,height());
                //_cursor.setPos(mouseEvent->globalX()+_move,mouseEvent->globalY());
                startPos.setX(mouseEvent->globalX());
                break;
            }
            case bottom_frame:
            {
                resize(width(),height()+mouseEvent->globalY()-startPos.y());
                startPos.setY(mouseEvent->globalY());
                break;
            }
            default:
            {
                _cursor.setShape(Qt::ArrowCursor);
                setCursor(_cursor);
                return false;
            }
            }
        }

        setCursor(_cursor);
        return true;
    }
    else if(e->type() == QEvent::MouseButtonRelease && pressed)
    {
        pressed=none;
        return true;
    }
    else if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(e);
        if(mouseEvent->buttons() == Qt::LeftButton)
        {
          if(x()-range <= mouseEvent->globalX() &&
          x()+range >= mouseEvent->globalX())
          {
              pressed=left_frame;
              startPos=mouseEvent->globalPos();
              return true;
          }
          else if(x()+width()-range <= mouseEvent->globalX() &&
          x()+width()+range >= mouseEvent->globalX())
          {
              pressed=right_frame;
              startPos=mouseEvent->globalPos();
              return true;
          }
          else if(y()+height()-range <= mouseEvent->globalY()&&
          y()+height()+range >=mouseEvent->globalY())
          {
              pressed=bottom_frame;
              startPos=mouseEvent->globalPos();
              return true;
          }
        }
    }

    return qApp->eventFilter(obj,e);
}*/
