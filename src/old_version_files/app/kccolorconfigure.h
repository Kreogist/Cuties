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


#ifndef KCCOLORCONFIGURE_H
#define KCCOLORCONFIGURE_H

#include <QMap>
#include <QPalette>
#include <QDebug>

#include "kcconfigure.h"

class KCColorConfigure : public KCAbstractConfigure
{
    Q_OBJECT
public:
    ~KCColorConfigure();
    static KCColorConfigure *getInstance();
    void readConfigure();
    void writeConfigure();

    void getPalette(QPalette &pal, const QString &objectName) const;
    void registerColorInfo(QPalette::ColorRole role,
                           const QColor &color,
                           const QString &objectName);

    static QString getColorConfigFilePath();
    static void setColorConfigFilePath(const QString &filePath);

protected:
    QString getGroupName() const;

private:
    struct Color
    {
        int r,g,b;
        Color()
        {
            r=-1;
            g=-1;
            b=-1;
        }
        Color(int red,int green,int blue)
        {
            r=red;
            g=green;
            b=blue;
        }
    };
    struct ColorInfo
    {
        Color color;
        QPalette::ColorRole colorRole;
        ColorInfo operator = (const Color &a)
        {
            color.r=a.r;
            color.g=a.g;
            color.b=a.b;
            return *this;
        }
    };

    KCColorConfigure();
    Color parseColor(const QString &content);
    Color parseObjectColor(const QString &content);
    bool isValidColor(const Color &color);
    QPalette::ColorRole getColorRoleFromString(const QString &string);
    QString getColorRoleString(QPalette::ColorRole role);

    static KCColorConfigure *instance;
    static QString colorConfigFilePath;
    QMap<QString,QVector<ColorInfo> > colorInfoMap;
    QMap<QString,Color> colorSheet;
};

#endif // KCCOLORCONFIGURE_H
