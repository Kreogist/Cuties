#include "compilerbasefactor.h"

compilerBaseFactor::compilerBaseFactor(QObject *parent) :
    QObject(parent)
{
}

compilerBase* compilerBaseFactor::createCompilerBase(const QString &fileName,
                                                     QObject *parent)
{
    QFileInfo _fileInfo(fileName);
    QString suffix=_fileInfo.suffix();

    if(suffix.contains(gcc::suffixFilter()))
    {
        return new gcc(parent);
    }
    else
    {
        return nullptr;
    }
}
