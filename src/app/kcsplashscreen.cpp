#include "kcsplashscreen.h"

KCSplashScreen::KCSplashScreen()
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}
