#ifndef KCITITLEBAR_H
#define KCITITLEBAR_H

#include <QPoint>
#include <QMouseEvent>
#include <QToolButton>
#include <QStyle>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QString>
#include <QToolBar>
#include <QPalette>

class kciTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit kciTitleBar(QWidget *parent = 0);
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString& mainIcon);
    
signals:
    
public slots:

private slots:
    void _exchange_button_state();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    bool hasPressed;
    bool isShowingNormalButton;   //false when show minimizeButton, true when show normalButton
    QPoint mousePosStart;
    QWidget *mainWindow;

    QToolButton *maximizeButton,*minimizeButton;
    QToolButton *closeButton;

    QHBoxLayout *hLayout;
    QLabel *titleLabel;
    QString windowTitle;

    QToolButton *mainButton;
    QIcon mainButtonIcon,normalButtonIcon,maximizeButtonIcon;
};

#endif // KCITITLEBAR_H
