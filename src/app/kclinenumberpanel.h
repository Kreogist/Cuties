#ifndef KCLINENUMBERPANEL_H
#define KCLINENUMBERPANEL_H

#include "kctextpanel.h"

class KCLineNumberPanel : public KCTextPanel
{
    Q_OBJECT
public:
    explicit KCLineNumberPanel(QWidget *parent = 0);
    void drawContent(int x, int y, int width, int height,
                     QTextBlock *block, KCTextBlockData *data, QTextCursor cursor);
    void setPanelWidth(int lineNumberPanelWidth);

signals:
    void requireSelectLine(int blockNumber);

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QColor textColor;
    QPoint pressedPos;
    bool isPressed;
};

#endif // KCLINENUMBERPANEL_H
