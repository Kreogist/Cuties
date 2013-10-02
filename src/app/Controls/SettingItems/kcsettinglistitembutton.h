#ifndef KCSETTINGLISTITEMBUTTON_H
#define KCSETTINGLISTITEMBUTTON_H

#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QMouseEvent>

class KCSettingListItemButton : public QWidget
{
    Q_OBJECT
public:
    explicit KCSettingListItemButton(QWidget *parent = 0);
    void setButtonText(QString newButtonText);

signals:
    void buttonPressed();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

public slots:

private:
    QLabel *Caption;
    QHBoxLayout *mainLayout;
    QPalette pal;
};

#endif // KCSETTINGLISTITEMBUTTON_H
