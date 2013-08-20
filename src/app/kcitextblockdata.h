/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCITEXTBLOCKDATA_H
#define KCITEXTBLOCKDATA_H

#include <QTextBlockUserData>
#include <QList>
#include <QString>
#include <QMutex>
#include <climits>

struct matchedInfo
{
    int pos;
    int matchedLength;
};

class kciTextBlockData : public QTextBlockUserData
{
public:
    kciTextBlockData();
    void beginUsingDatas();
    void endUsingDatas();

    void resetForSearch();
    void setSearchCode(const unsigned long long int& searchCode);
    QList<matchedInfo>::iterator getFirstMatchedTextPosition();
    QList<matchedInfo>::iterator getEndMatchedTextPosition();
    void insertMatchedTextPositions(const int& pos, const int& matchedLen);
    bool isSearched(const unsigned long long int& searchCodeNow);
    bool hasMatched();
    void onBlockChanged();

private:
    unsigned long long int searchCode;
    bool isChanged;
    QMutex mutex;
    QList<matchedInfo> matchedTextPositions;
};

#endif // KCITEXTBLOCKDATA_H
