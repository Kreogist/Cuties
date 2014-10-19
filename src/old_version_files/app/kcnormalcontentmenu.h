#ifndef KCNORMALCONTENTMENU_H
#define KCNORMALCONTENTMENU_H

#include <QPropertyAnimation>
#include <QShowEvent>
#include <QMenu>

class KCNormalContentMenu : public QMenu
{
    Q_OBJECT
public:
    explicit KCNormalContentMenu(QWidget *parent = 0);

signals:

public slots:

protected:
    void showEvent(QShowEvent *e);

private:
    QPropertyAnimation *showAnimation;
};

#endif // KCNORMALCONTENTMENU_H
