#ifndef KCITEXTSEARCHER_H
#define KCITEXTSEARCHER_H

#include <QObject>
#include <QThread>
#include <QRegularExpression>
#include <QTextDocument>
#include <QTextBlock>
#include <QRegularExpressionMatch>
#include <QList>
#include <QPointer>
#include <QReadWriteLock>
#include <QDebug>

struct searchResult
{
    int lineNum;
    int startPos;
    int length;
};

class kciTextSearchWorker : public QThread
{
    Q_OBJECT
public:
    QRegularExpression regexp;
    QTextDocument* document;

protected:
    void run();

signals:
    void oneResultReady(searchResult result);

};

class kciTextSearcher : public QObject
{
    Q_OBJECT
public:
    enum seacherFlags
    {
        RegularExpress =   0x1,
        MatchCase =        0x2,
        WholeWord =        0x4
    };

    explicit kciTextSearcher(QObject *parent = 0);

    void search();

    void setDocument(QTextDocument *value);
    void setSubString(const QString &value);
    int getFlags() const;
    void setFlags(int value);

    QList<searchResult> resultList;
    QReadWriteLock lock;

signals:
    void finished();
    
public slots:
    void receiveSingleResult(searchResult result);
    
private:
    QString subString;
    QTextDocument* p_document;
    int flags;
    QPointer<kciTextSearchWorker> worker;
};

#endif // KCITEXTSEARCHER_H
