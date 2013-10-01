#ifndef KCILISTBUTTON_H
#define KCILISTBUTTON_H

#include <QLabel>
#include <QPalette>
#include <QHBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QColor>
#include <QPixmap>

class kciListButton : public QWidget
{
    Q_OBJECT
public:
    explicit kciListButton(QWidget *parent = 0);
    void setLabelIcon(const QString &fileName);
    void setLabelText(const QString &text);
    void setBackgroundColor(const QColor &NewColor);
    QColor getBackgroundColor();
    void setPushedColor(const QColor &NewColor);
    QColor getPushedColor();
    void setTextColor(const QColor &NewColor);
    QColor getTextColor();
    void setPushedTextColor(const QColor &NewColor);
    QColor getPushedTextColor();
    void setHoverColor(const QColor &NewColor);
    QColor getHoverColor();
    void setPushed(bool newValue);
    bool getPushed();

    QWidget *getUserInterfaceWidget() const;
    void setUserInterfaceWidget(QWidget *value);

signals:
    void click();

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *e);

public slots:

private:
    bool pushed;

    QLabel *lblButtonIcon, *lblButtonText;
    QHBoxLayout *mLayout;
    QPalette pal;
    QColor *bgColor, *pushedColor, *textColor, *pushedTextColor, *hoverColor;
    QWidget *UserInterfaceWidget;
};

#endif // KCILISTBUTTON_H
