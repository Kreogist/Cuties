/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *
 *  highlighterfactory.cpp is part of Kreogist-Cute-IDE.
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

#include "highlighterfactory.h"

highlighterFactory::highlighterFactory(QObject *parent) :
    QObject(parent)
{
}

QSyntaxHighlighter* highlighterFactory::createHighlighterByFileName(
        const QString &fileName,
        QObject *parent)
{
    QFileInfo _fileInfo(fileName);
    QString suffix=_fileInfo.suffix();

    if(suffix.contains(cppHighlighter::suffixFilter()))
    {
        return new cppHighlighter(parent);
    }
    else if(suffix.contains(pascalHighlighter::suffixFilter()))
    {
        return new pascalHighlighter(parent);
    }
    else
    {
        //use cpp-mode as default.
        //return new cppHighlighter(parent);
    }
}
