
#include <QGraphicsDropShadowEffect>

#include "kcwelcomewindow.h"

KCWelcomeWindow::KCWelcomeWindow(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);

    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    setGraphicsEffect(wndShadow);

}
