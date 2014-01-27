#ifndef KCLINENUMBERPANEL_H
#define KCLINENUMBERPANEL_H

#include "kctextpanel.h"

class KCLineNumberPanel : public KCTextPanel
{
    Q_OBJECT
public:
    explicit KCLineNumberPanel(QWidget *parent = 0);
    void drawContent(int x, int y, int width, int height, QTextBlock block, QTextCursor cursor);
    void setPanelWidth(int lineNumberPanelWidth);

signals:

public slots:

private:
    QColor textColor;
};

#endif // KCLINENUMBERPANEL_H
