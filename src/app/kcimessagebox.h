#ifndef KCIMESSAGEBOX_H
#define KCIMESSAGEBOX_H

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

class kciMessageBoxTitle : public QWidget
{
    Q_OBJECT
public:
    explicit kciMessageBoxTitle(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QLabel *backPixDisplay;
};

class kciMessageBoxPanel : public QWidget
{
    Q_OBJECT
public:
    explicit kciMessageBoxPanel(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QLabel *backPixDisplay;
};

class kciMessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit kciMessageBox(QWidget *parent = 0);
    void startAnime();
    
signals:

public slots:

private slots:
    void heightExpandAnime();

private:
    kciMessageBoxTitle *titleWidget;
    QVBoxLayout *mainLayout;
    QRect parentGeometry;
};

#endif // KCIMESSAGEBOX_H
