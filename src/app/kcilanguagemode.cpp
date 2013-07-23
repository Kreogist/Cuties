#include "kcilanguagemode.h"

kciLanguageMode::kciLanguageMode(QWidget *parent) :
    QObject(parent)
{
    m_compiler=NULL;
    m_executor=new kciExecutor(this);
    m_highlighter=NULL;
    m_parent=qobject_cast<kciCodeEditor*>(parent);
    m_type=plainText;
    receiver=NULL;

    Q_ASSERT(parent!=NULL);
}

void kciLanguageMode::setMode(const modeType &type)
{
    m_type=type;
}

void kciLanguageMode::compile()
{
    if(m_compiler==NULL)
        return ;

    if(receiver==NULL)
    {
        receiver=new compileOutputReceiver(this);
    }
    receiver->connectCompiler(m_compiler);

    //Prepare Compiler
    receiver->addText(QTime::currentTime().toString("hh:mm:ss") +
                      " " +
                      tr("Preparing Compiler.")+
                      "\n");
    //Get Compiler Info.
    receiver->addText(QTime::currentTime().toString("hh:mm:ss") +
                      " " +
                      tr("Current Compiler Details:\n") +
                      m_compiler->compilerName() + " " +
                      m_compiler->version() +
                      "\n");

    //Output Compile Info:
    receiver->addText(QTime::currentTime().toString("hh:mm:ss") +
                      " " +
                      tr("Compile Command:") +
                      "\n");
    //compile command will be output when compiler emit signal compileinfo

    stateLock.lockForWrite();
    state=compiling;

    connect(m_compiler,SIGNAL(finished(int)),
            this,SLOT(onCompileFinished()));

    m_compiler->startCompile(m_parent->filePath);
    stateLock.unlock();
}

void kciLanguageMode::setFileSuffix(const QString& suffix)
{
    QRegularExpression _regexp_cpp("(h|hpp|rh|hh|c|cpp|cc|cxx|c++|cp)",
                                   QRegularExpression::CaseInsensitiveOption);
    QRegularExpression _regexp_pascal("pas",
                                      QRegularExpression::CaseInsensitiveOption);

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

    if(suffix.contains(_regexp_cpp))
    {
        m_type=cpp;
        m_compiler=new gcc(m_parent);
        m_highlighter=new cppHighlighter(m_parent);
        m_highlighter->setDocument(m_parent->document);
    }
    else if(suffix.contains(_regexp_pascal))
    {
        m_type=pascal;
        m_compiler=new fpc(m_parent);
        m_highlighter=new pascalHighlighter(m_parent);
        m_highlighter->setDocument(m_parent->document);
    }
    else
        m_type=plainText;


    if(m_compiler==NULL)
        return ;
}

compileOutputReceiver *kciLanguageMode::getReceiver() const
{
    return receiver;
}

void kciLanguageMode::onCompileFinished()
{
    stateLock.lockForWrite();
    state=compiled;
    stateLock.unlock();
    if(!receiver->hasCompileError())
    {
        emit compileSuccessfully(m_parent->execFileName);
    }
}

kciExecutor* kciLanguageMode::getExecutor()
{
    return m_executor;
}
