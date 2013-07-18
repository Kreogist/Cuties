#ifndef KCILISTBUTTON_H
#define KCILISTBUTTON_H

#include <QLabel>
#include <QPalette>
#include <QHBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QPixmap>

class kciListButton : public QWidget
{
    Q_OBJECT
public:
    explicit kciListButton(QWidget *parent = 0);
    void setLabelIcon(const QString &fileName);
    void setLabelText(const QString &text);
    
signals:
    void click();
    
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *e);

public slots:

private:
    QLabel *lblButtonIcon, *lblButtonText;
    QHBoxLayout *mLayout;
    QPalette pal;
};

#endif // KCILISTBUTTON_H
