#ifndef KCGRAPHICBUTTONBASE_H
#define KCGRAPHICBUTTONBASE_H

#include <QLabel>
#include <QWidget>

class KCGraphicButtonBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCGraphicButtonBase(QWidget *parent = 0);
    QPixmap getNormalGraphic() const;
    QPixmap getHoverGraphic() const;
    QPixmap getPressedGraphic() const;
    void setNormalGraphic(const QPixmap &value);
    void setHoverGraphic(const QPixmap &value);
    void setPressedGraphic(const QPixmap &value);

signals:
    void pressed();
    void clicked();

public slots:

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QLabel *buttonGraphic;
    QPixmap normalGraphic, hoverGraphic, pressedGraphic;
};

#endif // KCGRAPHICBUTTONBASE_H
