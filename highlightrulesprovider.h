/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *  highlightrulesprovider.h is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HIGHLIGHTRULESPROVIDER_H
#define HIGHLIGHTRULESPROVIDER_H

#include <QObject>
#include <QList>

//This is a Single Ton

class highlightRulesProvider : public QObject
{
    Q_OBJECT

public:
    highlightRulesProvider* getInstance();
    
signals:
    void highlightRuleChanged();
    
public slots:

private:
    highlightRulesProvider();

    static highlightRulesProvider *instance;

    void generateCppRules();
};

#endif // HIGHLIGHTRULESPROVIDER_H
