#ifndef KCIEXECUTOR_H
#define KCIEXECUTOR_H

#include <QProcess>
#include <QThread>
#include <QByteArray>
#include <QObject>

class kciExecutor : public QObject
{
    Q_OBJECT
public:
    explicit kciExecutor(QObject *parent = 0);
    void setInputData(const QByteArray& input);
    void setInputFile(QString File);
    
signals:
    
public slots:
    
};

#endif // KCIEXECUTOR_H
