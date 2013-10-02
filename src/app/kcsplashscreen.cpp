#include "kcsplashscreen.h"

KCSplashScreen::KCSplashScreen()
{
    minimumMillisecondPerMessage=200;
}

void KCSplashScreen::showMessage(const QString &message,
                                 int alignment,
                                 const QColor &color)
{
    QTime count;
    count.start();
    QSplashScreen::showMessage(message,alignment,color);

    while(count.elapsed()<minimumMillisecondPerMessage)
        QApplication::processEvents();
}


int KCSplashScreen::getMinimumMillisecondPerMessage() const
{
    return minimumMillisecondPerMessage;
}

void KCSplashScreen::setMinimumMillisecondPerMessage(const int &ms)
{
    minimumMillisecondPerMessage = ms;
}
