#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

#include "kccodecompileprogress.h"

KCCodeCompileProgress::KCCodeCompileProgress(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("KCCodeCompileProgress");
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    QVBoxLayout *compileProgressLayout=new QVBoxLayout(this);
    compileProgressLayout->setContentsMargins(0,0,0,0);
    compileProgressLayout->setSpacing(0);
    setLayout(compileProgressLayout);

    compileProgressDisplay=new QProgressBar(this);
    compileProgressLayout->addWidget(compileProgressDisplay);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    setGraphicsEffect(wndShadow);
}
