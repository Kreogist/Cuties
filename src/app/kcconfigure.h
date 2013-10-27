#ifndef KCCONFIGURE_H
#define KCCONFIGURE_H

#include <QObject>
#include <QSettings>
#include <QString>

class KCConfigure : public QObject
{
    Q_OBJECT

public:
    virtual void readConfigure() = 0;
    virtual void writeConfigure() = 0;

    static QString getCfgFileName();
    static void setCfgFileName(const QString &value);

private:
    static QString cfgFileName;

};

#endif // KCCONFIGURE_H
