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

#include "kctextblockdata.h"

KCTextBlockData::KCTextBlockData()
{
    searchCode=0;
    codeLevel=0;
    resetForSearch();
}

void KCTextBlockData::resetForSearch()
{
    needSearchAgain=false;
    matchedTextPositions.clear();
    matchedInfo gmin,gmax;
    gmin.pos=INT_MIN;
    gmax.pos=INT_MAX;
    matchedTextPositions<<gmin<<gmax; //two guard elements
}

QList<matchedInfo>::iterator KCTextBlockData::getFirstMatchedTextPosition()
{
    return matchedTextPositions.begin()+1;  //skip the guard elements
}

QList<matchedInfo>::iterator KCTextBlockData::getEndMatchedTextPosition()
{
    return matchedTextPositions.end()-1;  //skip the guard elements
}

void KCTextBlockData::setSearchCode(const unsigned long long &searchCode)
{
    this->searchCode=searchCode;
}

void KCTextBlockData::insertMatchedTextPositions(const int &pos,
        const int &matchedLen)
{
    auto i=matchedTextPositions.begin(),
         l=matchedTextPositions.end();
    while(i<l)
    {
        if(i->pos<=pos && pos <= (i+1)->pos)
        {
            break;
        }

        i++;
    }

    matchedInfo newElement;
    newElement.pos=pos;
    newElement.matchedLength=matchedLen;
    matchedTextPositions.insert(i+1,newElement);
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
    return matchedTextPositions.size()>2;
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

void KCTextBlockData::setCodeLevel(const int &level)
{
    codeLevel=level;
}

int KCTextBlockData::getCodeLevel() const
{
    return codeLevel;
}

markUnit KCTextBlockData::getMarkInfo() const
{
    return markInfo;
}

void KCTextBlockData::setMarkInfo(const markUnit &value)
{
    markInfo = value;
}
