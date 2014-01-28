#ifndef KCDEBUGMARKPANEL_H
#define KCDEBUGMARKPANEL_H

#include <QMouseEvent>

#include "kctextpanel.h"

class KCDebugMarkPanel : public KCTextPanel
{
    Q_OBJECT
public:
    explicit KCDebugMarkPanel(QWidget *parent = 0);
    void drawContent(int x, int y, int width, int height,
                     QTextBlock *block, KCTextBlockData *data, QTextCursor cursor);
    void setPanelWidth(int lineNumberPanelWidth);
    void setDebugCursor(int lineNum);
    void resetDebugCursor();

signals:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPixmap markPix, debugArrow;
    QPoint pressedPos;
    bool isPressed;
    int markPanelHeight;
    int debugCursorLine=-1;
};

#endif // KCDEBUGMARKPANEL_H
