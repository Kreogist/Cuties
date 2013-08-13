#include "kcilanguagemode.h"

kciLanguageMode::kciLanguageMode(QWidget *parent) :
    QObject(parent)
{
    m_compiler=NULL;
    m_highlighter=NULL;
    m_parent=qobject_cast<kciCodeEditor*>(parent);
    m_type=plainText;
    compilerReceiver=NULL;
    dbgReceiver=NULL;
    gdbInstance=NULL;

    Q_ASSERT(parent!=NULL);
}

void kciLanguageMode::setMode(const modeType &type)
{
    m_type=type;
}

void kciLanguageMode::compile()
{
    if(m_compiler==NULL)
    {
        qDebug()<<"compiler is NULL";
        return ;
    }

    if(compilerReceiver==NULL)
    {
        compilerReceiver=new compileOutputReceiver(this);
        compilerReceiver->connectCompiler(m_compiler);
    }

    stateLock.lockForWrite();
    state=compiling;
    stateLock.unlock();

    compilerReceiver->addForwardText();

    compilerFinishedConnection=connect(m_compiler,SIGNAL(finished(int)),
            this,SLOT(onCompileFinished()));

    m_compiler->startCompile(m_parent->filePath);
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
        m_compiler=new gcc(m_parent);
        m_highlighter=new cppHighlighter(m_parent);
    }
    else if(suffix.contains(_regexp_pascal))
    {
        if(m_type==pascal) //file type doesn't change,so return.
            return ;

        resetCompilerAndHighlighter();

        m_type=pascal;
        m_compiler=new fpc(m_parent);
        m_highlighter=new pascalHighlighter(m_parent);
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

void kciLanguageMode::onCompileFinished()
{
    stateLock.lockForWrite();
    state=compiled;
    stateLock.unlock();

    if((bool)compilerFinishedConnection)
        disconnect(compilerFinishedConnection);

    if(!compilerReceiver->hasCompileError())
    {
        emit compileSuccessfully(m_parent->execFileName);
    }
}

void kciLanguageMode::resetCompilerAndHighlighter()
{
    if(m_compiler!=NULL)
    {
        delete m_compiler;
        m_compiler=NULL;
    }
    if(m_highlighter!=NULL)
    {
        delete m_highlighter;
        m_highlighter=NULL;
    }
}
