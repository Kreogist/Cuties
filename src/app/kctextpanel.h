#ifndef KCTEXTPANEL_H
#define KCTEXTPANEL_H

#include <QWidget>
#include <QPaintEvent>
#include <QTextBlock>
#include <QTextCursor>

class KCTextPanel : public QWidget
{
    Q_OBJECT
public:
    explicit KCTextPanel(QWidget *parent = 0);
    virtual void drawContent(int x,
                             int y,
                             int width,
                             int height,
                             QTextBlock block,
                             QTextCursor textCursor)=0;
    virtual void setPanelWidth(int lineNumberPanelWidth)=0;
    QTextBlock getFirstBlock() const;
    void setFirstBlock(const QTextBlock &value);
    QTextBlock getLastBlock() const;
    void setLastBlock(const QTextBlock &value);

signals:
    void requireRepaintLineNumber(KCTextPanel *panel,
                                  QPaintEvent *event);

protected:
    void paintEvent(QPaintEvent *event);
    QTextBlock firstBlock;
    QTextBlock lastBlock;

};
#endif // KCTEXTPANEL_H
