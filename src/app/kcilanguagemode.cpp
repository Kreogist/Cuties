#include "kcilanguagemode.h"

kciLanguageMode::kciLanguageMode(QWidget *parent) :
    QObject(parent)
{
    m_compiler=NULL;
    m_executor=new kciExecutor(this);
    m_highlighter=NULL;
    m_parent=qobject_cast<kciCodeEditor*>(parent);
    m_type=plainText;

    Q_ASSERT(parent!=NULL);
}

kciExecutor* kciLanguageMode::getExecutor()
{
    return m_executor;
}

compilerBase* kciLanguageMode::getCompiler()
{
    return m_compiler;
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
}

