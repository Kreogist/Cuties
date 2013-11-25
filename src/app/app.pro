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

TARGET = Cuties

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
    kcmainwindow.cpp \
    gdbmivalue.cpp \
    kcmarkpanel.cpp \
    kcstatusbar.cpp \
    kctextsearcher.cpp \
    kcsearchwindow.cpp \
    kcstatuscursorinfo.cpp \
    kcexecutor.cpp \
    kcjudgedock.cpp \
    kclanguagemode.cpp \
    fpc.cpp \
    kclistbutton.cpp \
    dbgoutputreceiver.cpp \
    kcplaintextbrowser.cpp \
    kcdragproxy.cpp \
    kctextblockdata.cpp \
    kchighlighter.cpp \
    kcsidebar.cpp \
    kcgeneralconfigure.cpp \
    kceditorconfigure.cpp \
    kccompilerconfigure.cpp \
    kcdebuggerconfigure.cpp \
    kclanguageconfigure.cpp \
    kcfileassociation.cpp \
    kcconfigure.cpp \
    kchistoryconfigure.cpp \
    kcmessagebox.cpp \
    kcsearchlinetext.cpp \
    kcsearchwidget.cpp \
    kcstatusrewriteinfo.cpp \
    kcsplashscreen.cpp \
    kcclipboard.cpp \
    kccompilerbase.cpp \
    kccompileoutputreceiver.cpp \
    kcconnectionhandler.cpp \
    kccpphighlighter.cpp \
    kcpascalhighlighter.cpp \
    kcreplacewindow.cpp \
    kccolorconfigure.cpp \
    kcdebugcommandio.cpp \
    kcdebugcontrolpanel.cpp \
    kcfloattoolbar.cpp \
    kcfontconfigure.cpp \
    kccodecompileprogress.cpp \
    gdbcontroller.cpp \
    kcpreference.cpp \
    kcpreferencesuperlist.cpp \
    kcpreferencepager.cpp \
    kcpreferenceembedded.cpp \
    Controls/Preference/kcpreferenceitembase.cpp \
    Controls/Preference/kcpreferenceitemcombo.cpp \
    Controls/Preference/kcpreferenceitemboolean.cpp \
    Controls/Preference/kcpreferenceitemint.cpp \
    Controls/Preference/kcpreferenceitembooleangroup.cpp \
    Controls/Preference/kcpreferenceitempath.cpp \
    kcpreferencelangaugelist.cpp \
    Controls/GraphicButtons/kcgraphicbuttonbase.cpp \
    Controls/GraphicButtons/kcgraphicbuttonok.cpp

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
    kcmainwindow.h \
    gdbmivalue.h \
    kcmarkpanel.h \
    kcstatusbar.h \
    kctextsearcher.h \
    kcsearchwindow.h \
    kcstatuscursorinfo.h \
    kcexecutor.h \
    kcjudgedock.h \
    kclanguagemode.h \
    kcsearchlinetext.h \
    fpc.h \
    kclistbutton.h \
    dbgoutputreceiver.h \
    kcplaintextbrowser.h \
    kcdragproxy.h \
    kctextblockdata.h \
    kchighlighter.h \
    kcsidebar.h \
    kcconfigure.h \
    kcgeneralconfigure.h \
    kceditorconfigure.h \
    kccompilerconfigure.h \
    kcdebuggerconfigure.h \
    kclanguageconfigure.h \
    kcfileassociation.h \
    kchistoryconfigure.h \
    kcmessagebox.h \
    kcsearchwidget.h \
    kcstatusrewriteinfo.h \
    kcsplashscreen.h \
    kcclipboard.h \
    kccompileoutputreceiver.h \
    kccompilerbase.h \
    kcconnectionhandler.h \
    kccpphighlighter.h \
    kcpascalhighlighter.h \
    kcreplacewindow.h \
    kccolorconfigure.h \
    kcdebugcommandio.h \
    kcdebugcontrolpanel.h \
    kcfloattoolbar.h \
    kcfontconfigure.h \
    kccodecompileprogress.h \
    gdbcontroller.h \
    kcpreference.h \
    kcpreferencesuperlist.h \
    kcpreferencepager.h \
    kcpreferenceembedded.h \
    Controls/Preference/kcpreferenceitembase.h \
    Controls/Preference/kcpreferenceitemcombo.h \
    Controls/Preference/kcpreferenceitemboolean.h \
    Controls/Preference/kcpreferenceitemint.h \
    Controls/Preference/kcpreferenceitembooleangroup.h \
    Controls/Preference/kcpreferenceitempath.h \
    kcpreferencelangaugelist.h \
    Controls/GraphicButtons/kcgraphicbuttonbase.h \
    Controls/GraphicButtons/kcgraphicbuttonok.h

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
    winico.rc \
    translations/zh_CN.ts \
    translations/en_US.ts
