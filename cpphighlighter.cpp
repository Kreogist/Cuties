#include "cpphighlighter.h"

cppHighlighter::cppHighlighter(QObject *parent) :
    highlighterBase(parent)
{
    int i;
    //tpye
    highlight_rule datatype;
    datatype.regexp.setPattern(
         "\\b(bool|char|double|float|int|long|short|signed|unsigned|void|wchar_t|char16_t|char32_t|nullptr)\\b");
    datatype.type_name="datatype";
    rules<<datatype;

    //other keywords
    highlight_rule keywords;
    QStringList _keyword;
    _keyword<<"__asm|__cdecl|__declspec|__export|__far16"
    <<"__fastcall|__fortran|__import"
    <<"__pascal|__rtti|__stdcall|_asm|_cdecl"
    <<"__except|_export|_far16|_fastcall"
    <<"__finally|_fortran|_import|_pascal|_stdcall|__thread|__try|asm|auto"
    <<"break|case|catch|cdecl|const|continue|default"
    <<"do|else|enum|extern|for|goto"
    <<"if|pascal"
    <<"register|return|sizeof|static"
    <<"struct|switch"
    <<"typedef|union"
    <<"volatile|while""class|const_cast|delete"
    <<"dynamic_cast|explicit|false|friend"
    <<"inline|mutable|namespace|new|operator|private|protected"
    <<"public|reinterpret_cast|static_cast"
    <<"template|this|throw|true"
    <<"try|typeid|typename"
    <<"using|virtual";
    keywords.type_name="keyword";

    for(i=0;i<_keyword.size();i++)
    {
        keywords.regexp.setPattern(QString("\\b(")+_keyword[i]+QString(")\\b"));
        rules<<keywords;
    }

    highlight_rule preproc;
    preproc.type_name="preproc";
    preproc.regexp.setPattern("^[[:blank:]]*#([[:blank:]]*[[:word:]]*)");
    rules<<preproc;

    highlight_rule label;
    label.type_name="label";
    label.regexp.setPattern("^[[:blank:]]*[[:alnum:]]+:[[:blank:]]*\\z");
    rules<<label;

    highlight_rule number;
    number.type_name="number";
    number.regexp.setPattern("\\<[+-]?((0x[[:xdigit:]]+)|(([[:digit:]]*\\.)?[[:digit:]]+([eE][+-]?[[:digit:]]+)?))u?((int(?:8|16|32|64))|L)?\\>'");
    rules<<number;

    highlight_rule todo;
    todo.type_name="todo";
    todo.regexp.setPattern("(TODO|FIXME|BUG)([:]?)");
    rules<<todo;
}

void cppHighlighter::highlightBlock(const QString &text)
{
    for(int i=0;i<rules.size();i++)
    {
        QRegularExpressionMatch match=rules[i].regexp.match(text);
        if(match.hasMatch())
            setFormat(match.capturedStart(),
                      match.capturedEnd(),
                      this->getTextCharFormat(rules[i].type_name));
    }
}
