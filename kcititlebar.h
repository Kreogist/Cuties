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

class kciTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit kciTitleBar(QWidget *parent = 0);
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString& mainIcon);
    
signals:
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool hasPressed;
    QPoint mousePosStart;
    QWidget *mainWindow;

    QToolButton *maximizeButton,*minimizeButton;
    QToolButton *closeButton;

    QHBoxLayout *hLayout;
    QLabel *titleLabel;
    QString windowTitle;

    QToolButton *mainButton;
    QIcon mainButtonIcon;
};

#endif // KCITITLEBAR_H
