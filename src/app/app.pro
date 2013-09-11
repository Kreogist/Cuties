#-------------------------------------------------
#
#   Copyright 2013 Kreogist Dev Team
#
#     Kreogist-Cuties is free software: you can redistribute it and/or
#   modify it under the terms of the GNU General Public License as published
#   by the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Kreogist-Cuties is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
#
#-------------------------------------------------

TARGET = Kreogist-Cuties

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
    fpc.cpp \
    kcilistbutton.cpp \
    Controls/SettingItems/kcisettinglistitemboolean.cpp \
    Controls/SettingItems/kcisettinglistitembase.cpp \
    Controls/SettingItems/kcisettinglistitemcombo.cpp \
    compileoutputreceiver.cpp \
    Controls/SettingItems/kcisettinglistitemlinetext.cpp \
    dbgoutputreceiver.cpp \
    connectionhandler.cpp \
    kciplaintextbrowser.cpp \
    kcimessagebox.cpp \
    kcidragproxy.cpp \
    kciclipboard.cpp \
    kcidebugwatchdock.cpp \
    kcitextblockdata.cpp \
    kcihighlighter.cpp \
    kcisidebar.cpp \
    Controls/SettingItems/kcisettinglistitembrowsetext.cpp \
    Controls/SettingItems/kcisettinglistitemlanguageitem.cpp \
    kcigeneralconfigure.cpp \
    kcieditorconfigure.cpp \
    kcicompilerconfigure.cpp \
    kcidebuggerconfigure.cpp \
    kcilanguageconfigure.cpp \
    kcifileassociation.cpp \
    kciconfigure.cpp \
    Controls/SettingItems/kcisettinglistitemnuminput.cpp \
    kcifiletype.cpp \
    kcihistoryconfigure.cpp \
    kcirecentlyfilesmenu.cpp

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
    fpc.h \
    kcilistbutton.h \
    Controls/SettingItems/kcisettinglistitemboolean.h \
    Controls/SettingItems/kcisettinglistitembase.h \
    Controls/SettingItems/kcisettinglistitemcombo.h \
    compileoutputreceiver.h \
    Controls/SettingItems/kcisettinglistitemlinetext.h \
    dbgoutputreceiver.h \
    connectionhandler.h \
    kciplaintextbrowser.h \
    kcimessagebox.h \
    kcidragproxy.h \
    kciclipboard.h \
    kcidebugwatchdock.h \
    kcitextblockdata.h \
    kcihighlighter.h \
    kcisidebar.h \
    Controls/SettingItems/kcisettinglistitembrowsetext.h \
    Controls/SettingItems/kcisettinglistitemlanguageitem.h \
    kciconfigure.h \
    kcigeneralconfigure.h \
    kcieditorconfigure.h \
    kcicompilerconfigure.h \
    kcidebuggerconfigure.h \
    kcilanguageconfigure.h \
    kcifileassociation.h \
    Controls/SettingItems/kcisettinglistitemnuminput.h \
    kcifiletype.h \
    kcihistoryconfigure.h \
    kcirecentlyfilesmenu.h

# Enable C++11
CONFIG += c++11

RESOURCES += \
    rc.qrc

RC_FILE += winico.rc

ICON += Cuties.icns

TRANSLATIONS += zh_CN.ts

OTHER_FILES += \
    zh_CN.ts \
    lang.map \
    default.style \
    COPYING.txt \
    Cuties.icns
    winico.rc
