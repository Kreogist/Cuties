#include "kcilanguagemode.h"

kciLanguageMode::kciLanguageMode(QWidget *parent) :
    QObject(parent)
{
    compiler=NULL;
    m_highlighter=NULL;
    m_parent=qobject_cast<kciCodeEditor*>(parent);
    m_type=plainText;
    compilerReceiver=NULL;
    dbgReceiver=NULL;
    gdbInstance=NULL;

    Q_ASSERT(m_parent!=NULL);
}

void kciLanguageMode::setMode(const modeType &type)
{
    m_type=type;
}

void kciLanguageMode::compile()
{
    if(compiler==NULL)
    {
        qDebug()<<"compiler is NULL";
        return ;
    }

    if(compilerReceiver==NULL)
    {
        compilerReceiver=new compileOutputReceiver(this);
        connectCompilerAndOutputReceiver();
    }

    stateLock.lockForWrite();
    state=compiling;
    stateLock.unlock();

    compilerReceiver->addForwardText();

    compilerFinishedConnection=connect(compiler,&compilerBase::compileFinished,
            this,&kciLanguageMode::onCompileFinished);

    compiler->startCompile(m_parent->filePath);
}

void kciLanguageMode::connectCompilerAndOutputReceiver()
{
    connectionHandles.disConnectAll();

    compilerReceiver->setCompilerVersionString(compiler->compilerName()+
                                               " "+
                                               compiler->version());

    //Output Compile Message:
    connectionHandles+=connect(compiler,&compilerBase::compileCmd,
                               compilerReceiver,&compileOutputReceiver::addText);
    connectionHandles+=connect(compiler,&compilerBase::output,
                               compilerReceiver,&compileOutputReceiver::addText);
    connectionHandles+=connect(compiler,&compilerBase::compileError,
                               compilerReceiver,&compileOutputReceiver::onCompileMsgReceived);
    connectionHandles+=connect(compiler,&compilerBase::compileFinished,
                               compilerReceiver,&compileOutputReceiver::onCompileFinished);
}

void kciLanguageMode::setFileSuffix(const QString& suffix)
{
    QRegularExpression _regexp_cpp("(h|hpp|rh|hh|c|cpp|cc|cxx|c++|cp)",
                                   QRegularExpression::CaseInsensitiveOption);
    QRegularExpression _regexp_pascal("pas",
                                      QRegularExpression::CaseInsensitiveOption);

    if(suffix.contains(_regexp_cpp))
    {
        if(m_type==cpp) //file type doesn't change,so return.
            return ;

        resetCompilerAndHighlighter();

        m_type=cpp;
        compiler=new gcc(this);
        m_highlighter=new cppHighlighter(this);
    }
    else if(suffix.contains(_regexp_pascal))
    {
        if(m_type==pascal) //file type doesn't change,so return.
            return ;

        resetCompilerAndHighlighter();

        m_type=pascal;
        compiler=new fpc(this);
        m_highlighter=new pascalHighlighter(this);
    }
    else
        m_type=plainText;


    if(m_highlighter==NULL)
        return ;
    m_highlighter->setDocument(m_parent->document);
}

compileOutputReceiver* kciLanguageMode::getCompilerReceiver() const
{
    return compilerReceiver;
}

dbgOutputReceiver* kciLanguageMode::getDbgReceiver() const
{
    return dbgReceiver;
}

gdb* kciLanguageMode::getGdbInstance() const
{
    return gdbInstance;
}

gdb* kciLanguageMode::startDebug()
{
    if(gdbInstance == NULL)
        gdbInstance=new gdb(this);

    if(dbgReceiver == NULL)
        dbgReceiver=new dbgOutputReceiver(this);

    dbgReceiver->connectGDB(gdbInstance);
    gdbInstance->runGDB(m_parent->execFileName);

    return gdbInstance;
}

void kciLanguageMode::onCompileFinished(bool hasError)
{
    stateLock.lockForWrite();
    state=compiled;
    stateLock.unlock();

    if((bool)compilerFinishedConnection)
        disconnect(compilerFinishedConnection);

    if(!hasError)
    {
        emit compileSuccessfully(m_parent->execFileName);
    }
}

void kciLanguageMode::resetCompilerAndHighlighter()
{
    if(compiler!=NULL)
    {
        compiler->deleteLater();
        compiler=NULL;
    }
    if(m_highlighter!=NULL)
    {
        m_highlighter->deleteLater();
        m_highlighter=NULL;
    }
}
