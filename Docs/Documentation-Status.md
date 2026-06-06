# Статус документации Rdk-CvBasicLib

## RU

Краткий статус документации библиотеки Rdk-CvBasicLib и чеклист синхронизации с кодом.

**Аудит:** 2026-06-06 — [Component-Gap-Report.md](../../../Docs/Audit/Component-Gap-Report.md), [Code-Inventory.json](../../../Docs/Audit/Code-Inventory.json)

---

## Статистика (сверка с кодом)

| Метрика | Значение |
|---------|----------|
| Зарегистрированных классов (`UploadClass`) | **56** |
| Файлов `Docs/Components/*.md` | **12** |
| Классов с doc-файлом по имени класса | **1** (`ColorConvert`) |
| Классов без отдельного doc-файла | **55** |
| Orphan docs (групповые) | **11** |
| Отсутствуют в Component-Catalog | **50** |
| Регистрация | `Core/Basic.cpp` |

**Прогресс по классам:** 1/56 (2%) — per-class; 12/56 (21%) — групповое покрытие через тематические документы.

---

## Выполнено

### Общая документация
- ✅ **README.md** — обзор CV-библиотеки, быстрый старт (RU/EN)
- ✅ **Rdk-CvBasicLib-Overview.md** — расширенный обзор (RU-only; нет `## EN

`)
- ✅ **Architecture.md** — архитектура пайплайнов и UBA-компонентов (RU/EN)
- ✅ **API-Overview.md** — обзор API (RU/EN)
- ✅ **Usage-Examples.md** — примеры (RU/EN)
- ✅ **FAQ.md** — FAQ (RU/EN)
- ✅ **Component-Catalog.md** — каталог с группировкой (RU-only)
- ✅ **Diagrams/** — Image-Processing-Pipeline, Object-Detection-Flow (RU/EN)

### Компоненты с per-class документацией
- ✅ **ColorConvert** — [`Components/ColorConvert.md`](Components/ColorConvert.md)

### Групповые документы (тематическое покрытие, RU-only)
- ⚠ [`CaptureAndSources.md`](Components/CaptureAndSources.md) — sources и capture
- ⚠ [`BackgroundBinarizationLabeling.md`](Components/BackgroundBinarizationLabeling.md) — фон, binarization, маркировка
- ⚠ [`GeometricTransformations.md`](Components/GeometricTransformations.md) — geometric transformations
- ⚠ [`CropReduce.md`](Components/CropReduce.md) — обрезка и редукция
- ⚠ [`MatrixMathMux.md`](Components/MatrixMathMux.md) — матричная математика и мультиплексоры
- ⚠ [`PipelinesModelsStats.md`](Components/PipelinesModelsStats.md) — pipelines, models, statistics
- ⚠ [`UCRFamily.md`](Components/UCRFamily.md) — классификаторы UCR*
- ⚠ [`DetectorsSegmentators.md`](Components/DetectorsSegmentators.md) — detectors, сегментаторы, savers
- ⚠ [`MovingDetectors.md`](Components/MovingDetectors.md) — motion detectors
- ⚠ [`ReceiverAndShowRect.md`](Components/ReceiverAndShowRect.md) — receiver и visualization
- ⚠ [`VideoSimulators.md`](Components/VideoSimulators.md) — симуляторы видео/камеры

### Orphan docs (ожидаемые групповые)
Все 11 файлов в `Components/` — групповые; per-class файлы по имени `UploadClass` отсутствуют (кроме `ColorConvert`).

---

## Планируется / рекомендации

### Приоритет P0 — per-class documentation
- [ ] Создать **Component-Documentation-Template.md** (UML, свойства, методы, RU/EN)
- [ ] Разбить групповые docs на per-class страницы или добавить якоря `#ClassName` с полными таблицами свойств для каждого из **55** недостающих classes
- [ ] Обновить **Component-Catalog.md** — явная строка на каждый `UploadClass` (**50** сейчас отсутствуют)

### Приоритет P1 — bilingual parity
- [ ] Добавить `## EN` во все **12** файлов `Components/*.md` (сейчас RU-only)
- [ ] Добавить `## EN` в **Component-Catalog.md** и **Rdk-CvBasicLib-Overview.md**

### Приоритет P2 — синхронизация с кодом и конфигами
- [ ] Сверить свойства с `Core/Basic.cpp` и заголовками `Core/*.h`
- [ ] Добавить ссылки на `Bin/Configs/` для часто используемых компонентов (`ColorConvert`, `Crop`, `Reduce`, `TBinarizationSimple`, `UCR*`, `VideoSimulator*`)
- [ ] Согласовать имена в каталоге с реальными `ClassName` (for example `Pipeline` vs `UBPipeline` в тексте каталога)

---

## Чеклист по классам (`UploadClass`)

Регистрация: `Libraries/Rdk-CvBasicLib/Core/Basic.cpp`.

### Capture / Sources
| ClassName | Групповой doc | Per-class | Статус |
|-----------|---------------|-----------|--------|
| `BitmapSourceFile` | CaptureAndSources | — | ❌ |
| `BitmapSourceSimple` | CaptureAndSources | — | ❌ |
| `Receiver` | ReceiverAndShowRect | — | ❌ |
| `Source` | CaptureAndSources | — | ❌ |
| `SourceFile` | CaptureAndSources | — | ❌ |
| `SourceMultiFile` | CaptureAndSources | — | ❌ |

### Image processing (UBA*)
| ClassName | Групповой doc | Per-class | Статус |
|-----------|---------------|-----------|--------|
| `BackgroundAvg` | BackgroundBinarizationLabeling | — | ❌ |
| `BackgroundExponnential` | BackgroundBinarizationLabeling | — | ❌ |
| `BackgroundSimpleAdaptive` | BackgroundBinarizationLabeling | — | ❌ |
| `ColorConvert` | — | ColorConvert.md | ✅ |
| `Crop` | CropReduce | — | ❌ |
| `DeltaBackgroundExponnential` | BackgroundBinarizationLabeling | — | ❌ |
| `DifferenceFrameSimple` | BackgroundBinarizationLabeling | — | ❌ |
| `Reduce` | CropReduce | — | ❌ |
| `ResizeEdges` | GeometricTransformations | — | ❌ |
| `RotateSimple` | GeometricTransformations | — | ❌ |
| `TBinarizationSimple` | BackgroundBinarizationLabeling | — | ❌ |
| `TBinarizationSimpleAdaptiveThreshold` | BackgroundBinarizationLabeling | — | ❌ |
| `TLabelingSimple` | BackgroundBinarizationLabeling | — | ❌ |
| `UBABackgroundDependDiff` | BackgroundBinarizationLabeling | — | ❌ |
| `UBABinarizationOtsu` | BackgroundBinarizationLabeling | — | ❌ |
| `UBAFlipImageSimple` | GeometricTransformations | — | ❌ |
| `UBShowRect` | ReceiverAndShowRect | — | ❌ |
| `ShowObjectsSimple` | DetectorsSegmentators | — | ❌ |

### Simulators
| ClassName | Групповой doc | Per-class | Статус |
|-----------|---------------|-----------|--------|
| `DataSimulatorSimple` | VideoSimulators | — | ❌ |
| `RotCameraSimulator` | VideoSimulators | — | ❌ |
| `Video3DSimulatorSimple` | VideoSimulators | — | ❌ |
| `VideoSimulatorSimple` | VideoSimulators | — | ❌ |
| `VideoSimulatorSimpleBin` | VideoSimulators | — | ❌ |

### Math / Matrix
| ClassName | Групповой doc | Per-class | Статус |
|-----------|---------------|-----------|--------|
| `BMathOperator` | MatrixMathMux | — | ❌ |
| `BStatisticSimple` | PipelinesModelsStats | — | ❌ |
| `UMatrixDoubleMath` | MatrixMathMux | — | ❌ |
| `UMatrixIntMath` | MatrixMathMux | — | ❌ |
| `UMDMatrixDoubleMux` | MatrixMathMux | — | ❌ |
| `UMDMatrixIntMux` | MatrixMathMux | — | ❌ |
| `UMDScalarDoubleMux` | MatrixMathMux | — | ❌ |
| `UMDScalarIntMux` | MatrixMathMux | — | ❌ |

### Pipelines / Models
| ClassName | Групповой doc | Per-class | Статус |
|-----------|---------------|-----------|--------|
| `Model` | PipelinesModelsStats | — | ❌ |
| `ParallelPipeline` | PipelinesModelsStats | — | ❌ |
| `Pipeline` | PipelinesModelsStats | — | ❌ |

### Classification / Detection / Segmentation
| ClassName | Групповой doc | Per-class | Статус |
|-----------|---------------|-----------|--------|
| `UCRBarnesHutTSNE` | UCRFamily | — | ❌ |
| `UCRConvolutionNetwork` | UCRFamily | — | ❌ |
| `UCRDirectCompare` | UCRFamily | — | ❌ |
| `UCRDistance` | UCRFamily | — | ❌ |
| `UCRFusion` | UCRFamily | — | ❌ |
| `UCRPerseptron` | UCRFamily | — | ❌ |
| `UCRPrincipalComponentAnalysis` | UCRFamily | — | ❌ |
| `UCRSample` | UCRFamily | — | ❌ |
| `UCRTeacherCVNetworkBP` | UCRFamily | — | ❌ |
| `UCRTeacherPerseptronBP` | UCRFamily | — | ❌ |
| `UCRTeacherPerseptronDL` | UCRFamily | — | ❌ |
| `UClassifierBase` | DetectorsSegmentators | — | ❌ |
| `UClassifierResSaver` | DetectorsSegmentators | — | ❌ |
| `UDetResSaverPVOC` | DetectorsSegmentators | — | ❌ |
| `UDetectorBase` | DetectorsSegmentators | — | ❌ |
| `USegmentatorBase` | DetectorsSegmentators | — | ❌ |

**Итого:** 1 ✅, 55 ❌ (per-class); 11 групповых docs дают обзорное покрытие без таблиц properties по классу.

---

## EN

Brief documentation status for the Rdk-CvBasicLib library and a code-sync checklist.

**Audit:** 2026-06-06 — [Component-Gap-Report.md](../../../Docs/Audit/Component-Gap-Report.md), [Code-Inventory.json](../../../Docs/Audit/Code-Inventory.json)

---

## Statistics (code cross-check)

| Metric | Value |
|--------|-------|
| Registered classes (`UploadClass`) | **56** |
| Files `Docs/Components/*.md` | **12** |
| Classes with per-class doc file | **1** (`ColorConvert`) |
| Classes without a dedicated doc file | **55** |
| Orphan docs (group docs) | **11** |
| Missing from Component-Catalog | **50** |
| Registration | `Core/Basic.cpp` |

**Class progress:** 1/56 (2%) — per-class; 12/56 (21%) — group coverage via thematic documents.

---

## Completed

### General documentation
- ✅ **README.md** — CV library overview, quick start (RU/EN)
- ✅ **Rdk-CvBasicLib-Overview.md** — extended overview (RU-only; no `## EN`)
- ✅ **Architecture.md** — pipeline and UBA component architecture (RU/EN)
- ✅ **API-Overview.md** — API overview (RU/EN)
- ✅ **Usage-Examples.md** — examples (RU/EN)
- ✅ **FAQ.md** — FAQ (RU/EN)
- ✅ **Component-Catalog.md** — catalog with grouping (RU-only)
- ✅ **Diagrams/** — Image-Processing-Pipeline, Object-Detection-Flow (RU/EN)

### Components with per-class documentation
- ✅ **ColorConvert** — [`Components/ColorConvert.md`](Components/ColorConvert.md)

### Group documents (thematic coverage, RU-only)
- ⚠ [`CaptureAndSources.md`](Components/CaptureAndSources.md) — sources and capture
- ⚠ [`BackgroundBinarizationLabeling.md`](Components/BackgroundBinarizationLabeling.md) — background, binarization, labeling
- ⚠ [`GeometricTransformations.md`](Components/GeometricTransformations.md) — geometric transformations
- ⚠ [`CropReduce.md`](Components/CropReduce.md) — crop and reduce
- ⚠ [`MatrixMathMux.md`](Components/MatrixMathMux.md) — matrix math and multiplexers
- ⚠ [`PipelinesModelsStats.md`](Components/PipelinesModelsStats.md) — pipelines, models, statistics
- ⚠ [`UCRFamily.md`](Components/UCRFamily.md) — UCR* classifiers
- ⚠ [`DetectorsSegmentators.md`](Components/DetectorsSegmentators.md) — detectors, segmentators, savers
- ⚠ [`MovingDetectors.md`](Components/MovingDetectors.md) — motion detectors
- ⚠ [`ReceiverAndShowRect.md`](Components/ReceiverAndShowRect.md) — receiver and visualization
- ⚠ [`VideoSimulators.md`](Components/VideoSimulators.md) — video/camera simulators

### Orphan docs (expected group docs)
All 11 files in `Components/` are group docs; per-class files by `UploadClass` name are missing (except `ColorConvert`).

---

## Planned / recommendations

### Priority P0 — per-class documentation
- [ ] Create **Component-Documentation-Template.md** (UML, properties, methods, RU/EN)
- [ ] Split group docs into per-class pages or add `#ClassName` anchors with full property tables for each of the **55** missing classes
- [ ] Update **Component-Catalog.md** — explicit row for every `UploadClass` (**50** currently missing)

### Priority P1 — bilingual parity
- [ ] Add `## EN` to all **12** `Components/*.md` files (currently RU-only)
- [ ] Add `## EN` to **Component-Catalog.md** and **Rdk-CvBasicLib-Overview.md**

### Priority P2 — code and config sync
- [ ] Verify properties against `Core/Basic.cpp` and `Core/*.h` headers
- [ ] Add links to `Bin/Configs/` for frequently used components (`ColorConvert`, `Crop`, `Reduce`, `TBinarizationSimple`, `UCR*`, `VideoSimulator*`)
- [ ] Align catalog names with real `ClassName` values (for example `Pipeline` vs `UBPipeline` in catalog text)

---

## Class checklist (`UploadClass`)

Registration: `Libraries/Rdk-CvBasicLib/Core/Basic.cpp`.

### Capture / Sources
| ClassName | Group doc | Per-class | Status |
|-----------|-----------|-----------|--------|
| `BitmapSourceFile` | CaptureAndSources | — | ❌ |
| `BitmapSourceSimple` | CaptureAndSources | — | ❌ |
| `Receiver` | ReceiverAndShowRect | — | ❌ |
| `Source` | CaptureAndSources | — | ❌ |
| `SourceFile` | CaptureAndSources | — | ❌ |
| `SourceMultiFile` | CaptureAndSources | — | ❌ |

### Image processing (UBA*)
| ClassName | Group doc | Per-class | Status |
|-----------|-----------|-----------|--------|
| `BackgroundAvg` | BackgroundBinarizationLabeling | — | ❌ |
| `BackgroundExponnential` | BackgroundBinarizationLabeling | — | ❌ |
| `BackgroundSimpleAdaptive` | BackgroundBinarizationLabeling | — | ❌ |
| `ColorConvert` | — | ColorConvert.md | ✅ |
| `Crop` | CropReduce | — | ❌ |
| `DeltaBackgroundExponnential` | BackgroundBinarizationLabeling | — | ❌ |
| `DifferenceFrameSimple` | BackgroundBinarizationLabeling | — | ❌ |
| `Reduce` | CropReduce | — | ❌ |
| `ResizeEdges` | GeometricTransformations | — | ❌ |
| `RotateSimple` | GeometricTransformations | — | ❌ |
| `TBinarizationSimple` | BackgroundBinarizationLabeling | — | ❌ |
| `TBinarizationSimpleAdaptiveThreshold` | BackgroundBinarizationLabeling | — | ❌ |
| `TLabelingSimple` | BackgroundBinarizationLabeling | — | ❌ |
| `UBABackgroundDependDiff` | BackgroundBinarizationLabeling | — | ❌ |
| `UBABinarizationOtsu` | BackgroundBinarizationLabeling | — | ❌ |
| `UBAFlipImageSimple` | GeometricTransformations | — | ❌ |
| `UBShowRect` | ReceiverAndShowRect | — | ❌ |
| `ShowObjectsSimple` | DetectorsSegmentators | — | ❌ |

### Simulators
| ClassName | Group doc | Per-class | Status |
|-----------|-----------|-----------|--------|
| `DataSimulatorSimple` | VideoSimulators | — | ❌ |
| `RotCameraSimulator` | VideoSimulators | — | ❌ |
| `Video3DSimulatorSimple` | VideoSimulators | — | ❌ |
| `VideoSimulatorSimple` | VideoSimulators | — | ❌ |
| `VideoSimulatorSimpleBin` | VideoSimulators | — | ❌ |

### Math / Matrix
| ClassName | Group doc | Per-class | Status |
|-----------|-----------|-----------|--------|
| `BMathOperator` | MatrixMathMux | — | ❌ |
| `BStatisticSimple` | PipelinesModelsStats | — | ❌ |
| `UMatrixDoubleMath` | MatrixMathMux | — | ❌ |
| `UMatrixIntMath` | MatrixMathMux | — | ❌ |
| `UMDMatrixDoubleMux` | MatrixMathMux | — | ❌ |
| `UMDMatrixIntMux` | MatrixMathMux | — | ❌ |
| `UMDScalarDoubleMux` | MatrixMathMux | — | ❌ |
| `UMDScalarIntMux` | MatrixMathMux | — | ❌ |

### Pipelines / Models
| ClassName | Group doc | Per-class | Status |
|-----------|-----------|-----------|--------|
| `Model` | PipelinesModelsStats | — | ❌ |
| `ParallelPipeline` | PipelinesModelsStats | — | ❌ |
| `Pipeline` | PipelinesModelsStats | — | ❌ |

### Classification / Detection / Segmentation
| ClassName | Group doc | Per-class | Status |
|-----------|-----------|-----------|--------|
| `UCRBarnesHutTSNE` | UCRFamily | — | ❌ |
| `UCRConvolutionNetwork` | UCRFamily | — | ❌ |
| `UCRDirectCompare` | UCRFamily | — | ❌ |
| `UCRDistance` | UCRFamily | — | ❌ |
| `UCRFusion` | UCRFamily | — | ❌ |
| `UCRPerseptron` | UCRFamily | — | ❌ |
| `UCRPrincipalComponentAnalysis` | UCRFamily | — | ❌ |
| `UCRSample` | UCRFamily | — | ❌ |
| `UCRTeacherCVNetworkBP` | UCRFamily | — | ❌ |
| `UCRTeacherPerseptronBP` | UCRFamily | — | ❌ |
| `UCRTeacherPerseptronDL` | UCRFamily | — | ❌ |
| `UClassifierBase` | DetectorsSegmentators | — | ❌ |
| `UClassifierResSaver` | DetectorsSegmentators | — | ❌ |
| `UDetResSaverPVOC` | DetectorsSegmentators | — | ❌ |
| `UDetectorBase` | DetectorsSegmentators | — | ❌ |
| `USegmentatorBase` | DetectorsSegmentators | — | ❌ |

**Total:** 1 ✅, 55 ❌ (per-class); 11 group docs provide overview coverage without per-class property tables.

---
