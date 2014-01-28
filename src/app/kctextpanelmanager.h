#ifndef KCTEXTPANELMANAGER_H
#define KCTEXTPANELMANAGER_H

#include <QHBoxLayout>
#include <QWidget>
#include <QPaintEvent>

#include "kctextpanel.h"

class KCTextPanelManager : public QWidget
{
    Q_OBJECT
public:
    explicit KCTextPanelManager(QWidget *parent = 0);
    void addPanel(KCTextPanel *panel);
    int resizePanel(int lineNumberPanelWidth);

signals:
    void requirePaintPanel(KCTextPanel *panel,
                           QPaintEvent *event);

public slots:
    void updateAllPanel();

protected:

private:
    QHBoxLayout *layout;

};

#endif // KCTEXTPANELMANAGER_H
