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

    void setShowCodeLevel(bool value);

signals:
    void requireFoldStartAt(int blockIndex);
    void requireUnfoldStartAt(int blockIndex);

public slots:

protected:
    void panelItemClickEvent(QTextBlock *block,
                             KCTextBlockData *data);

private:
    QPixmap foldMark, foldEndMark, foldedMark;
    QPixmap compileErrorMark;
    int foldMarkWidth, foldMarkHeight;
    int errorMarkWidth, errorMarkHeight;
    bool showCodeLevel=false;
};

#endif // KCUNIBODYPANEL_H
