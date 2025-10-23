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
// ������������ � �����������
// --------------------------
CvBasicLib::CvBasicLib(void)
 : ULibrary("CvBasicLib","1.0", GetGlobalVersion())
{
}
// --------------------------

// --------------------------
// ������ ����������� �����������
// --------------------------
// ��������� ������ ClassSamples �������� ������������ �������� � �� �������.
// �� ��������� ��������������� ������� ������� � ������ ������.
void CvBasicLib::CreateClassSamples(UStorage *storage)
{
 std::shared_ptr<UContainer> cont;
 cont=std::make_shared<UBAColorConvert>();
 cont->SetName("ColorConvert");
 cont->Default();
 UploadClass("ColorConvert",cont);

 cont=std::make_shared<UBAResizeEdges>();
 cont->SetName("ResizeEdges");
 cont->Default();
 UploadClass("ResizeEdges",cont);

 cont=std::make_shared<UBARotateSimple>();
 cont->SetName("RotateSimple");
 cont->Default();
 UploadClass("RotateSimple",cont);

 cont=std::make_shared<UBAModel>();
 cont->SetName("Model");
 cont->Default();
 UploadClass("Model",cont);

 cont=std::make_shared<UBPipeline>();
 cont->SetName("Pipeline");
 cont->Default();
 UploadClass("Pipeline",cont);

 cont=std::make_shared<UBParallelPipeline>();
 cont->SetName("ParallelPipeline");
 cont->Default();
 UploadClass("ParallelPipeline",cont);

 cont=std::make_shared<UBASource>();
 cont->SetName("Source");
 cont->Default();
 UploadClass("Source",cont);

 cont=std::make_shared<UBASourceFile>();
 cont->SetName("Source");
 cont->Default();
 UploadClass("SourceFile",cont);

 cont=std::make_shared<UBASourceMultiFile>();
 cont->SetName("Source");
 cont->Default();
 UploadClass("SourceMultiFile",cont);

 cont=std::make_shared<UBAReceiver>();
 cont->SetName("Receiver");
 cont->Default();
 UploadClass("Receiver",cont);

 cont=std::make_shared<UBACrop>();
 cont->SetName("Crop");
 cont->Default();
 UploadClass("Crop",cont);

 cont=std::make_shared<UBAReduce>();
 cont->SetName("Reduce");
 cont->Default();
 UploadClass("Reduce",cont);

 cont=std::make_shared<UBAFlipImageSimple>();
 cont->SetName("FlipImage");
 cont->Default();
 UploadClass("UBAFlipImageSimple",cont);

 cont=std::make_shared<UMDMatrixMux<double>>();
 cont->SetName("MDMatrixDoubleMux");
 cont->Default();
 UploadClass("UMDMatrixDoubleMux",cont);

 cont=std::make_shared<UMDMatrixMux<int>>();
 cont->SetName("MDMatrixIntMux");
 cont->Default();
 UploadClass("UMDMatrixIntMux",cont);

 cont=std::make_shared<UBMathOperator>();
 cont->SetName("BMathOperator");
 cont->Default();
 UploadClass("BMathOperator",cont);

 cont=std::make_shared<UMatrixMath<int>>();
 cont->SetName("MatrixIntMath");
 cont->Default();
 UploadClass("UMatrixIntMath",cont);

 cont=std::make_shared<UMatrixMath<double>>();
 cont->SetName("MatrixDoubleMath");
 cont->Default();
 UploadClass("UMatrixDoubleMath",cont);

 cont=std::make_shared<UMDScalarMux<double>>();
 cont->SetName("MDScalarDoubleMux");
 cont->Default();
 UploadClass("UMDScalarDoubleMux",cont);

 cont=std::make_shared<UMDScalarMux<int>>();
 cont->SetName("MDScalarIntMux");
 cont->Default();
 UploadClass("UMDScalarIntMux",cont);

  cont=std::make_shared<UBADifferenceFrameSimple>();
 cont->SetName("DifferenceFrameSimple");
 cont->Default();
 UploadClass("DifferenceFrameSimple",cont);

 cont=std::make_shared<UBABackgroundAvg>();
 cont->SetName("Background");
 cont->Default();
 UploadClass("BackgroundAvg",cont);

 cont=std::make_shared<UBABinarizationSimple>();
 cont->SetName("Binarization");
 cont->Default();
 UploadClass("TBinarizationSimple",cont);

 cont=std::make_shared<UBABinarizationSimpleAdaptiveThreshold>();
 cont->SetName("Binarization");
 cont->Default();
 UploadClass("TBinarizationSimpleAdaptiveThreshold",cont);

 cont=std::make_shared<UBALabelingSimple>();
 cont->SetName("Labeling");
 cont->Default();
 UploadClass("TLabelingSimple",cont);


 cont=std::make_shared<UBABackgroundExponnential>();
 cont->SetName("Background");
 cont->Default();
 UploadClass("BackgroundExponnential",cont);

 cont=std::make_shared<UBADeltaBackgroundExponnential>();
 cont->SetName("DeltaBackground");
 cont->Default();
 UploadClass("DeltaBackgroundExponnential",cont);

 cont=std::make_shared<UBABackgroundSimpleAdaptive>();
 cont->SetName("Background");
 cont->Default();
 UploadClass("BackgroundSimpleAdaptive",cont);

 cont=std::make_shared<UBABinarizationOtsu>();
 cont->SetName("Binarization");
 cont->Default();
 UploadClass("UBABinarizationOtsu",cont);

 cont=std::make_shared<UBABackgroundDependDiff>();
 cont->SetName("Background");
 cont->Default();
 UploadClass("UBABackgroundDependDiff",cont);

 cont=std::make_shared<UBShowRect>();
 cont->SetName("ShowRect");
 cont->Default();
 UploadClass("UBShowRect",cont);

 cont=std::make_shared<UBAShowObjectsSimple>();
 cont->SetName("ShowObjectsSimple");
 cont->Default();
 UploadClass("ShowObjectsSimple",cont);

  cont=std::make_shared<UBAVideoSimulatorSimple>();
 cont->SetName("VideoSimulatorSimple");
 cont->Default();
 UploadClass("VideoSimulatorSimple",cont);

 cont=std::make_shared<UBARotCameraSimulator>();
 cont->SetName("RotCameraSimulator");
 cont->Default();
 UploadClass("RotCameraSimulator",cont);

 cont=std::make_shared<UBAVideoSimulatorSimpleBin>();
 cont->SetName("VideoSimulatorSimpleBin");
 cont->Default();
 UploadClass("VideoSimulatorSimpleBin",cont);
			   /*
 cont=new UBAVideo3DSimulatorSimple;
 cont->SetName("Video3DSimulatorSimple");
 cont->Default();
 UploadClass("Video3DSimulatorSimple",cont);
                 */
 cont=std::make_shared<UBADataSimulatorSimple>();
 cont->SetName("DataSimulatorSimple");
 cont->Default();
 UploadClass("DataSimulatorSimple",cont);

 cont=std::make_shared<UBABitmapSourceSimple>();
 cont->SetName("BitmapSourceSimple");
 cont->Default();
 UploadClass("BitmapSourceSimple",cont);

 cont=std::make_shared<UBABitmapSourceFile>();
 cont->SetName("BitmapSourceFile");
 cont->Default();
 UploadClass("BitmapSourceFile",cont);

 cont=std::make_shared<UBASourceFreezeFrame>();
 cont->SetName("BitmapSourceFreezeFrame");
 cont->Default();

 cont=std::make_shared<UBStatisticSimple>();
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
 cont=std::make_shared<UClassifierBase>();
 cont->SetName("ClassifierBase");
 cont->Default();
 UploadClass("UClassifierBase",cont);

 cont=std::make_shared<UDetectorBase>();
 cont->SetName("DetectorBase");
 cont->Default();
 UploadClass("UDetectorBase",cont);

 cont=std::make_shared<USegmentatorBase>();
 cont->SetName("SegmentatorBase");
 cont->Default();
 UploadClass("USegmentatorBase",cont);

 cont=std::make_shared<UClassifierResSaver>();
 cont->SetName("ClassifierResSaver");
 cont->Default();
 UploadClass("UClassifierResSaver",cont);

 cont=std::make_shared<UDetResSaverPVOC>();
 cont->SetName("DetResSaverPVOC");
 cont->Default();
 UploadClass("UDetResSaverPVOC",cont);

 cont=std::make_shared<UCRPrincipalComponentAnalysis>();
 cont->SetName("CRPrincipalComponentAnalysis");
 cont->Default();
 UploadClass("UCRPrincipalComponentAnalysis",cont);

 cont=std::make_shared<UCRBarnesHutTSNE>();
 cont->SetName("CRBarnesHutTSNE");
 cont->Default();
 UploadClass("UCRBarnesHutTSNE",cont);

 // UploadClass<TCaptureImageSequence>("TCaptureImageSequence","Capture");
 {
  auto cap = std::make_shared<TCaptureImageSequence>();
  cap->SetName("Capture");
  cap->Default();
  UploadClass("TCaptureImageSequence", cap);
 }
}

bool CvBasicLib::CvBasicLibCrPropMock(RDK::USerStorageXML *serstorage, RDK::UMockUNet *mock_unet)
{
    return BaseCrPropMockTempl<CvBasicLib>(serstorage,mock_unet);
}
// --------------------------


}

#endif
