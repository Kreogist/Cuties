#ifndef KCISTATUSBAR_H
#define KCISTATUSBAR_H

#include <QLabel>
#include <QStatusBar>

class kciStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    kciStatusBar(QWidget *parent);

public slots:
    void updateCursorPosition(int LineNum, int ColNum);

private:
    QLabel *lblCursorPosition;
};

#endif // KCISTATUSBAR_H
