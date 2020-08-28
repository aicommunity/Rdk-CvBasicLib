#-------------------------------------------------
#
# Project created by QtCreator 2012-11-11T15:17:55
#
#-------------------------------------------------

QT       -= gui

TARGET = Rdk-CvBasicLib.qt
TEMPLATE = lib
CONFIG += staticlib

include($$PWD/../../../../Rdk/Build/Lib/Qt/RdkDefines.pri)

DEFINES += LIBRDK_LIBRARY_EXPORT
DEFINES += RDK_UNICODE_RUN
DEFINES += RDK_QT

VERSION = $$system(hg parents --template '{rev}')
DEFINES += RDK_LIB_CVS_REVISION=$$VERSION

unix {
    DESTDIR = $$PWD/../../../../Bin/Platform/Linux/Lib.Qt
}

windows {
    DESTDIR = $$PWD/../../../../Bin/Platform/Win/Lib.Qt
}

HEADERS += \
    ../../Core/Basic.h \
    ../../Core/UBAColorConvert.h \
    ../../Core/UBACrop.h \
    ../../Core/UBAFlipImage.h \
    ../../Core/UBAModel.h \
    ../../Core/UBAReceiver.h \
    ../../Core/UBAReduce.h \
    ../../Core/UBAResize.h \
    ../../Core/UBARotate.h \
    ../../Core/UBASource.h \
    ../../Core/UBASourceFile.h \
    ../../Core/UBASourceMultiFile.h \
    ../../Core/UBPipeline.h

SOURCES += \
    ../../Core/Basic.cpp \
    ../../Core/UBAColorConvert.cpp \
    ../../Core/UBACrop.cpp \
    ../../Core/UBAFlipImage.cpp \
    ../../Core/UBAModel.cpp \
    ../../Core/UBAReceiver.cpp \
    ../../Core/UBAReduce.cpp \
    ../../Core/UBAResize.cpp \
    ../../Core/UBARotate.cpp \
    ../../Core/UBASource.cpp \
    ../../Core/UBASourceFile.cpp \
    ../../Core/UBASourceMultiFile.cpp \
    ../../Core/UBPipeline.cpp
