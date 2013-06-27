#ifndef GDB_H
#define GDB_H


#include <QProcess>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QCharRef>
#include <QVector>
#include <QDebug>

struct bkpt_struct
{
    int number;
    QString type;
    bool enabled;
    QString disp;
    QString addr;
    QString func;
    QString file;
    QString fullName;
    int line;
    QString threadGroups;
    int times;
    QString original_location;
};

class gdb : public QProcess
{
    Q_OBJECT
public:
    explicit gdb(QObject *parent = 0);

    static void setGDBPath(const QString& path);
    static bool checkGDB();
    static void isGDBPathRight();

    bool runGDB(const QString& filePath);
    void quitGDB();

    //breakpoint
    void setBreakPoint(const int &number, const int &count);
    void setBreakPoint(const QString& functionName);
    void setBreakCondition(const int &lineNum, const QString& expr);

    //watchpoint
    void setWatchPoint(const QString& var);

    //Program Control
    void execRun();
    void execAbort();
    void execContinue();
    void execFinish();
    void execNext();
    void execReturn();
    void execStepi();
    void execUntil(const QString& location);

    //Stack Manipulation
    void stackListLocals();
    
    const QVector<bkpt_struct>* getBkptVec() const;

signals:
    void errorOccured(QString errMsg);
    
public slots:
    void onReadReady();

private:
    void parseBkpt(const QString& _msg);
    void parseStopMsg(const QString& _msg);
    void parseLine(const QString& _msg);

    static QString gdbPath;
    static bool checkResult;
    QVector<bkpt_struct> bkptVec;
};

#endif // GDB_H
