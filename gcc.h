#ifndef GCC_H
#define GCC_H

#include <QFileInfo>
#include <QRegularExpression>
#include <QDebug>

#include "compilerbase.h"

class gcc : public compilerBase
{
    Q_OBJECT
public:
    explicit gcc(QObject *parent = 0);
    void startCompile(const QString &filePath);
    QString version();
    QString path(){return gccPath;}
    bool checkCompilerPath(const QString& ){return true;}
    QString compilerName(){return "g++";}

    static QRegularExpression suffixFilter();

public slots:
    void onOutputReady();

private:
    static QString gccPath;
};

#endif // GCC_H
