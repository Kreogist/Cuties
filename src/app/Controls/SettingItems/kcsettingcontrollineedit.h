#ifndef KCSETTINGCONTROLLINEEDIT_H
#define KCSETTINGCONTROLLINEEDIT_H

#include <QLineEdit>

class KCSettingControlLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit KCSettingControlLineEdit(QWidget *parent = 0);

signals:
    void clicked();

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // KCSETTINGCONTROLLINEEDIT_H
