#ifndef KCIEXECUTOR_H
#define KCIEXECUTOR_H

#include <QProcess>
#include <QThread>
#include <QByteArray>
#include <QObject>
#include <QStringList>

class kciExecutor : public QObject
{
    Q_OBJECT
public:
    explicit kciExecutor(QObject *parent = 0);
    int addTestCase(const QByteArray& input,const QByteArray& output);
    void removeInputData(const int& inputDataNum);
    void setInputFiles(const QStringList& Files);
    
signals:
    
public slots:

private:
    struct TestCase
    {
        int testCaseNumber;
        QByteArray input;
        QByteArray output;
    };
    QStringList inputFilesPath;
    QList<TestCase> testData;
    int testCaseNum;
};

#endif // KCIEXECUTOR_H
