#ifndef GDBMIVALUE_H
#define GDBMIVALUE_H

#include <QString>
#include <QList>

#include <QDebug>

class GdbMiValue
{
public:
    enum ValueType
    {
        Invalid,
        Const,
        Tuple,
        List
    };

    GdbMiValue():type(Invalid){}

    void build(const QChar* &begin, const QChar* &end);
    QString getName() const;

    inline ValueType getType(){return type;}

    QString getValue() const;

    GdbMiValue operator [](const char *_str_name) const;
    GdbMiValue& operator += (const GdbMiValue& child);

private:
    void parseConst(const QChar* &begin, const QChar* &end);
    void parseList(const QChar* &begin, const QChar* &end);
    void parseTuple(const QChar* &begin, const QChar* &end);

    ValueType type;
    QString name;
    QString value;
    QList<GdbMiValue> children;
};

#endif // GDBMIVALUE_H
