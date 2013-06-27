#include "kcimainwindow.h"

int kciMainWindow::range=2;

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

bool kciMainWindow::eventFilter(QObject *obj, QEvent *e)
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
}
