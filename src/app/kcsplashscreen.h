#ifndef KCSPLASHSCREEN_H
#define KCSPLASHSCREEN_H

#include <QPainter>
#include <QSplashScreen>
#include <QTime>
#include <QApplication>

class KCSplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    KCSplashScreen();

    int getMinimumMillisecondPerMessage() const;
    void setMinimumMillisecondPerMessage(const int &ms);

signals:

public slots:
    void showMessage(const QString &message,
                     int alignment=Qt::AlignLeft,
                     const QColor &color=Qt::black);

private:
    int minimumMillisecondPerMessage;
};

#endif // KCSPLASHSCREEN_H
