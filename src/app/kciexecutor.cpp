#include "kciexecutor.h"

#ifdef Q_OS_WIN32
const QString console_runner_path("KciConsoleRunner.exe");
#else
const QString console_runner_path("KciConsoleRunner");
#endif

kciRunner::kciRunner(QObject *parent):
    QThread(parent)
{
}

void kciRunner::run()
{
    kciExecutor *p=qobject_cast<kciExecutor*>(parent());

    if(p!=NULL)
    {
        p->lock.lockForRead();

        if(p->process!=NULL)
        {
            p->process->kill();
            p->process->waitForFinished();
            delete p->process;
        }

        if(p->enabledBackExec)
        {
            p->process=new QProcess(this);
            p->process->setReadChannelMode(QProcess::MergedChannels);
            connect(p->process,SIGNAL(readyRead()),
                    this,SLOT(onReadyRead()));
            p->process->start(p->path);
        }
        else
        {
            QStringList arg;
            arg<<p->path;
            p->process=new QProcess(this);
            p->process->startDetached(console_runner_path,arg);

        }

        if(p->enabledAutoInput)
            p->process->write(p->m_input);

        p->lock.unlock();
    }
}

void kciRunner::onReadyRead()
{
    kciExecutor *p=qobject_cast<kciExecutor*>(parent());
    if(p!=NULL)
    {
        p->output_lock.lockForWrite();

        p->user_output+=p->process->readAll();

        p->output_lock.unlock();
    }
}

kciExecutor::kciExecutor(QObject *parent) :
    QObject(parent)
{
    enabledBackExec=false;
}

kciExecutor::~kciExecutor()
{
    if(process!=NULL)
    {
        process->kill();
        process->waitForFinished();
        delete process;
    }

    if(worker!=NULL)
    {
        worker->quit();
        worker->wait();
        delete worker;
    }
}

void kciExecutor::setTestCase(const QByteArray &input, const QByteArray &output)
{
    m_input=input;
    m_output=output;
    worker=NULL;
    process=NULL;
}

bool kciExecutor::getBackgroundExec() const
{
    return enabledBackExec;
}

void kciExecutor::setBackgroundExec(bool value)
{
    lock.lockForWrite();
    enabledBackExec = value;
    lock.unlock();
}

bool kciExecutor::isEnabledAutoInput() const
{
    return enabledAutoInput;
}

void kciExecutor::setEnabledAutoInput(bool value)
{
    lock.lockForWrite();
    enabledAutoInput = value;
    lock.unlock();
}

void kciExecutor::exec(const QString &programPath)
{
    lock.lockForWrite();
    path=programPath;

    if(worker!=NULL)
    {
        worker->quit();
        worker->wait();
        delete worker;
    }

    worker=new kciRunner(this);
    worker->start();

    lock.unlock();
}

QByteArray kciExecutor::getUserOutput()
{
    output_lock.lockForRead();
    QByteArray ret = user_output;
    output_lock.unlock();
    return ret;
}
