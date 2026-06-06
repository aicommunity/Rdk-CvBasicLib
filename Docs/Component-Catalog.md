# Rdk-CvBasicLib — Component Catalog

## RU

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
Часто встречаются в `Bin/Configs`: `ColorConvert`, `Crop`, `Reduce`, `TBinarizationSimple`, `TBinarizationSimpleAdaptiveThreshold`, `UMatrix*`, `UCR*`, `VideoSimulator*`, `RotCameraSimulator`, `BStatisticSimple`, `UMD*Mux`.

---

## EN

Components from `Core/Basic.cpp`, grouped by purpose. For details see `Architecture.md` / `API-Overview.md`.

## Capture / Sources

- **TCapture**, **TCaptureCamera**, **TCaptureCameraIp**, **TCaptureImageSequence**, **UBASource**, **UBASourceFile**, **UBASourceMultiFile**, **UBABitmapSource***, **UBASourceFreezeFrame**, **UBAReceiver** — image/bitmap sources and receivers.  
  See [`Capture & Sources`](Components/CaptureAndSources.md).

## Image Processing (UBA*)

- **ColorConvert** — see [`ColorConvert`](Components/ColorConvert.md).
- **ResizeEdges**, **RotateSimple**, **UBAFlipImageSimple** — geometric transforms.  
  See [`Geometric Transformations`](Components/GeometricTransformations.md).
- **Crop**, **Reduce** — see [`Crop / Reduce`](Components/CropReduce.md).
- Background and difference operators, binarization, labeling — UBA component family.  
  See [`Background / Difference / Binarization / Labeling / Looping / GUI`](Components/BackgroundBinarizationLabeling.md).
- **TLabelingSimple**, **UBShowRect**, **ShowObjectsSimple** — visualization/labeling (see [`Detectors / Segmentators / Savers`](Components/DetectorsSegmentators.md)).
- **RotCameraSimulator**, **VideoSimulatorSimple**, **VideoSimulatorSimpleBin**, **Video3DSimulatorSimple**, **DataSimulatorSimple** — see [`Video/Camera Simulators`](Components/VideoSimulators.md).
- **BStatisticSimple** — basic image statistics (to be described in a separate component doc).

## Math / Matrix Ops

- **UMatrixIntMath**, **UMatrixDoubleMath**, **UMDMatrixDoubleMux**, **UMDMatrixIntMux**, **UMDScalarDoubleMux**, **UMDScalarIntMux**, **BMathOperator** — see [`Matrix/Scalar Math & Mux`](Components/MatrixMathMux.md).

## Pipelines / Models

- **UBPipeline**, **UBParallelPipeline**, **UBAModel**, and statistics `UBStatistic*` — pipelines, models, and statistics collection.  
  See [`Pipelines, Models & Statistics`](Components/PipelinesModelsStats.md).

## Classification / Detection / Segmentation

- **UCRPerseptron**, **UCRDirectCompare**, **UCRDistance**, **UCRFusion**, **UCRSample**, **UCRTeacherPerseptronBP/DL**, **UCRConvolutionNetwork**, **UCRTeacherCVNetworkBP**, **UCRPrincipalComponentAnalysis**, **UCRBarnesHutTSNE** — see [`UCR* family`](Components/UCRFamily.md).
- **UClassifierBase**, **UClassifierResSaver**, **UDetectorBase**, **UDetResSaverPVOC**, **USegmentatorBase**, and visual UBA components — see [`Detectors / Segmentators / Savers`](Components/DetectorsSegmentators.md).
- **UBAMovingDetector***, **UBANightMovingDetector**, **UBACollateMovingDetector**, **UBAObjectDetector***, **UBANightDetector** — motion detectors.  
  See [`Moving Detectors`](Components/MovingDetectors.md).
- **UBAReceiver**, **UBShowRect** — receiver and rectangle visualization.  
  See [`Receiver & ShowRect`](Components/ReceiverAndShowRect.md).

## Usage (priority)

Commonly found in `Bin/Configs`: `ColorConvert`, `Crop`, `Reduce`, `TBinarizationSimple`, `TBinarizationSimpleAdaptiveThreshold`, `UMatrix*`, `UCR*`, `VideoSimulator*`, `RotCameraSimulator`, `BStatisticSimple`, `UMD*Mux`.
