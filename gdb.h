#ifndef GDB_H
#define GDB_H


#include <QProcess>
#include <QFileInfo>

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
    void setBreakPoint(const int &lineNum, const int &count);
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
    
signals:
    
public slots:

private:
    static QString gdbPath;
    static bool checkResult;
};

#endif // GDB_H
