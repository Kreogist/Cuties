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

#include <climits>
#include <QDebug>

#include "kctextblockdata.h"

KCTextBlockData::KCTextBlockData()
{
    searchCode=0;
    resetForSearch();
}

void KCTextBlockData::resetForSearch()
{
    needSearchAgain=false;
    matchedTextPositions.clear();
}

void KCTextBlockData::setSearchCode(const unsigned long long &searchCode)
{
    this->searchCode=searchCode;
}

KCTextBlockData::matchedInfo KCTextBlockData::getMatchedInfo(int index)
{
    return matchedTextPositions.at(index);
}

int KCTextBlockData::matchedCount()
{
    return matchedTextPositions.count();
}

void KCTextBlockData::insertMatchedTextPositions(const int &pos,
                                                 const int &matchedLen)
{
    matchedInfo newElement;
    newElement.pos=pos;
    newElement.matchedLength=matchedLen;
    switch(matchedTextPositions.count())
    {
    case 0:
        matchedTextPositions.append(newElement);
        break;
    case 1:
        matchedTextPositions.insert(pos>matchedTextPositions.at(0).pos?1:0,
                                    newElement);
        break;
    default:
        int finalPosition=matchedTextPositions.count()-1;
        bool insertFlag=false;
        for(int i=0;i<finalPosition;i++)
        {
            if(matchedTextPositions.at(i).pos<=pos &&
               matchedTextPositions.at(i+1).pos>=pos)
            {
                insertFlag=true;
                matchedTextPositions.insert(i+1,newElement);
                break;
            }
        }
        if(!insertFlag)
        {
            matchedTextPositions.append(newElement);
        }
        break;
    }
}

void KCTextBlockData::insertQuotationInfo(const int &beginPos, const int &endPos)
{
    quotationInfo newElement;
    newElement.beginPos=beginPos;
    newElement.endPos=endPos;
    quotationInfos.append(newElement);
}

bool KCTextBlockData::isSearched(const unsigned long long &searchCodeNow)
{
    return (searchCodeNow==searchCode) && (!needSearchAgain);
}

void KCTextBlockData::onBlockChanged()
{
    needSearchAgain=true;
}

void KCTextBlockData::beginUsingSearchDatas()
{
    mutex.lock();
}

void KCTextBlockData::endUsingSearchDatas()
{
    mutex.unlock();
}

bool KCTextBlockData::hasMatched()
{
    return !matchedTextPositions.isEmpty();
}

void KCTextBlockData::resetParentheseInfos()
{
    parenthesesInfos.clear();
}

void KCTextBlockData::resetQuotationInfos()
{
    quotationInfos.clear();
}

QList<quotationInfo>::iterator KCTextBlockData::getFirstQuotationInfo()
{
    return quotationInfos.begin();
}

QList<quotationInfo>::iterator KCTextBlockData::getEndQuotationInfo()
{
    return quotationInfos.end();
}

void KCTextBlockData::insertParenthesesInfo(const int &pos,
        const char &character)
{
    auto i=parenthesesInfos.begin(),
         l=parenthesesInfos.end();
    while(i<l)
    {
        if(i->pos > pos)
        {
            break;
        }
        i++;
    }

    parenthesesInfo info;
    info.pos=pos;
    info.character=character;
    parenthesesInfos.insert(i,info);
}

QList<parenthesesInfo>::iterator KCTextBlockData::getFirstParenthesesInfo()
{
    return parenthesesInfos.begin();
}

QList<parenthesesInfo>::iterator KCTextBlockData::getEndParenthesesInfo()
{
    return parenthesesInfos.end();
}

markUnit KCTextBlockData::getMarkInfo() const
{
    return markInfo;
}

void KCTextBlockData::setMarkInfo(const markUnit &value)
{
    markInfo = value;
}

int KCTextBlockData::getLineCommentPos() const
{
    return lineCommentPos;
}

void KCTextBlockData::setLineCommentPos(int value)
{
    lineCommentPos = value;
}

int KCTextBlockData::getQuotationStatus() const
{
    return quotationStatus;
}

void KCTextBlockData::setQuotationStatus(int value)
{
    quotationStatus = value;
}

codeLevelUnit KCTextBlockData::getCodeLevelInfo() const
{
    return codeLevelInfo;
}

void KCTextBlockData::setCodeLevelInfo(const codeLevelUnit &value)
{
    codeLevelInfo = value;
}

int KCTextBlockData::getCodeLevel() const
{
    return codeLevelInfo.codeLevel;
}

void KCTextBlockData::setCodeLevel(int value)
{
    codeLevelInfo.codeLevel = value;
}

bool KCTextBlockData::getHasFolded() const
{
    return codeLevelInfo.hasFolded;
}

void KCTextBlockData::setHasFolded(bool value)
{
    codeLevelInfo.hasFolded = value;
}

void KCTextBlockData::setHasError(bool value)
{
    codeLevelInfo.hasError = value;
}
