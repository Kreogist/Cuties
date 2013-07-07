TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = KciConsoleRummer

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
