#include "kcsplashscreen.h"

KCSplashScreen::KCSplashScreen()
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    QTimer::singleShot(1000, this, SLOT(close()));
}
