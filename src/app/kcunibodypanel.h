#ifndef KCUNIBODYPANEL_H
#define KCUNIBODYPANEL_H

#include "kctextpanel.h"

class KCUnibodyPanel : public KCTextPanel
{
    Q_OBJECT
public:
    explicit KCUnibodyPanel(QWidget *parent = 0);
    void drawContent(int x, int y, int width, int height,
                     QTextBlock *block, KCTextBlockData *data, QTextCursor cursor);
    void setPanelWidth(int lineNumberPanelWidth);

signals:
    void requireFoldStartAt(int blockIndex);
    void requireUnfoldStartAt(int blockIndex);

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPixmap foldMark, foldEndMark, foldedMark;
    QPixmap compileErrorMark;
    QPoint pressedPos;
    bool isPressed=false;
    int foldMarkWidth, foldMarkHeight;
    int errorMarkWidth, errorMarkHeight;
};

#endif // KCUNIBODYPANEL_H
