#ifndef KCISTATUSBAR_H
#define KCISTATUSBAR_H

#include <QLabel>
#include <QDebug>
#include <QStatusBar>

#include "kcistatuscursorinfo.h"

class kciStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    kciStatusBar(QWidget *parent);
    void showGotoBar(int currentValue, int MaxValue);

signals:
    void newUpdateCursorPosition(int LineNum, int ColNum);
    void ToNewPosition(int NewLineNum);

public slots:
    void updateCursorPosition(int LineNum, int ColNum);

private:
    kciStatusCursorInfo *kscCursorPosition;
};

#endif // KCISTATUSBAR_H
