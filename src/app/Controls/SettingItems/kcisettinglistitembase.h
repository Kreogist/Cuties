#ifndef KCISETTINGLISTITEMBASE_H
#define KCISETTINGLISTITEMBASE_H

#include <QPalette>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QTimeLine>
#include <QMouseEvent>
#include <QDebug>

class kciSettingListItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit kciSettingListItemBase(QWidget *parent = 0);
    QLabel *Caption;

signals:
    void ValueChanged();
    void ItemGetFocus();
    void ItemLostFocus();

public slots:
    void enableEditMode();
    void disableEditMode();

private slots:
    void changeBackgroundAlpha(int alpha);

protected:
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private:
    QPalette pal;
    QTimeLine *animeFadeOut;
    bool itemSelected;
    bool blnEditMode;
};

#endif // KCISETTINGLISTITEMBASE_H
