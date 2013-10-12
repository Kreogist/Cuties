#ifndef KCMESSAGEBOX_H
#define KCMESSAGEBOX_H

//Base Dialog
#include <QDialog>
#include <QPainter>
#include <QPalette>

//Display Graphic
#include <QLabel>
#include <QPixmap>

//Sort Widget/Scale Image.
#include <QVBoxLayout>

//Animation Framework.
#include <QPropertyAnimation>

//Debug
#include <QDebug>

class KCMessageBoxTitle : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxTitle(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QLabel *backPixDisplay;
};

class KCMessageBoxPanel : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxPanel(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QLabel *backPixDisplay;
};

class KCMessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit KCMessageBox(QWidget *parent = 0);
    void startAnime();

signals:

public slots:

private slots:
    void heightExpandAnime();

private:
    KCMessageBoxTitle *titleWidget;
    QVBoxLayout *mainLayout;
    QRect parentGeometry;
};

#endif // KCMESSAGEBOX_H
