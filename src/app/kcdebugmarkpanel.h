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
    void panelItemClickEvent(QTextBlock *block,
                               KCTextBlockData *data);

private:
    QPixmap markPix, debugArrow;
    int markPanelHeight;
    int debugCursorLine=-1;
};

#endif // KCDEBUGMARKPANEL_H
