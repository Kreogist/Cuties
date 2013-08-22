#ifndef KCICOMPILERCONFIGURE_H
#define KCICOMPILERCONFIGURE_H

#include <QString>

#include "kciconfigure.h"

class kciCompilerConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciCompilerConfigure* getInstance();

    QString getGccPath() const;
    void setGccPath(const QString &value);
    QString getGppPath() const;
    void setGppPath(const QString &value);
    QString getFpcPath() const;
    void setFpcPath(const QString &value);

private:
    kciCompilerConfigure();
    static kciCompilerConfigure* instance;

    QString gccPath, gppPath, fpcPath;
};

#endif // KCICOMPILERCONFIGURE_H
