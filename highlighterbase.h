#ifndef HIGHLIGHTERBASE_H
#define HIGHLIGHTERBASE_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QMap>
#include <QString>
#include <QTextCharFormat>
#include <QFile>
#include <QString>
#include <QSet>
#include <QDebug>

struct highlight_rule
{
    QString type_name;

    QRegularExpression regexp;
};

class highlighterBase : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit highlighterBase(QObject *parent = 0);

    const QTextCharFormat& operator[] (const QString& typeName);
    const QTextCharFormat& getTextCharFormat(const QString& typeName);

private:
    static QMap<QString, QTextCharFormat> map;
    static bool isInited;

    bool parseStyleFileLine(char *str_line);
    
};

#endif // HIGHLIGHTERBASE_H
