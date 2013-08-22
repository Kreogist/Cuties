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

struct parenthesesInfo
{
    char character;
    int pos;
};

class kciTextBlockData : public QTextBlockUserData
{
public:
    kciTextBlockData();
    void beginUsingSearchDatas();
    void endUsingSearchDatas();

    void resetForSearch();
    void setSearchCode(const unsigned long long int& searchCode);
    QList<matchedInfo>::iterator getFirstMatchedTextPosition();
    QList<matchedInfo>::iterator getEndMatchedTextPosition();
    void insertMatchedTextPositions(const int& pos, const int& matchedLen);
    bool isSearched(const unsigned long long int& searchCodeNow);
    bool hasMatched();
    void onBlockChanged();

    void insertParenthesesInfo(const int& pos, const char& character);
    void resetParentheseInfos();
    QList<parenthesesInfo>::iterator getFirstParenthesesInfo();
    QList<parenthesesInfo>::iterator getEndParenthesesInfo();

    void setCodeLevel(const int& level);
    int getCodeLevel() const;

private:
    unsigned long long int searchCode;
    bool needSearchAgain;
    QMutex mutex;
    QList<matchedInfo> matchedTextPositions;
    QList<parenthesesInfo> parenthesesInfos;
    int codeLevel;
};

#endif // KCITEXTBLOCKDATA_H
