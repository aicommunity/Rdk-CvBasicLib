# Rdk-CvBasicLib — Component Catalog

Компоненты из `Core/Basic.cpp`, сгруппированы по назначению. Для деталей см. `Architecture.md` / `API-Overview.md`.

## Capture / Sources
- **TCaptureImageSequence**, **Capture**, **UBASource**, **Source**, **SourceFile**, **SourceMultiFile**, **BitmapSourceSimple**, **BitmapSourceFile**, **Receiver**, **UBAReceiver** — источники и приёмники изображений/bitmap (см. будущие компоненты в `Docs/Components` по мере детализации).

## Image Processing (UBA*)
- **ColorConvert** — см. [`ColorConvert`](Components/ColorConvert.md).
- **ResizeEdges**, **RotateSimple**, **UBAFlipImageSimple**, фоновые и разностные операторы, бинаризация, маркировка — семейство UBA-компонентов, описываемое в `Docs/Components/*.md` (подробные файлы для ключевых операторов будут добавляться по мере необходимости).
- **Crop**, **Reduce** — см. [`Crop / Reduce`](Components/CropReduce.md).
- **TLabelingSimple**, **UBShowRect**, **ShowObjectsSimple** — визуализация/маркировка (см. [`Detectors / Segmentators / Savers`](Components/DetectorsSegmentators.md)).
- **RotCameraSimulator**, **VideoSimulatorSimple**, **VideoSimulatorSimpleBin**, **Video3DSimulatorSimple**, **DataSimulatorSimple** — см. [`Video/Camera Simulators`](Components/VideoSimulators.md).
- **BStatisticSimple** — базовая статистика по изображениям (будет описана в отдельном компоненте).

## Math / Matrix Ops
- **UMatrixIntMath**, **UMatrixDoubleMath**, **UMDMatrixDoubleMux**, **UMDMatrixIntMux**, **UMDScalarDoubleMux**, **UMDScalarIntMux**, **BMathOperator** — см. [`Matrix/Scalar Math & Mux`](Components/MatrixMathMux.md).

## Pipelines / Models
- **Model**, **UBPipeline**, **ParallelPipeline**, **UBAModel** — пайплайны и модели (для них могут быть созданы отдельные файлы компонентов).

## Classification / Detection / Segmentation
- **UCRPerseptron**, **UCRDirectCompare**, **UCRDistance**, **UCRFusion**, **UCRSample**, **UCRTeacherPerseptronBP/DL**, **UCRConvolutionNetwork**, **UCRTeacherCVNetworkBP**, **UCRPrincipalComponentAnalysis**, **UCRBarnesHutTSNE** — см. [`UCR* family`](Components/UCRFamily.md).
- **UClassifierBase**, **UClassifierResSaver**, **UDetectorBase**, **UDetResSaverPVOC**, **USegmentatorBase**, а также визуальные UBA-компоненты — см. [`Detectors / Segmentators / Savers`](Components/DetectorsSegmentators.md).

## Использование (приоритет)
Часто встречаются в `Bin/Configs`: `ColorConvert`, `Crop`, `Reduce`, `TBinarizationSimple`, `UMatrix*`, `UCR*`, `VideoSimulator*`, `RotCameraSimulator`, `BStatisticSimple`, `UMD*Mux`.
