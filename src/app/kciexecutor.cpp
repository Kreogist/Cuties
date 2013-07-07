/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
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

#include "kciexecutor.h"

kciExecutor::kciExecutor(QObject *parent) :
    QObject(parent)
{
    testCaseNum=0;
}

void kciExecutor::setInputFiles(const QStringList &Files)
{
    inputFilesPath=Files;
}

int kciExecutor::addTestCase(const QByteArray &input, const QByteArray &output)
{
    TestCase test;
    test.input=input;
    test.output=output;
    test.testCaseNumber=testCaseNum;
    testData<<test;

    return testCaseNum++;;
}

void kciExecutor::removeInputData(const int &inputDataNum)
{
    for(auto i=testData.begin(),end=testData.end();
        i!=end;
        i++)
    {
        if(i->testCaseNumber == inputDataNum)
        {
            testData.erase(i);
            return ;
        }
    }
}
