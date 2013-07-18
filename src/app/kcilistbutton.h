#ifndef KCILISTBUTTON_H
#define KCILISTBUTTON_H

#include <QLabel>
#include <QPalette>
#include <QHBoxLayout>
#include <QWidget>
#include <QPixmap>

class kciListButton : public QWidget
{
    Q_OBJECT
public:
    explicit kciListButton(QWidget *parent = 0);
    void setLabelIcon(const QString &fileName);
    void setLabelText(const QString &text);
    
signals:
    
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);


public slots:

private:
    QLabel *lblButtonIcon, *lblButtonText;
    QHBoxLayout *mLayout;
    QPalette pal;
};

#endif // KCILISTBUTTON_H
