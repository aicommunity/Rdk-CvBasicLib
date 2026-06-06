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
- ✅ **Rdk-CvBasicLib-Overview.md** — расширенный обзор (RU-only; нет `## EN`)
- ✅ **Architecture.md** — архитектура пайплайнов и UBA-компонентов (RU/EN)
- ✅ **API-Overview.md** — обзор API (RU/EN)
- ✅ **Usage-Examples.md** — примеры (RU/EN)
- ✅ **FAQ.md** — FAQ (RU/EN)
- ✅ **Component-Catalog.md** — каталог с группировкой (RU-only)
- ✅ **Diagrams/** — Image-Processing-Pipeline, Object-Detection-Flow (RU/EN)

### Компоненты с per-class документацией
- ✅ **ColorConvert** — [`Components/ColorConvert.md`](Components/ColorConvert.md)

### Групповые документы (тематическое покрытие, RU-only)
- ⚠ [`CaptureAndSources.md`](Components/CaptureAndSources.md) — источники и захват
- ⚠ [`BackgroundBinarizationLabeling.md`](Components/BackgroundBinarizationLabeling.md) — фон, бинаризация, маркировка
- ⚠ [`GeometricTransformations.md`](Components/GeometricTransformations.md) — геометрические преобразования
- ⚠ [`CropReduce.md`](Components/CropReduce.md) — обрезка и редукция
- ⚠ [`MatrixMathMux.md`](Components/MatrixMathMux.md) — матричная математика и мультиплексоры
- ⚠ [`PipelinesModelsStats.md`](Components/PipelinesModelsStats.md) — пайплайны, модели, статистика
- ⚠ [`UCRFamily.md`](Components/UCRFamily.md) — классификаторы UCR*
- ⚠ [`DetectorsSegmentators.md`](Components/DetectorsSegmentators.md) — детекторы, сегментаторы, savers
- ⚠ [`MovingDetectors.md`](Components/MovingDetectors.md) — детекторы движения
- ⚠ [`ReceiverAndShowRect.md`](Components/ReceiverAndShowRect.md) — приёмник и визуализация
- ⚠ [`VideoSimulators.md`](Components/VideoSimulators.md) — симуляторы видео/камеры

### Orphan docs (ожидаемые групповые)
Все 11 файлов в `Components/` — групповые; per-class файлы по имени `UploadClass` отсутствуют (кроме `ColorConvert`).

---

## Планируется / рекомендации

### Приоритет P0 — per-class документация
- [ ] Создать **Component-Documentation-Template.md** (UML, свойства, методы, RU/EN)
- [ ] Разбить групповые docs на per-class страницы или добавить якоря `#ClassName` с полными таблицами свойств для каждого из **55** недостающих классов
- [ ] Обновить **Component-Catalog.md** — явная строка на каждый `UploadClass` (**50** сейчас отсутствуют)

### Приоритет P1 — bilingual parity
- [ ] Добавить `## EN` во все **12** файлов `Components/*.md` (сейчас RU-only)
- [ ] Добавить `## EN` в **Component-Catalog.md** и **Rdk-CvBasicLib-Overview.md**

### Приоритет P2 — синхронизация с кодом и конфигами
- [ ] Сверить свойства с `Core/Basic.cpp` и заголовками `Core/*.h`
- [ ] Добавить ссылки на `Bin/Configs/` для часто используемых компонентов (`ColorConvert`, `Crop`, `Reduce`, `TBinarizationSimple`, `UCR*`, `VideoSimulator*`)
- [ ] Согласовать имена в каталоге с реальными `ClassName` (например `Pipeline` vs `UBPipeline` в тексте каталога)

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

**Итого:** 1 ✅, 55 ❌ (per-class); 11 групповых docs дают обзорное покрытие без таблиц свойств по классу.

---

## Чеклист синхронизации с кодом

При добавлении или изменении класса в `Libraries/Rdk-CvBasicLib/Core/` рекомендуется обновить:

1. **Component-Catalog.md** — при регистрации нового `UploadClass` в `Basic.cpp`
2. **Docs/Components/[ComponentName].md** — создать per-class страницу или расширить групповой doc
3. **API-Overview.md** — при изменении публичного API (`ColorConvert`, `Pipeline`, `UCR*`, `UMatrix*`)
4. **Usage-Examples.md** — при появлении новых CV-сценариев
5. **Architecture.md** / **Diagrams/** — при изменении пайплайнов обработки
6. **Rdk-CvBasicLib-Overview.md** — при добавлении новых категорий компонентов
7. Перезапустить аудит: `Scripts/doc-audit/run-all.sh`

---

## EN

### Documentation status summary

Rdk-CvBasicLib has **56** registered classes and **12** group component docs. Only **ColorConvert** has a per-class markdown file matching `UploadClass`. **55** classes lack dedicated documentation; **50** are missing from Component-Catalog.

**Progress:** 1/56 per-class (2%); 12/56 with group overview (21%).

### Priority actions

1. Create per-class pages (or anchored sections) for all 55 missing classes
2. Add `## EN` sections to all component docs and Component-Catalog
3. Introduce Component-Documentation-Template.md aligned with MotionControlLib/PulseLib

### Sync checklist (code changes)

When changing `Core/Basic.cpp` or headers: update Component-Catalog, component docs, API-Overview, Usage-Examples; re-run doc audit.

---

*Источники: [Component-Gap-Report.md](../../../Docs/Audit/Component-Gap-Report.md), [Code-Inventory.json](../../../Docs/Audit/Code-Inventory.json); шаблон — [Nmsdk-MotionControlLib/Docs/Documentation-Status.md](../../Nmsdk-MotionControlLib/Docs/Documentation-Status.md).*
