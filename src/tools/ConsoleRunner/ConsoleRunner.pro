#-------------------------------------------------
#
#   Copyright 2013 Kreogist Dev Team
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

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = KciConsoleRunner

SOURCES += main.cpp

win32 {
    DEFINES+= _OS_WIN32_
}

linux {
    DEFINES+= _OS_LINUX_
}

macx {
    DEFINES+= _OS_MAC_X_
}
