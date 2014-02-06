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
#include <QSettings>
#include <QString>

class KCConfigure : public QObject
{
    Q_OBJECT

public:
    KCConfigure();
    virtual void readConfigure();
    virtual void writeConfigure();

    virtual QVariant getValue(const QString &key) const;
    virtual void setValue(const QString &key, const QVariant &value);

    static QString getCfgFileName();
    static void setCfgFileName(const QString &value);

    virtual void setPathValue(const QString &key, const QString &value);
    virtual QString getPathValue(const QString &key) const;

protected:
    virtual QString getGroupName() const {return "";}
    QMap<QString, QVariant> configureMap;

private:
    void readConfigure(const QString& filePath);
    static QString cfgFileName;

};

#endif // KCCONFIGURE_H
