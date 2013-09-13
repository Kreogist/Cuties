#ifndef KCILANGUAGECONFIGURE_H
#define KCILANGUAGECONFIGURE_H

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QApplication>
#include <QStringList>

#include "kciconfigure.h"

class kciLanguageConfigure : public kciConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static kciLanguageConfigure* getInstance();

private:
    kciLanguageConfigure();
    static kciLanguageConfigure* instance;

    QStringList languageFileList, languageName, languageImage;
    void loadLanguageList();
};

#endif // KCILANGUAGECONFIGURE_H
