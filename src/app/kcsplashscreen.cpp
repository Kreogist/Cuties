#include "kcsplashscreen.h"

KCSplashScreen::KCSplashScreen()
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    setContentsMargins(0,0,0,0);
    QTimer::singleShot(1000, this, SLOT(close()));
}
