#ifndef KCISETTINGLISTITEMBUTTON_H
#define KCISETTINGLISTITEMBUTTON_H

#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QMouseEvent>

class kciSettingListItemButton : public QWidget
{
    Q_OBJECT
public:
    explicit kciSettingListItemButton(QWidget *parent = 0);
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

#endif // KCISETTINGLISTITEMBUTTON_H
