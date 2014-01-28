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

#ifndef KCTEXTBLOCKDATA_H
#define KCTEXTBLOCKDATA_H

#include <QTextBlockUserData>
#include <QList>
#include <QString>
#include <QMutex>

struct quotationInfo
{
    int beginPos;
    int endPos;
};

struct parenthesesInfo
{
    char character;
    int pos;
};

struct markUnit
{
    QRect rect;
    bool marked;
    markUnit()
    {
        marked=false;
    }
};

struct codeLevelUnit
{
    QRect codeLevelRect;
    bool codeLevelUp;
    bool codeLevelDown;
    bool hasFolded;
    bool hasError;
    int codeLevel;
    codeLevelUnit()
    {
        codeLevel=0;
        codeLevelUp=false;
        codeLevelDown=false;
        hasFolded=false;
        hasError=false;
    }
};

class KCTextBlockData : public QTextBlockUserData
{
public:
    struct matchedInfo
    {
        int pos;
        int matchedLength;
    };

    KCTextBlockData();
    void beginUsingSearchDatas();
    void endUsingSearchDatas();

    void resetForSearch();
    void setSearchCode(const unsigned long long int &searchCode);
    matchedInfo getMatchedInfo(int index);
    int matchedCount();

    void insertMatchedTextPositions(const int &pos, const int &matchedLen);
    bool isSearched(const unsigned long long int &searchCodeNow);
    bool hasMatched();
    void onBlockChanged();

    void insertQuotationInfo(const int &beginPos, const int &endPos);
    void resetQuotationInfos();
    QList<quotationInfo>::iterator getFirstQuotationInfo();
    QList<quotationInfo>::iterator getEndQuotationInfo();

    void insertParenthesesInfo(const int &pos, const char &character);
    void resetParentheseInfos();
    QList<parenthesesInfo>::iterator getFirstParenthesesInfo();
    QList<parenthesesInfo>::iterator getEndParenthesesInfo();

    markUnit getMarkInfo() const;
    void setMarkInfo(const markUnit &value);
    int getLineCommentPos() const;
    void setLineCommentPos(int value);
    int getQuotationStatus() const;
    void setQuotationStatus(int value);
    codeLevelUnit getCodeLevelInfo() const;
    void setCodeLevelInfo(const codeLevelUnit &value);
    int getCodeLevel() const;
    void setCodeLevel(int value);
    bool getHasFolded() const;
    void setHasFolded(bool value);
    void setHasError(bool value);

private:
    unsigned long long int searchCode;
    bool needSearchAgain;
    QMutex mutex;
    QList<matchedInfo> matchedTextPositions;
    QList<parenthesesInfo> parenthesesInfos;
    QList<quotationInfo> quotationInfos;
    int lineCommentPos;
    int quotationStatus;
    markUnit markInfo;
    codeLevelUnit codeLevelInfo;
};

#endif // KCTEXTBLOCKDATA_H
