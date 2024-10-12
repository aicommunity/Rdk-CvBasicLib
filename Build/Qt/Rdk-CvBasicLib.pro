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

VERSION = 0 # $$system(hg parents --template '{rev}')
DEFINES += RDK_LIB_CVS_REVISION=$$VERSION

unix {
    DESTDIR = $$PWD/../../../../Bin/Platform/Linux/Lib.Qt
}

windows {
    DESTDIR = $$PWD/../../../../Bin/Platform/Win/Lib.Qt
}

HEADERS += \
    ../../Core/Basic.h \
    ../../Core/TCapture.h \
    ../../Core/TCaptureCamera.h \
    ../../Core/TCaptureCameraIp.h \
    ../../Core/TCaptureImageSequence.h \
    ../../Core/TCaptureSupport.h \
    ../../Core/TSNE/sptree.h \
    ../../Core/TSNE/tsne.h \
    ../../Core/TSNE/vptree.h \
    ../../Core/UBABackground.h \
    ../../Core/UBABinarization.h \
    ../../Core/UBABitmapSource.h \
    ../../Core/UBAColorConvert.h \
    ../../Core/UBACrop.h \
    ../../Core/UBADataSimulator.h \
    ../../Core/UBADifferenceFrame.h \
    ../../Core/UBAFlipImage.h \
    ../../Core/UBAGuiSelection.h \
    ../../Core/UBALabeling.h \
    ../../Core/UBALooping.h \
    ../../Core/UBAModel.h \
    ../../Core/UBAMovingDetector.h \
    ../../Core/UBAObjectDetector.h \
    ../../Core/UBAReceiver.h \
    ../../Core/UBAReduce.h \
    ../../Core/UBAResize.h \
    ../../Core/UBARotCameraSimulator.h \
    ../../Core/UBARotate.h \
    ../../Core/UBAShowObjects.h \
    ../../Core/UBASource.h \
    ../../Core/UBASourceFile.h \
    ../../Core/UBASourceMultiFile.h \
    ../../Core/UBAVideoSimulator.h \
    ../../Core/UBMathOperator.h \
    ../../Core/UBPipeline.h \
    ../../Core/UBShowRect.h \
    ../../Core/UBStatistic.h \
    ../../Core/UCRBarnesHutTSNE.h \
    ../../Core/UCRPrincipalComponentAnalysis.h \
    ../../Core/UCRTeacher.h \
    ../../Core/UClassifierBase.h \
    ../../Core/UClassifierResSaver.h \
    ../../Core/UDetResSaverPVOC.h \
    ../../Core/UDetectorBase.h \
    ../../Core/UMDMatrixMux.h \
    ../../Core/UMatrixMath.h \
    ../../Core/USegmentatorBase.h

SOURCES += \
    ../../Core/Basic.cpp \
    ../../Core/TCapture.cpp \
    ../../Core/TCaptureCamera.cpp \
    ../../Core/TCaptureCameraIp.cpp \
    ../../Core/TCaptureImageSequence.cpp \
    ../../Core/TCaptureSupport.cpp \
    ../../Core/TSNE/sptree.cpp \
    ../../Core/TSNE/tsne.cpp \
    ../../Core/UBABackground.cpp \
    ../../Core/UBABinarization.cpp \
    ../../Core/UBABitmapSource.cpp \
    ../../Core/UBAColorConvert.cpp \
    ../../Core/UBACrop.cpp \
    ../../Core/UBADataSimulator.cpp \
    ../../Core/UBADifferenceFrame.cpp \
    ../../Core/UBAFlipImage.cpp \
    ../../Core/UBAGuiSelection.cpp \
    ../../Core/UBALabeling.cpp \
    ../../Core/UBALooping.cpp \
    ../../Core/UBAModel.cpp \
    ../../Core/UBAMovingDetector.cpp \
    ../../Core/UBAObjectDetector.cpp \
    ../../Core/UBAReceiver.cpp \
    ../../Core/UBAReduce.cpp \
    ../../Core/UBAResize.cpp \
    ../../Core/UBARotCameraSimulator.cpp \
    ../../Core/UBARotate.cpp \
    ../../Core/UBAShowObjects.cpp \
    ../../Core/UBASource.cpp \
    ../../Core/UBASourceFile.cpp \
    ../../Core/UBASourceMultiFile.cpp \
    ../../Core/UBAVideoSimulator.cpp \
    ../../Core/UBMathOperator.cpp \
    ../../Core/UBPipeline.cpp \
    ../../Core/UBShowRect.cpp \
    ../../Core/UBStatistic.cpp \
    ../../Core/UCRBarnesHutTSNE.cpp \
    ../../Core/UCRPrincipalComponentAnalysis.cpp \
    ../../Core/UClassifierBase.cpp \
    ../../Core/UClassifierResSaver.cpp \
    ../../Core/UDetResSaverPVOC.cpp \
    ../../Core/UDetectorBase.cpp \
    ../../Core/UMDMatrixMux.cpp \
    ../../Core/UMatrixMath.cpp \
    ../../Core/USegmentatorBase.cpp
