#ifndef KCVISIBLERECORDER_H
#define KCVISIBLERECORDER_H

#include <QObject>
#include <QList>
#include <QWidget>

struct visibleRecordItem
{
    QWidget *widget;
    bool recordVisible;
};

class KCVisibleRecorder : public QObject
{
    Q_OBJECT
public:
    static KCVisibleRecorder *getInstance();
    void clearList();
    int addWidget(QWidget *widget);
    bool getWidgetVisible(int widgetIndex);
    void backupWidgetVisible();
    void restoreWidgetVisible();
    void hideAll();

signals:

public slots:

private:
    KCVisibleRecorder();
    static KCVisibleRecorder *instance;
    QList<visibleRecordItem> recorderList;
};

#endif // KCVISIBLERECORDER_H
