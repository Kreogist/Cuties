#include "kcwelcomewindow.h"

KCWelcomeWindow::KCWelcomeWindow(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);
}
