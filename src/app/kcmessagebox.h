#ifndef KCMESSAGEBOX_H
#define KCMESSAGEBOX_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTimerEvent>

class KCMessageBoxTitle : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxTitle(QWidget *parent = 0);
    void setTitleText(QString newTitleText);

private:
    QLabel *titleCaption;
};

class KCMessageBoxPanel : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxPanel(QWidget *parent = 0);

private:

};

class KCMessageBoxContent : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxContent(QWidget *parent = 0);
    ~KCMessageBoxContent();
    void addText(QString displayText);

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *contentLayout;
};

class KCMessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBox(QWidget *parent = 0);
    void addText(QString displayText);

signals:

public slots:
    void show();
    void setTitle(QString messageBoxTitle);

private slots:

private:
    QVBoxLayout *mainLayout;
    QPropertyAnimation *widthExpand;

    //Basic widgets
    KCMessageBoxTitle *titleWidget;
    KCMessageBoxPanel *panelWidget;
    KCMessageBoxContent *contentWidget;
};

#endif // KCMESSAGEBOX_H
