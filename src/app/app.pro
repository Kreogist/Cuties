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
    widgets\
    network

SOURCES += \
    main.cpp \
    Controls/GraphicButtons/kcgraphicbuttonbase.cpp \
    Controls/GraphicButtons/kcgraphicbuttonok.cpp \
    Controls/Preference/kcpreferenceitembase.cpp \
    Controls/Preference/kcpreferenceitemboolean.cpp \
    Controls/Preference/kcpreferenceitembooleangroup.cpp \
    Controls/Preference/kcpreferenceitemcombo.cpp \
    Controls/Preference/kcpreferenceitemint.cpp \
    Controls/Preference/kcpreferenceitempath.cpp \
    dbgoutputreceiver.cpp \
    fpc.cpp \
    gcc.cpp \
    gdbcontroller.cpp \
    gdbmivalue.cpp \
    kcclipboard.cpp \
    kccodecompileprogress.cpp \
    kccodeeditor.cpp \
    kccolorconfigure.cpp \
    kccompiledock.cpp \
    kccompileoutputreceiver.cpp \
    kccompilerbase.cpp \
    kccompilerconfigure.cpp \
    kcconfigure.cpp \
    kcconnectionhandler.cpp \
    kccpphighlighter.cpp \
    kcdebugcommandio.cpp \
    kcdebugcontrolpanel.cpp \
    kcdebuggerconfigure.cpp \
    kcdebugwatch.cpp \
    kcdragproxy.cpp \
    kceditorconfigure.cpp \
    kcexecutor.cpp \
    kcfileassociation.cpp \
    kcfloattoolbar.cpp \
    kcfontconfigure.cpp \
    kcgeneralconfigure.cpp \
    kcglobal.cpp \
    kchighlighter.cpp \
    kchistoryconfigure.cpp \
    kcjudgedock.cpp \
    kclanguageconfigure.cpp \
    kclanguagemode.cpp \
    kclinenumpanel.cpp \
    kcmainwindow.cpp \
    kcmarkpanel.cpp \
    kcmessagebox.cpp \
    kcpanel.cpp \
    kcpascalhighlighter.cpp \
    kcplaintextbrowser.cpp \
    kcpreference.cpp \
    kcpreferenceembedded.cpp \
    kcpreferencelangaugelist.cpp \
    kcpreferencepager.cpp \
    kcpreferencesuperlist.cpp \
    kcreplacewindow.cpp \
    kcsearchlinetext.cpp \
    kcsearchwidget.cpp \
    kcsearchwindow.cpp \
    kcsidebar.cpp \
    kcsplashscreen.cpp \
    kcstatusbar.cpp \
    kcstatuscursorinfo.cpp \
    kcstatusrewriteinfo.cpp \
    kctabmanager.cpp \
    kctextblockdata.cpp \
    kctexteditor.cpp \
    kctextsearcher.cpp \
    kctitlebar.cpp \
    kcwelcomewindow.cpp \
    kreogistcutestyle.cpp \
    mainwindow.cpp \
    textcharformatmap.cpp \ 
    kcstatusrecorder.cpp \
    kcdocumentrecorder.cpp

HEADERS += \
    Controls/GraphicButtons/kcgraphicbuttonbase.h \
    Controls/GraphicButtons/kcgraphicbuttonok.h \
    Controls/Preference/kcpreferenceitembase.h \
    Controls/Preference/kcpreferenceitembooleangroup.h \
    Controls/Preference/kcpreferenceitemboolean.h \
    Controls/Preference/kcpreferenceitemcombo.h \
    Controls/Preference/kcpreferenceitemint.h \
    Controls/Preference/kcpreferenceitempath.h \
    dbgoutputreceiver.h \
    fpc.h \
    gcc.h \
    gdbcontroller.h \
    gdbmivalue.h \
    highlighterGlobal.h \
    kcclipboard.h \
    kccodecompileprogress.h \
    kccodeeditor.h \
    kccolorconfigure.h \
    kccompiledock.h \
    kccompileoutputreceiver.h \
    kccompilerbase.h \
    kccompilerconfigure.h \
    kcconfigure.h \
    kcconnectionhandler.h \
    kccpphighlighter.h \
    kcdebugcommandio.h \
    kcdebugcontrolpanel.h \
    kcdebuggerconfigure.h \
    kcdebugwatch.h \
    kcdragproxy.h \
    kceditorconfigure.h \
    kcexecutor.h \
    kcfileassociation.h \
    kcfloattoolbar.h \
    kcfontconfigure.h \
    kcgeneralconfigure.h \
    kcglobal.h \
    kchighlighter.h \
    kchistoryconfigure.h \
    kcjudgedock.h \
    kclanguageconfigure.h \
    kclanguagemode.h \
    kclinenumpanel.h \
    kcmainwindow.h \
    kcmarkpanel.h \
    kcmessagebox.h \
    kcpanel.h \
    kcpascalhighlighter.h \
    kcplaintextbrowser.h \
    kcpreferenceembedded.h \
    kcpreference.h \
    kcpreferencelangaugelist.h \
    kcpreferencepager.h \
    kcpreferencesuperlist.h \
    kcreplacewindow.h \
    kcsearchlinetext.h \
    kcsearchwidget.h \
    kcsearchwindow.h \
    kcsidebar.h \
    kcsplashscreen.h \
    kcstatusbar.h \
    kcstatuscursorinfo.h \
    kcstatusrewriteinfo.h \
    kctabmanager.h \
    kctextblockdata.h \
    kctexteditor.h \
    kctextsearcher.h \
    kctitlebar.h \
    kcwelcomewindow.h \
    kreogistcutestyle.h \
    mainwindow.h \
    textcharformatmap.h \ 
    kcstatusrecorder.h \
    kcdocumentrecorder.h \
    qmljs_global.h


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
