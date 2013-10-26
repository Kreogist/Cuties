#ifndef KCMESSAGEBOX_H
#define KCMESSAGEBOX_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>

class KCMessageBoxTitle : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxTitle(QWidget *parent = 0);

private:

};

class KCMessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBox(QWidget *parent = 0);

signals:

public slots:

private slots:

private:
    QVBoxLayout *mainLayout;
    QPropertyAnimation *widthExpand;
};

#endif // KCMESSAGEBOX_H
