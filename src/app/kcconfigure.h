/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCCONFIGURE_H
#define KCCONFIGURE_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QVariant>

class KCAbstractConfigure : public QObject
{
    Q_OBJECT

public:
    virtual ~KCAbstractConfigure() = 0;

signals:
    void configureChanged(QString groupName);

public slots:
    virtual void readConfigure() = 0;
    virtual void writeConfigure() = 0;

protected:
    virtual QString getGroupName() const = 0;
};

class KCConfigure : public KCAbstractConfigure
{
    Q_OBJECT

public:
    ~KCConfigure();
    static QString getCfgFileName();
    static void setCfgFileName(const QString &value);

public slots:
    void readConfigure() final;
    void writeConfigure() final;

    QVariant getValue(const QString &key) const;
    void setValue(const QString &key, const QVariant &value);

    void setPathValue(const QString &key, const QString &value);
    QString getPathValue(const QString &key) const;

protected:
    virtual void readConfigureCustomSteps(){}
    virtual void writeConfigureCustomSteps(){}

private:
    void doReadConfigure(const QString &filePath);
    QMap<QString, QVariant> configureMap;
    static QString cfgFileName;
};

#endif // KCCONFIGURE_H
