#ifndef KCILINENUMPANEL_H
#define KCILINENUMPANEL_H

#include <QFont>
#include <QColor>

#include <QDebug>

#include "kcipanel.h"

class kciLinenumPanel : public kciPanel
{
    Q_OBJECT
public:
    explicit kciLinenumPanel(QWidget *parent = 0);    
    
signals:
    
public slots:

protected:
    void draw(QPainter *painter, QTextBlock *block,
              int x, int y, int w, int h,
              bool isCurrentLine);

private:
    QColor textColor;
    
};

#endif // KCILINENUMPANEL_H
