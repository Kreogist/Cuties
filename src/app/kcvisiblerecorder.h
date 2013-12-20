#ifndef KCVISIBLERECORDER_H
#define KCVISIBLERECORDER_H

#include <QObject>
#include <QList>
#include <QWidget>

class KCVisibleRecorder : public QObject
{
    Q_OBJECT
public:
    explicit KCVisibleRecorder(QObject *parent = 0);

signals:

public slots:

private:
    ;
};

#endif // KCVISIBLERECORDER_H
