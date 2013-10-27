#ifndef KCSETTINGLISTITEMBASE_H
#define KCSETTINGLISTITEMBASE_H

#include <QPalette>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QTimeLine>
#include <QMouseEvent>
#include <QDebug>

class KCSettingListItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCSettingListItemBase(QWidget *parent = 0);
    QLabel *captionText;
    bool getEditMode();
    bool getItemSelectedStatus();

signals:
    void valueChanged();
    void itemGetFocus();
    void itemLostFocus();

public slots:
    void setEditMode(bool value);
    void setItemSelected(bool value);
private slots:
    void changeBackgroundAlpha(int alpha);

protected:
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private:
    QPalette pal;
    QTimeLine *animationBackgroundFadeOut;
    bool itemSelected;
    bool editMode;
};

#endif // KCSETTINGLISTITEMBASE_H
