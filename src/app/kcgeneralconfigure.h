#ifndef KCGENERALCONFIGURE_H
#define KCGENERALCONFIGURE_H

#include <QString>
#include <QList>

#include "kcconfigure.h"

struct searchEngine
{
    QString name;
    QString engineURL;
};

class KCGeneralConfigure : public KCConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static KCGeneralConfigure *getInstance();

    int getDefaultLanguageMode() const;
    QString getDefaultLanguageModeString();
    void setDefaultLanguageMode(const int &value);

    bool getRememberUnclosedFile() const;
    void setRememberUnclosedFile(bool value);

    bool getUseDefaultLanguageWhenOpen() const;
    void setUseDefaultLanguageWhenOpen(bool value);

    bool getUseDefaultLanguageWhenSave() const;
    void setUseDefaultLanguageWhenSave(bool value);

    QString getStrFileFilter() const;
    void setStrFileFilter(const QString &value);

    QString getAsfFilter() const;
    void setAsfFilter(const QString &value);

    QString getPtfFilter() const;
    void setPtfFilter(const QString &value);

    QString getHfFilter() const;
    void setHfFilter(const QString &value);

    QString getCfFilter() const;
    void setCfFilter(const QString &value);

    QString getCppfFilter() const;
    void setCppfFilter(const QString &value);

    QString getPasfFilter() const;
    void setPasfFilter(const QString &value);

    QString getAfFilter() const;
    void setAfFilter(const QString &value);

    int getSearchEngineIndex() const;
    void setSearchEngineIndex(int value);

    QList<searchEngine> getSearchEngineList() const;
    void setSearchEngineList(const QList<searchEngine> &value);

private:
    KCGeneralConfigure();
    int defaultLanguageMode;
    bool rememberUnclosedFile;
    bool useDefaultLanguageWhenOpen;
    bool useDefaultLanguageWhenSave;
    static KCGeneralConfigure *instance;
    int searchEngineIndex;
    QList<searchEngine> searchEngineList;

    QString strFileFilter;
    QString asfFilter, ptfFilter, hfFilter, cfFilter, cppfFilter, pasfFilter, afFilter;
};
#endif // KCGENERALCONFIGURE_H
