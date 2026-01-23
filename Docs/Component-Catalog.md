# Rdk-CvBasicLib — Component Catalog

Компоненты из `Core/Basic.cpp`, сгруппированы по назначению. Для деталей см. `Architecture.md` / `API-Overview.md`.

## Capture / Sources
- **TCapture**, **TCaptureCamera**, **TCaptureCameraIp**, **TCaptureImageSequence**, **UBASource**, **UBASourceFile**, **UBASourceMultiFile**, **UBABitmapSource***, **UBASourceFreezeFrame**, **UBAReceiver** — источники и приёмники изображений/bitmap.  
  См. [`Capture & Sources`](Components/CaptureAndSources.md).

## Image Processing (UBA*)
- **ColorConvert** — см. [`ColorConvert`](Components/ColorConvert.md).
- **ResizeEdges**, **RotateSimple**, **UBAFlipImageSimple** — геометрические преобразования.  
  См. [`Geometric Transformations`](Components/GeometricTransformations.md).
- **Crop**, **Reduce** — см. [`Crop / Reduce`](Components/CropReduce.md).
- Фоновые и разностные операторы, бинаризация, маркировка — семейство UBA-компонентов.  
  См. [`Background / Difference / Binarization / Labeling / Looping / GUI`](Components/BackgroundBinarizationLabeling.md).
- **TLabelingSimple**, **UBShowRect**, **ShowObjectsSimple** — визуализация/маркировка (см. [`Detectors / Segmentators / Savers`](Components/DetectorsSegmentators.md)).
- **RotCameraSimulator**, **VideoSimulatorSimple**, **VideoSimulatorSimpleBin**, **Video3DSimulatorSimple**, **DataSimulatorSimple** — см. [`Video/Camera Simulators`](Components/VideoSimulators.md).
- **BStatisticSimple** — базовая статистика по изображениям (будет описана в отдельном компоненте).

## Math / Matrix Ops
- **UMatrixIntMath**, **UMatrixDoubleMath**, **UMDMatrixDoubleMux**, **UMDMatrixIntMux**, **UMDScalarDoubleMux**, **UMDScalarIntMux**, **BMathOperator** — см. [`Matrix/Scalar Math & Mux`](Components/MatrixMathMux.md).

## Pipelines / Models
- **UBPipeline**, **UBParallelPipeline**, **UBAModel**, а также статистика `UBStatistic*` — пайплайны, модели и сбор статистики.  
  См. [`Pipelines, Models & Statistics`](Components/PipelinesModelsStats.md).

## Classification / Detection / Segmentation
- **UCRPerseptron**, **UCRDirectCompare**, **UCRDistance**, **UCRFusion**, **UCRSample**, **UCRTeacherPerseptronBP/DL**, **UCRConvolutionNetwork**, **UCRTeacherCVNetworkBP**, **UCRPrincipalComponentAnalysis**, **UCRBarnesHutTSNE** — см. [`UCR* family`](Components/UCRFamily.md).
- **UClassifierBase**, **UClassifierResSaver**, **UDetectorBase**, **UDetResSaverPVOC**, **USegmentatorBase**, а также визуальные UBA-компоненты — см. [`Detectors / Segmentators / Savers`](Components/DetectorsSegmentators.md).
- **UBAMovingDetector***, **UBANightMovingDetector**, **UBACollateMovingDetector**, **UBAObjectDetector***, **UBANightDetector** — детекторы движения.  
  См. [`Moving Detectors`](Components/MovingDetectors.md).
- **UBAReceiver**, **UBShowRect** — приёмник и визуализация прямоугольников.  
  См. [`Receiver & ShowRect`](Components/ReceiverAndShowRect.md).

## Использование (приоритет)
Часто встречаются в `Bin/Configs`: `ColorConvert`, `Crop`, `Reduce`, `TBinarizationSimple`, `UMatrix*`, `UCR*`, `VideoSimulator*`, `RotCameraSimulator`, `BStatisticSimple`, `UMD*Mux`.
