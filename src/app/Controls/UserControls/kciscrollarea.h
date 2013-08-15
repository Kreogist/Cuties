#ifndef KCISCROLLAREA_H
#define KCISCROLLAREA_H

#include <QScrollBar>
#include <QWidget>

class kciScrollArea : public QWidget
{
    Q_OBJECT
public:
    explicit kciScrollArea(QWidget *parent = 0);
    void setWidget(QWidget *widget);
    
signals:
    
public slots:

private:
    QScrollBar *horizontalScrollBar,
               *verticalScrollBar;
};

#endif // KCISCROLLAREA_H
