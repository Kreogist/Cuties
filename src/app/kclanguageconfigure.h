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
    Q_OBJECT
public:
    void readConfigure();
    void writeConfigure();
    static KCLanguageConfigure *getInstance();

    int setLanguage(QString newLanguageName);
    void setLanguageIndex(int newLangaugeIndex);
    QStringList getLanguageList() const;
    QStringList getLanguageNameList() const;
    int getCurrLanguageIndex() const;

signals:
    void newLanguageSet();

private:
    void applyLangaugeSet(int languageIndex);

    QString languageFileDir, currLanguageName;
    int currLanguageIndex;

    KCLanguageConfigure();
    static KCLanguageConfigure *instance;

    QStringList languageFileList, languageName, languageImage;
    void loadLanguageList();

    QTranslator appTrans;
};

#endif // KCLANGUAGECONFIGURE_H
