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
    kccodeeditor.cpp \
    kctexteditor.cpp \
    kcpanel.cpp \
    kclinenumpanel.cpp \
    kreogistcutestyle.cpp \
    kctitlebar.cpp \
    kcglobal.cpp \
    textcharformatmap.cpp \
    gcc.cpp \
    kctabmanager.cpp \
    kccompiledock.cpp \
    gdb.cpp \
    kcmainwindow.cpp \
    gdbmivalue.cpp \
    kcmarkpanel.cpp \
    kcstatusbar.cpp \
    kctextsearcher.cpp \
    kcsearchwindow.cpp \
    kcstatuscursorinfo.cpp \
    kccontrolcenter.cpp \
    kcexecutor.cpp \
    kcjudgedock.cpp \
    kclanguagemode.cpp \
    kcdebugdock.cpp \
    fpc.cpp \
    kclistbutton.cpp \
    Controls/SettingItems/kcsettinglistitemboolean.cpp \
    Controls/SettingItems/kcsettinglistitembase.cpp \
    Controls/SettingItems/kcsettinglistitemcombo.cpp \
    Controls/SettingItems/kcsettinglistitemlinetext.cpp \
    dbgoutputreceiver.cpp \
    kcplaintextbrowser.cpp \
    kcdragproxy.cpp \
    kcdebugwatchdock.cpp \
    kctextblockdata.cpp \
    kchighlighter.cpp \
    kcsidebar.cpp \
    Controls/SettingItems/kcsettinglistitembrowsetext.cpp \
    Controls/SettingItems/kcsettinglistitemlanguageitem.cpp \
    kcgeneralconfigure.cpp \
    kceditorconfigure.cpp \
    kccompilerconfigure.cpp \
    kcdebuggerconfigure.cpp \
    kclanguageconfigure.cpp \
    kcfileassociation.cpp \
    kcconfigure.cpp \
    Controls/SettingItems/kcsettinglistitemnuminput.cpp \
    kcfiletype.cpp \
    kchistoryconfigure.cpp \
    kcmessagebox.cpp \
    kcsearchlinetext.cpp \
    kcsearchwidget.cpp \
    kcstatusrewriteinfo.cpp \
    Controls/SettingItems/kcsettinglistitembutton.cpp \
    kcsplashscreen.cpp \
    kcclipboard.cpp \
    kccompilerbase.cpp \
    kccompileoutputreceiver.cpp \
    kcconnectionhandler.cpp \
    kccpphighlighter.cpp \
    kcpascalhighlighter.cpp \
    kcreplacewindow.cpp \
    kccolorconfigure.cpp

HEADERS += \
    mainwindow.h \
    kccodeeditor.h \
    kctexteditor.h \
    kcpanel.h \
    kclinenumpanel.h \
    kreogistcutestyle.h \
    kctitlebar.h \
    kcglobal.h \
    textcharformatmap.h \
    highlighterGlobal.h \
    gcc.h \
    kctabmanager.h \
    kccompiledock.h \
    gdb.h \
    kcmainwindow.h \
    gdbmivalue.h \
    kcmarkpanel.h \
    kcstatusbar.h \
    kctextsearcher.h \
    kcsearchwindow.h \
    kcstatuscursorinfo.h \
    kccontrolcenter.h \
    kcexecutor.h \
    kcjudgedock.h \
    kclanguagemode.h \
    kcsearchlinetext.h \
    kcdebugdock.h \
    fpc.h \
    kclistbutton.h \
    Controls/SettingItems/kcsettinglistitemboolean.h \
    Controls/SettingItems/kcsettinglistitembase.h \
    Controls/SettingItems/kcsettinglistitemcombo.h \
    Controls/SettingItems/kcsettinglistitemlinetext.h \
    dbgoutputreceiver.h \
    kcplaintextbrowser.h \
    kcdragproxy.h \
    kcdebugwatchdock.h \
    kctextblockdata.h \
    kchighlighter.h \
    kcsidebar.h \
    Controls/SettingItems/kcsettinglistitembrowsetext.h \
    Controls/SettingItems/kcsettinglistitemlanguageitem.h \
    kcconfigure.h \
    kcgeneralconfigure.h \
    kceditorconfigure.h \
    kccompilerconfigure.h \
    kcdebuggerconfigure.h \
    kclanguageconfigure.h \
    kcfileassociation.h \
    Controls/SettingItems/kcsettinglistitemnuminput.h \
    kcfiletype.h \
    kchistoryconfigure.h \
    kcmessagebox.h \
    kcsearchwidget.h \
    kcstatusrewriteinfo.h \
    Controls/SettingItems/kcsettinglistitembutton.h \
    kcsplashscreen.h \
    kcclipboard.h \
    kccompileoutputreceiver.h \
    kccompilerbase.h \
    kcconnectionhandler.h \
    kccpphighlighter.h \
    kcpascalhighlighter.h \
    kcreplacewindow.h \
    kccolorconfigure.h

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
    Cuties.icns \
    winico.rc
