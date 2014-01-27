#ifndef KCTEXTPANEL_H
#define KCTEXTPANEL_H

#include <QWidget>
#include <QPaintEvent>

class KCTextPanel : public QWidget
{
    Q_OBJECT
public:
    explicit KCTextPanel(QWidget *parent = 0);

    QSize sizeHint() const {
        return QSize(100, 0);
    }
signals:
    void requireRepaintLineNumber(QPaintEvent *event);

protected:
    void paintEvent(QPaintEvent *event) {
        emit requireRepaintLineNumber(event);
    }

};

class KCPanelManager : public QWidget
{
    Q_OBJECT
public:
    explicit KCPanelManager(QWidget *parent = 0);

signals:

private:
    ;
};

#endif // KCTEXTPANEL_H
