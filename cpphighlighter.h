#ifndef CPPHIGHLIGHTER_H
#define CPPHIGHLIGHTER_H

#include <QList>
#include <QFont>
#include <QRegularExpression>
#include "highlighterbase.h"

class cppHighlighter : public highlighterBase
{
    Q_OBJECT
public:
    explicit cppHighlighter(QObject *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    QList<highlight_rule> rules;
    
};

#endif // CPPHIGHLIGHTER_H
