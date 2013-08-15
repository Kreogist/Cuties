#ifndef KCITEXTSEARCHWORKER_H
#define KCITEXTSEARCHWORKER_H

#include <QThread>
#include <QReadWriteLock>
#include <QRegularExpression>
#include <QStringMatcher>
#include <QTextDocument>
#include <QTextBlock>
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
    kciTextSearchWorker();

    bool needQuit;
    QReadWriteLock lock;

    QList<searchResult>* getResults();
    void setResults(QList<searchResult> *results);

    void setDocument(QTextDocument *value);
    void setIsCaseSensitive(bool value);
    virtual void setPattern(const QString& pattern) = 0;

protected:
    void run();
    void emitResult(int startPos, int length);
    void quitWhenRequest();
    virtual void match(const QString& text) = 0;
    virtual void setCaseSensitive(bool value) = 0;
    
private:
    QList<searchResult> *resultList;
    int currBlockNumber;
    bool isCaseSensitive;
    QTextDocument* document;
};

class kciTextSearchWorkerRegexp : public kciTextSearchWorker
{
public:
    void setPattern(const QString &pattern);

protected:
    void match(const QString& text);
    void setCaseSensitive(bool value);

private:
    QRegularExpression regexp;
};

class kciTextSearchWorkerStringMatcher : public kciTextSearchWorker
{
public:
    void setPattern(const QString& pattern);

protected:
    void match(const QString& text);
    void setCaseSensitive(bool value);

private:
    QStringMatcher matcher;
};

#endif // KCITEXTSEARCHWORKER_H
