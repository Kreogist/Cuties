#ifndef KCILANGUAGECONFIGURE_H
#define KCILANGUAGECONFIGURE_H

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QApplication>
#include <QStringList>
#include <QDebug>
#include <QTranslator>
#include <QApplication>

#include "kciconfigure.h"

class kciLanguageConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciLanguageConfigure *getInstance();

    void setLanguage(QString newLanguageName);
    QStringList getLanguageList() const;
    QStringList getLanguageNameList() const;

private:
    QString languageFileDir, currLanguageName;

    kciLanguageConfigure();
    static kciLanguageConfigure *instance;

    QStringList languageFileList, languageName, languageImage;
    void loadLanguageList();

    QTranslator appTrans;
};

#endif // KCILANGUAGECONFIGURE_H
