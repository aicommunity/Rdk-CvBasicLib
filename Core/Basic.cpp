/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBGRAPHICS_BASIC_CPP
#define UBGRAPHICS_BASIC_CPP

#include "Basic.h"


namespace RDK{

CvBasicLib CvBasicLibrary;

// --------------------------
// Конструкторы и деструкторы
// --------------------------
CvBasicLib::CvBasicLib(void)
 : ULibrary("CvBasicLib","1.0", GetGlobalVersion())
{
}
// --------------------------

// --------------------------
// Методы заполенения бибилиотеки
// --------------------------
// Заполняет массив ClassSamples готовыми экземплярами образцов и их именами.
// Не требуется предварительная очистка массива и уборка памяти.
void CvBasicLib::CreateClassSamples(UStorage *storage)
{
 UContainer *cont;
 cont=new UBAColorConvert;
 cont->SetName("ColorConvert");
 cont->Default();
 UploadClass("ColorConvert",cont);

 cont=new UBAResizeEdges;
 cont->SetName("ResizeEdges");
 cont->Default();
 UploadClass("ResizeEdges",cont);

 cont=new UBARotateSimple;
 cont->SetName("RotateSimple");
 cont->Default();
 UploadClass("RotateSimple",cont);

 cont=new UBAModel;
 cont->SetName("Model");
 cont->Default();
 UploadClass("Model",cont);

 cont=new UBPipeline;
 cont->SetName("Pipeline");
 cont->Default();
 UploadClass("Pipeline",cont);

 cont=new UBParallelPipeline;
 cont->SetName("ParallelPipeline");
 cont->Default();
 UploadClass("ParallelPipeline",cont);

 cont=new UBASource;
 cont->SetName("Source");
 cont->Default();
 UploadClass("Source",cont);

 cont=new UBASourceFile;
 cont->SetName("Source");
 cont->Default();
 UploadClass("SourceFile",cont);

 cont=new UBASourceMultiFile;
 cont->SetName("Source");
 cont->Default();
 UploadClass("SourceMultiFile",cont);

 cont=new UBAReceiver;
 cont->SetName("Receiver");
 cont->Default();
 UploadClass("Receiver",cont);

 cont=new UBACrop;
 cont->SetName("Crop");
 cont->Default();
 UploadClass("Crop",cont);

 cont=new UBAReduce;
 cont->SetName("Reduce");
 cont->Default();
 UploadClass("Reduce",cont);

 cont=new UBAFlipImageSimple;
 cont->SetName("FlipImage");
 cont->Default();
 UploadClass("UBAFlipImageSimple",cont);

 cont=new UMDMatrixMux<double>;
 cont->SetName("MDMatrixDoubleMux");
 cont->Default();
 UploadClass("UMDMatrixDoubleMux",cont);

 cont=new UMDMatrixMux<int>;
 cont->SetName("MDMatrixIntMux");
 cont->Default();
 UploadClass("UMDMatrixIntMux",cont);

 cont=new UBMathOperator;
 cont->SetName("BMathOperator");
 cont->Default();
 UploadClass("BMathOperator",cont);

 cont=new UMatrixMath<int>;
 cont->SetName("MatrixIntMath");
 cont->Default();
 UploadClass("UMatrixIntMath",cont);

 cont=new UMatrixMath<double>;
 cont->SetName("MatrixDoubleMath");
 cont->Default();
 UploadClass("UMatrixDoubleMath",cont);

 cont=new UMDScalarMux<double>;
 cont->SetName("MDScalarDoubleMux");
 cont->Default();
 UploadClass("UMDScalarDoubleMux",cont);

 cont=new UMDScalarMux<int>;
 cont->SetName("MDScalarIntMux");
 cont->Default();
 UploadClass("UMDScalarIntMux",cont);

  cont=new UBADifferenceFrameSimple;
 cont->SetName("DifferenceFrameSimple");
 cont->Default();
 UploadClass("DifferenceFrameSimple",cont);

 cont=new UBABackgroundAvg;
 cont->SetName("Background");
 cont->Default();
 UploadClass("BackgroundAvg",cont);

 cont=new UBABinarizationSimple;
 cont->SetName("Binarization");
 cont->Default();
 UploadClass("TBinarizationSimple",cont);

 cont=new UBABinarizationSimpleAdaptiveThreshold;
 cont->SetName("Binarization");
 cont->Default();
 UploadClass("TBinarizationSimpleAdaptiveThreshold",cont);

 cont=new UBALabelingSimple;
 cont->SetName("Labeling");
 cont->Default();
 UploadClass("TLabelingSimple",cont);


 cont=new UBABackgroundExponnential;
 cont->SetName("Background");
 cont->Default();
 UploadClass("BackgroundExponnential",cont);

 cont=new UBADeltaBackgroundExponnential;
 cont->SetName("DeltaBackground");
 cont->Default();
 UploadClass("DeltaBackgroundExponnential",cont);

 cont=new UBABackgroundSimpleAdaptive;
 cont->SetName("Background");
 cont->Default();
 UploadClass("BackgroundSimpleAdaptive",cont);

 cont=new UBABinarizationOtsu;
 cont->SetName("Binarization");
 cont->Default();
 UploadClass("UBABinarizationOtsu",cont);

 cont=new UBABackgroundDependDiff;
 cont->SetName("Background");
 cont->Default();
 UploadClass("UBABackgroundDependDiff",cont);

 cont=new UBShowRect;
 cont->SetName("ShowRect");
 cont->Default();
 UploadClass("UBShowRect",cont);

 cont=new UBAShowObjectsSimple;
 cont->SetName("ShowObjectsSimple");
 cont->Default();
 UploadClass("ShowObjectsSimple",cont);

  cont=new UBAVideoSimulatorSimple;
 cont->SetName("VideoSimulatorSimple");
 cont->Default();
 UploadClass("VideoSimulatorSimple",cont);

 cont=new UBARotCameraSimulator;
 cont->SetName("RotCameraSimulator");
 cont->Default();
 UploadClass("RotCameraSimulator",cont);

 cont=new UBAVideoSimulatorSimpleBin;
 cont->SetName("VideoSimulatorSimpleBin");
 cont->Default();
 UploadClass("VideoSimulatorSimpleBin",cont);
			   /*
 cont=new UBAVideo3DSimulatorSimple;
 cont->SetName("Video3DSimulatorSimple");
 cont->Default();
 UploadClass("Video3DSimulatorSimple",cont);
                 */
 cont=new UBADataSimulatorSimple;
 cont->SetName("DataSimulatorSimple");
 cont->Default();
 UploadClass("DataSimulatorSimple",cont);

 cont=new UBABitmapSourceSimple;
 cont->SetName("BitmapSourceSimple");
 cont->Default();
 UploadClass("BitmapSourceSimple",cont);

 cont=new UBABitmapSourceFile;
 cont->SetName("BitmapSourceFile");
 cont->Default();
 UploadClass("BitmapSourceFile",cont);

 cont=new UBASourceFreezeFrame;
 cont->SetName("BitmapSourceFreezeFrame");
 cont->Default();

 cont=new UBStatisticSimple;
 cont->SetName("BStatisticSimple");
 cont->Default();
 UploadClass("BStatisticSimple",cont);

/*
 cont=new UCRPerseptron;
 cont->SetName("CRPerseptron");
 cont->Default();
 UploadClass("UCRPerseptron",cont);

 cont=new UCRDirectCompare;
 cont->SetName("CRDirectCompare");
 cont->Default();
 UploadClass("UCRDirectCompare",cont);

 cont=new UCRDistance;
 cont->SetName("CRDistance");
 cont->Default();
 UploadClass("UCRDistance",cont);

 cont=new UCRFusion;
 cont->SetName("CRFusion");
 cont->Default();
 UploadClass("UCRFusion",cont);

 cont=new UCRSample;
 cont->SetName("CRSample");
 cont->Default();
 UploadClass("UCRSample",cont);

 cont=new UCRTeacherPerseptronBP;
 cont->SetName("CRTeacherPerseptronBP");
 cont->Default();
 UploadClass("UCRTeacherPerseptronBP",cont);


 cont=new UCRTeacherPerseptronDL;
 cont->SetName("CRTeacherPerseptronDL");
 cont->Default();
 UploadClass("UCRTeacherPerseptronDL",cont);

 cont=new UCRConvolutionNetwork;
 cont->SetName("CRConvolutionNetwork");
 cont->Default();
 UploadClass("UCRConvolutionNetwork",cont);

 cont=new UCRTeacherCVNetworkBP;
 cont->SetName("CRTeacherCVNetworkBP");
 cont->Default();
 UploadClass("UCRTeacherCVNetworkBP",cont);
*/
 cont=new UClassifierBase;
 cont->SetName("ClassifierBase");
 cont->Default();
 UploadClass("UClassifierBase",cont);

 cont=new UDetectorBase;
 cont->SetName("DetectorBase");
 cont->Default();
 UploadClass("UDetectorBase",cont);

 cont=new USegmentatorBase;
 cont->SetName("SegmentatorBase");
 cont->Default();
 UploadClass("USegmentatorBase",cont);

 cont=new UClassifierResSaver;
 cont->SetName("ClassifierResSaver");
 cont->Default();
 UploadClass("UClassifierResSaver",cont);

 cont=new UDetResSaverPVOC;
 cont->SetName("DetResSaverPVOC");
 cont->Default();
 UploadClass("UDetResSaverPVOC",cont);

 cont=new UCRPrincipalComponentAnalysis;
 cont->SetName("CRPrincipalComponentAnalysis");
 cont->Default();
 UploadClass("UCRPrincipalComponentAnalysis",cont);

 cont=new UCRBarnesHutTSNE;
 cont->SetName("CRBarnesHutTSNE");
 cont->Default();
 UploadClass("UCRBarnesHutTSNE",cont);

 UploadClass<TCaptureImageSequence>("TCaptureImageSequence","Capture");
}

bool CvBasicLib::CvBasicLibCrPropMock(RDK::USerStorageXML *serstorage, RDK::UMockUNet *mock_unet)
{
    return BaseCrPropMockTempl<CvBasicLib>(serstorage,mock_unet);
}
// --------------------------


}

#endif
