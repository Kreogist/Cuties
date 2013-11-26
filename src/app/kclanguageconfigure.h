#ifndef KCLANGUAGECONFIGURE_H
#define KCLANGUAGECONFIGURE_H

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QApplication>
#include <QPixmap>
#include <QStringList>
#include <QDebug>
#include <QTranslator>
#include <QApplication>
#include <QMetaEnum>

#include "kcconfigure.h"

class KCLanguageConfigure : public KCConfigure
{
    Q_OBJECT
public:
    void readConfigure();
    void writeConfigure();
    static KCLanguageConfigure *getInstance();

    QStringList getLanguageList() const;
    QStringList getLanguageCaption() const;
    QStringList getLanguageNameList() const;
    QList<QPixmap> getLanguageFileIcon() const;
    int getCurrentLanguageIndex() const;
    QString getCurrentLanguageName() const;
    QPixmap getCurrentLanguageIcon() const;
    QString getLanguageString(QLocale::Language language);
    QString getLocaleFileDir() const;

signals:
    void newLanguageSet();

public slots:
    void setLanguage(const QString &newLanguageName);
    void setLanguageIndex(int newLangaugeIndex);

private:
    void applyLangaugeSet(int languageIndex);

    //Language file folder & language translation file
    QString localeFileDir, localeTranslation;

    //Cache list
    QStringList languageFileList, languageName, languageCaption;
    QList<QPixmap> languageFileIcon;

    QString defaultLanguageName;
    QString currentLanguageName;
    int currentLanguageIndex;

    KCLanguageConfigure();
    static KCLanguageConfigure *instance;

    void loadLanguageList();

    QTranslator appTrans;
};

#endif // KCLANGUAGECONFIGURE_H
