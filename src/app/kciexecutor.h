#ifndef KCIEXECUTOR_H
#define KCIEXECUTOR_H

#include <QProcess>
#include <QThread>
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QReadWriteLock>

class kciExecutor;

class kciRunner : public QThread
{
    Q_OBJECT
public:
    explicit kciRunner(QObject *parent = 0);

public slots:
    void onReadyRead();

protected:
    void run();
};

class kciExecutor : public QObject
{
    Q_OBJECT
public:
    explicit kciExecutor(QObject *parent = 0);
    ~kciExecutor();

    void setTestCase(const QByteArray& input,const QByteArray& output);
    void setBackgroundExec(bool enabled);
    bool getBackgroundExec() const;
    bool isEnabledAutoInput() const;
    void setEnabledAutoInput(bool value);
    void exec(const QString& programPath);
    QByteArray getUserOutput();

private:
    QString path;
    QReadWriteLock lock;
    QByteArray m_input;
    QByteArray m_output;

    QReadWriteLock output_lock;
    QByteArray user_output;

    kciRunner *worker;
    QProcess* process;
    bool enabledBackExec;
    bool enabledAutoInput;

    friend class kciRunner;
};

#endif // KCIEXECUTOR_H
