#-------------------------------------------------
#
#   Copyright 2013 Kreogist Dev Team
#
#       Wang Luming <wlm199558@126.com>
#       Miyanaga Saki <tomguts@126.com>
#       Zhang Jiayi <bf109g2@126.com>
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
    cpphighlighter.cpp \
    kreogistcutestyle.cpp \
    kcititlebar.cpp \
    kciglobal.cpp \
    pascalhighlighter.cpp \
    textcharformatmap.cpp \
    compilerbase.cpp \
    gcc.cpp \
    kcitabmanager.cpp \
    kcicompiledock.cpp \
    gdb.cpp \
    kcimainwindow.cpp \
    gdbmivalue.cpp \
    kcimarkpanel.cpp \
    kcistatusbar.cpp \
    kcitextsearcher.cpp \
    kcisearchwindow.cpp \
    kcistatuscursorinfo.cpp \
    kcicontrolcenter.cpp \
    kciexecutor.cpp \
    kcijudgedock.cpp \
    kcilanguagemode.cpp \
    kcisearchlinetext.cpp \
    kcidebugdock.cpp \
    kcitextsearchworker.cpp \
    fpc.cpp \
    kcilistbutton.cpp \
    Controls/SettingItems/kcisettinglistitemboolean.cpp \
    Controls/SettingItems/kcisettinglistitembase.cpp \
    Controls/SettingItems/kcisettinglistitemcombo.cpp \
    compileoutputreceiver.cpp \
    Controls/SettingItems/kcisettinglistitemlinetext.cpp \
    dbgoutputreceiver.cpp \
    connectionhandler.cpp \
    Controls/SettingItems/kcisettinglistitemfoldertext.cpp \
    kciplaintextbrowser.cpp \
    kcimessagebox.cpp \
    kcidragproxy.cpp

HEADERS += \
    mainwindow.h \
    kcicodeeditor.h \
    kcitexteditor.h \
    kcipanel.h \
    kcilinenumpanel.h \
    cpphighlighter.h \
    kreogistcutestyle.h \
    kcititlebar.h \
    kciglobal.h \
    pascalhighlighter.h \
    textcharformatmap.h \
    highlighterGlobal.h \
    compilerbase.h \
    gcc.h \
    kcitabmanager.h \
    kcicompiledock.h \
    gdb.h \
    kcimainwindow.h \
    gdbmivalue.h \
    kcimarkpanel.h \
    kcistatusbar.h \
    kcitextsearcher.h \
    kcisearchwindow.h \
    kcistatuscursorinfo.h \
    kcicontrolcenter.h \
    kciexecutor.h \
    kcijudgedock.h \
    kcilanguagemode.h \
    kcisearchlinetext.h \
    kcidebugdock.h \
    kcitextsearchworker.h \
    fpc.h \
    kcilistbutton.h \
    Controls/SettingItems/kcisettinglistitemboolean.h \
    Controls/SettingItems/kcisettinglistitembase.h \
    Controls/SettingItems/kcisettinglistitemcombo.h \
    compileoutputreceiver.h \
    Controls/SettingItems/kcisettinglistitemlinetext.h \
    dbgoutputreceiver.h \
    connectionhandler.h \
    Controls/SettingItems/kcisettinglistitemfoldertext.h \
    kciplaintextbrowser.h \
    kcimessagebox.h \
    kcidragproxy.h

# Enable C++11
CONFIG += c++11

RESOURCES += \
    rc.qrc

RC_FILE += winico.rc

TRANSLATIONS += zh_CN.ts

OTHER_FILES += \
    zh_CN.ts \
    lang.map \
    default.style \
    COPYING.txt
