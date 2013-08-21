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

#include "kcitextblockdata.h"

kciTextBlockData::kciTextBlockData()
{
    searchCode=0;
    resetForSearch();
}

void kciTextBlockData::resetForSearch()
{
    needSearchAgain=false;
    matchedTextPositions.clear();
    matchedInfo gmin,gmax;
    gmin.pos=INT_MIN;
    gmax.pos=INT_MAX;
    matchedTextPositions<<gmin<<gmax; //two guard elements
}

QList<matchedInfo>::iterator kciTextBlockData::getFirstMatchedTextPosition()
{
    return matchedTextPositions.begin()+1;  //skip the guard elements
}

QList<matchedInfo>::iterator kciTextBlockData::getEndMatchedTextPosition()
{
    return matchedTextPositions.end()-1;  //skip the guard elements
}

void kciTextBlockData::setSearchCode(const unsigned long long &searchCode)
{
    this->searchCode=searchCode;
}

void kciTextBlockData::insertMatchedTextPositions(const int& pos,
                                                  const int &matchedLen)
{
    auto i=matchedTextPositions.begin(),
         l=matchedTextPositions.end();
    while(i<l)
    {
        if(i->pos<=pos && pos <= (i+1)->pos)
            break;

        i++;
    }

    matchedInfo newElement;
    newElement.pos=pos;
    newElement.matchedLength=matchedLen;
    matchedTextPositions.insert(i+1,newElement);
}

bool kciTextBlockData::isSearched(const unsigned long long &searchCodeNow)
{
    return (searchCodeNow==searchCode) && (!needSearchAgain);
}

void kciTextBlockData::onBlockChanged()
{
    needSearchAgain=true;
}

void kciTextBlockData::beginUsingSearchDatas()
{
    mutex.lock();
}

void kciTextBlockData::endUsingSearchDatas()
{
    mutex.unlock();
}

bool kciTextBlockData::hasMatched()
{
    return matchedTextPositions.size()>2;
}

void kciTextBlockData::resetParentheseInfos()
{
    parenthesesInfos.clear();
}

void kciTextBlockData::insertParenthesesInfo(const int &pos,
                                             const char &character)
{
    auto i=parenthesesInfos.begin(),
         l=parenthesesInfos.end();
    while(i<l)
    {
        if(i->pos > pos)
            break;
        i++;
    }

    parenthesesInfo info;
    info.pos=pos;
    info.character=character;
    parenthesesInfos.insert(i,info);
}

QList<parenthesesInfo>::iterator kciTextBlockData::getFirstParenthesesInfo()
{
    return parenthesesInfos.begin();
}

QList<parenthesesInfo>::iterator kciTextBlockData::getEndParenthesesInfo()
{
    return parenthesesInfos.end();
}
