#ifndef KCLANGUAGECONFIGURE_H
#define KCLANGUAGECONFIGURE_H

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QApplication>
#include <QStringList>
#include <QDebug>
#include <QTranslator>
#include <QApplication>

#include "kcconfigure.h"

class KCLanguageConfigure : public KCConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static KCLanguageConfigure *getInstance();

    void setLanguage(QString newLanguageName);
    QStringList getLanguageList() const;
    QStringList getLanguageNameList() const;

private:
    QString languageFileDir, currLanguageName;

    KCLanguageConfigure();
    static KCLanguageConfigure *instance;

    QStringList languageFileList, languageName, languageImage;
    void loadLanguageList();

    QTranslator appTrans;
};

#endif // KCLANGUAGECONFIGURE_H
