#ifndef HIGHLIGHTERGLOBAL_H
#define HIGHLIGHTERGLOBAL_H

struct highlight_rule
{
    QString type_name;

    QRegularExpression regexp;
};

#endif // HIGHLIGHTERGLOBAL_H
