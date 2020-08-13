#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T13:09:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lcsniff
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QMAKE_CXXFLAGS_RELEASE += -O2

SOURCES += \
    src/main.cpp \
    qhexedit2/src/chunks.cpp \
    qhexedit2/src/commands.cpp \
    qhexedit2/src/qhexedit.cpp \
    src/mainwindow.cpp \
    src/usbitem.cpp \
    src/usbmodel.cpp \
    src/usbpacket.cpp \
    src/usbrecord.cpp \
    src/helpers.cpp \
    src/usbgroup.cpp \
    src/usbtransaction.cpp \
    src/usbaggregator.cpp \
    src/capture.cpp \
    xbar/etherbone.c \
    xbar/xbar.c \
    src/configurewindow.cpp \
    src/usbproxy.cpp \
    src/filterwindow.cpp \
    src/msgitem.cpp \
    src/msgmodel.cpp \
    parser/parse.c \
    xbar/ft60x/fops.c \
    src/aboutwindow.cpp \
    src/lcsniffapplication.cpp \
    src/pcapexport.cpp

HEADERS += \
    qhexedit2/src/commands.h \
    qhexedit2/src/chunks.h \
    qhexedit2/src/qhexedit.h \
    src/mainwindow.h \
    src/usbitem.h \
    src/usbmodel.h \
    src/usbpacket.h \
    src/usbproxyfilter.h \
    src/usbrecord.h \
    src/helpers.h \
    src/usbgroup.h \
    src/usbtransaction.h \
    src/usbaggregator.h \
    src/capture.h \
    xbar/csr.h \
    xbar/etherbone.h \
    xbar/flags.h \
    xbar/sdram_phy.h \
    xbar/xbar.h \
    src/configurewindow.h \
    src/usbproxy.h \
    src/filterwindow.h \
    src/msgitem.h \
    src/msgmodel.h \
    parser/parse.h \
    xbar/ft60x/fops.h \
    src/aboutwindow.h \
    src/lcsniffapplication.h \
    src/pcapexport.h

FORMS += \
    ui/mainwindow.ui \
    ui/configurewindow.ui \
    ui/filterwindow.ui \
    ui/aboutwindow.ui

# Default rules for deployment.
# Attempt to set the PREFIX variable from one of these sources:
# 1. PREFIX qmake variable (i.e. leave it as-is)
# 2. PREFIX environment variable
# 3. Platform-specific defaults
isEmpty(PREFIX) {
	ENV_PREFIX = $$(PREFIX)
	!isEmpty(ENV_PREFIX): PREFIX = $$ENV_PREFIX
	else:qnx: PREFIX = /tmp/$${TARGET}
	else:unix:!android: PREFIX = /opt/$${TARGET}
}

!isEmpty(PREFIX) {
	target.path = $$PREFIX/bin
	INSTALLS += target
}

RESOURCES += \
    resources.qrc

win32 {
    contains(QT_ARCH, i386) {
        LIBS += -L$$PWD/xbar/ft60x/FTD3XXLibrary/Win32/ -lFTD3XX
    } else {
        LIBS += -L$$PWD/xbar/ft60x/FTD3XXLibrary/x64/ -lFTD3XX
    }
}
macx: LIBS += -L$$PWD/xbar/ft60x/FTD3XXLibrary/macOS/ -lftd3xx

mac {
    Resources.files += $$PWD/xbar/ft60x/FTD3XXLibrary/macOS/libftd3xx.dylib
    Resources.path = Contents/MacOS
    QMAKE_BUNDLE_DATA += Resources
    QMAKE_INFO_PLIST = $$PWD/lcsniff.plist
}

# INCLUDEPATH += $$PWD/xbar/ft60x/FTD3XXLibrary/Win32
INCLUDEPATH += $$PWD/qhexedit2/src
# DEPENDPATH += $$PWD/xbar/ft60x/FTD3XXLibrary/Win32

win32:!win32-g++ {
    contains(QT_ARCH, i386) {
        PRE_TARGETDEPS += $$PWD/xbar/ft60x/FTD3XXLibrary/Win32/FTD3XX.lib
    } else {
        PRE_TARGETDEPS += $$PWD/xbar/ft60x/FTD3XXLibrary/x64/FTD3XX.lib
    }
}
