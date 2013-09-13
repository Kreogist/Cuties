#include "kcimessagebox.h"

kciMessageBox::kciMessageBox(QWidget *parent) :
    QDialog(parent)
{
}

kciMessageBox::~kciMessageBox()
{

}

void kciMessageBox::paintEvent(QPaintEvent *e)
{
    QPainter p(this );
    p.fillRect(rect(), QColor(0,0xff,0,30));
}
