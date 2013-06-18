#ifndef COMPILERBASE_H
#define COMPILERBASE_H

#include <QProcess>

struct compilerMessage
{
    enum msgType
    {
        error,
        warning,
        others
    };

    msgType type;
    int lineNum;
    QString msg;
};

class compilerBase : public QProcess
{
    Q_OBJECT
public:
    explicit compilerBase(QObject *parent = 0);

    virtual void startCompile(const QString& ) = 0;
    virtual QString version() = 0;
    virtual QString path(){return "";}
    virtual bool checkCompilerPath(const QString& ) = 0;
    virtual QString compilerName(){return "compiler";}

signals:
    void output(compilerMessage msg);

};

#endif // COMPILERBASE_H
