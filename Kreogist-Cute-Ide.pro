#-------------------------------------------------
#   Copyright 2013 Wang Luming <wlm199558@126.com>
#   Copyright 2013 Ye Haolei <18710163604@126.com>
#
#     Kreogist-Cute-IDE is free software: you can redistribute it and/or
#   modify it under the terms of the GNU General Public License as published
#   by the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Kreogist-Cute-IDE is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
#
#-------------------------------------------------

TARGET = Kreogist-Cute-Ide

TEMPLATE = app

QT  += core\
    gui\
    widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    kcicodeeditor.cpp \
    kcitexteditor.cpp \
    kcipanel.cpp \
    kcilinenumpanel.cpp \
    highlighterbase.cpp \
    cpphighlighter.cpp \
    kreogistcutestyle.cpp \
    highlightrulesprovider.cpp \
    kcititlebar.cpp \
    kciglobal.cpp

HEADERS += \
    mainwindow.h \
    kcicodeeditor.h \
    kcitexteditor.h \
    kcipanel.h \
    kcilinenumpanel.h \
    highlighterbase.h \
    cpphighlighter.h \
    kreogistcutestyle.h \
    highlightrulesprovider.h \
    kcititlebar.h \
    kciglobal.h

# Enable C++11
CONFIG += c++11

RESOURCES += \
    rc.qrc

OTHER_FILES += \
    image/MainMenuButton.png \
    image/FileMenuIcon.png \
    image/Minimized.png \
    image/Maxmized.png \
    image/Close.png

TRANSLATIONS += zh_CN.ts
