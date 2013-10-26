#ifndef KCCOMPILERCONFIGURE_H
#define KCCOMPILERCONFIGURE_H

#include <QString>
#include <QApplication>
#include <QDebug>

#include "kcconfigure.h"

class KCCompilerConfigure : public KCConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static KCCompilerConfigure *getInstance();

    QString getGccPath() const;
    void setGccPath(const QString &value);
    QString getGppPath() const;
    void setGppPath(const QString &value);
    QString getFpcPath() const;
    void setFpcPath(const QString &value);

private:
    KCCompilerConfigure();
    static KCCompilerConfigure *instance;

    QString gccPath, gppPath, fpcPath;
};

#endif // KCCOMPILERCONFIGURE_H
