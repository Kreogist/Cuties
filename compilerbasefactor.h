#ifndef COMPILERBASEFACTOR_H
#define COMPILERBASEFACTOR_H

#include <QObject>

#include "compilerbase.h"
#include "gcc.h"

class compilerBaseFactor : public QObject
{
    Q_OBJECT
public:
    explicit compilerBaseFactor(QObject *parent = 0);

    static compilerBase* createCompilerBase(const QString& fileName,
                                            QObject *parent);
    
signals:
    
public slots:
    
};

#endif // COMPILERBASEFACTOR_H
