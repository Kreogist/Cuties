#include "kciexecutor.h"

kciExecutor::kciExecutor(QObject *parent) :
    QObject(parent)
{
    testCaseNum=0;
}

void kciExecutor::setInputFiles(const QStringList &Files)
{
    inputFilesPath=Files;
}

int kciExecutor::addTestCase(const QByteArray &input, const QByteArray &output)
{
    TestCase test;
    test.input=input;
    test.output=output;
    test.testCaseNumber=testCaseNum;
    testData<<test;

    return testCaseNum++;;
}

void kciExecutor::removeInputData(const int &inputDataNum)
{
    for(auto i=testData.begin(),end=testData.end();
        i!=end;
        i++)
    {
        if(i->testCaseNumber == inputDataNum)
        {
            testData.erase(i);
            return ;
        }
    }
}
