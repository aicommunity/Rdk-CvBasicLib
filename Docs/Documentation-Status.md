# Статус документации Rdk-CvBasicLib

## RU

Краткий статус документации библиотеки Rdk-CvBasicLib и чеклист синхронизации с кодом.

**Аудит:** 2026-06-06 — [Component-Gap-Report.md](../../../Docs/Audit/Component-Gap-Report.md), [Code-Inventory.json](../../../Docs/Audit/Code-Inventory.json)  
**Обновление Track 3:** 2026-07-27 — сгенерированы per-class страницы для всех `UploadClass`; добавлен пропущенный `TCaptureImageSequence` (57/57).

---

## Статистика (сверка с кодом)

| Метрика | Значение |
|---------|----------|
| Зарегистрированных классов (`UploadClass`) | **57** |
| Файлов `Docs/Components/*.md` | **68** (57 per-class + 11 групповых) |
| Классов с doc-файлом по имени класса | **57** |
| Классов без отдельного doc-файла | **0** |
| Orphan/group docs | **11** (тематические обзоры; `MovingDetectors` — без UploadClass в `Basic.cpp`) |
| Отсутствуют в Component-Catalog | **0** |
| Регистрация | `Core/Basic.cpp` |

**Прогресс по классам:** 57/57 (100%) ✅ — per-class; групповые документы сохранены как обзоры.

---

## Выполнено

### Общая документация
- ✅ **README.md** — обзор CV-библиотеки, быстрый старт (RU/EN)
- ✅ **Rdk-CvBasicLib-Overview.md** — расширенный обзор
- ✅ **Architecture.md** — архитектура пайплайнов и UBA-компонентов (RU/EN)
- ✅ **API-Overview.md** — обзор API (RU/EN)
- ✅ **Usage-Examples.md** — примеры (RU/EN)
- ✅ **FAQ.md** — FAQ (RU/EN)
- ✅ **Component-Catalog.md** — каталог всех 57 `UploadClass` (RU/EN)
- ✅ **Component-Documentation-Template.md** — шаблон per-class страницы
- ✅ **Diagrams/** — Image-Processing-Pipeline, Object-Detection-Flow (RU/EN)

### Компоненты
- ✅ **57** per-class файлов `Docs/Components/[ClassName].md` (включая `TCaptureImageSequence`, `ColorConvert` и все UCR*/UBA*/sources/simulators/math/pipelines)
- ✅ **11** групповых обзоров: CaptureAndSources, BackgroundBinarizationLabeling, GeometricTransformations, CropReduce, MatrixMathMux, PipelinesModelsStats, UCRFamily, DetectorsSegmentators, MovingDetectors, ReceiverAndShowRect, VideoSimulators

---

## Планируется / рекомендации

### Приоритет P1 — качество stub-страниц
- [ ] Расширить per-class stubs полными таблицами `UProperty` из `Core/*.h`
- [ ] Добавить ссылки на `Bin/Configs/` для часто используемых компонентов
- [ ] Довести bilingual parity на групповых docs при необходимости

### Приоритет P2 — синхронизация
- [ ] Сверять свойства с `Core/Basic.cpp` при изменении регистрации
- [ ] Перезапускать `Scripts/doc-audit/run-all.sh` после массовых правок docs

---

## Чеклист по классам (`UploadClass`)

Регистрация: `Libraries/Rdk-CvBasicLib/Core/Basic.cpp`.

Все **57** классов имеют per-class doc и строку в [Component-Catalog.md](Component-Catalog.md). Групповые docs остаются как тематические обзоры.

| Группа | Примеры ClassName | Per-class | Статус |
|--------|-------------------|-----------|--------|
| Capture / Sources | `Source`, `SourceFile`, `BitmapSource*`, … | ✅ | ✅ |
| Image processing | `ColorConvert`, `Crop`, `TBinarization*`, `UBA*`, … | ✅ | ✅ |
| Simulators | `VideoSimulator*`, `DataSimulatorSimple`, … | ✅ | ✅ |
| Math / Matrix | `UMatrix*Math`, `UMD*Mux`, `BMathOperator` | ✅ | ✅ |
| Pipelines / Models | `Pipeline`, `ParallelPipeline`, `Model`, `BStatisticSimple` | ✅ | ✅ |
| Classification / Detection | `UCR*`, `UClassifier*`, `UDetector*`, `USegmentator*` | ✅ | ✅ |

**Итого:** 56 ✅ per-class; 11 групповых docs.

---

## EN

Brief documentation status for the Rdk-CvBasicLib library and a code-sync checklist.

**Audit:** 2026-06-06 — [Component-Gap-Report.md](../../../Docs/Audit/Component-Gap-Report.md), [Code-Inventory.json](../../../Docs/Audit/Code-Inventory.json)  
**Track 3 update:** 2026-07-27 — generated per-class pages for all `UploadClass`; added missing `TCaptureImageSequence` (57/57).

---

## Statistics (code cross-check)

| Metric | Value |
|--------|-------|
| Registered classes (`UploadClass`) | **57** |
| Files `Docs/Components/*.md` | **68** (57 per-class + 11 group) |
| Classes with per-class doc file | **57** |
| Classes without a dedicated doc file | **0** |
| Orphan/group docs | **11** (thematic overviews; `MovingDetectors` has no UploadClass in `Basic.cpp`) |
| Missing from Component-Catalog | **0** |
| Registration | `Core/Basic.cpp` |

**Class progress:** 57/57 (100%) ✅ — per-class; group documents retained as overviews.

---

## Completed

### General documentation
- ✅ **README.md**, **Architecture.md**, **API-Overview.md**, **Usage-Examples.md**, **FAQ.md** (RU/EN)
- ✅ **Component-Catalog.md** — all 57 `UploadClass` (RU/EN)
- ✅ **Component-Documentation-Template.md**
- ✅ **Diagrams/**

### Components
- ✅ **57** per-class `Docs/Components/[ClassName].md` pages (includes `TCaptureImageSequence`)
- ✅ **11** thematic group docs retained

---

## Planned / recommendations

### Priority P1 — stub quality
- [ ] Expand stubs with full `UProperty` tables from `Core/*.h`
- [ ] Add `Bin/Configs/` usage links for frequently used components

### Priority P2 — sync
- [ ] Keep catalog and docs aligned with `Core/Basic.cpp`; re-run doc audit after bulk doc edits

---

## Class checklist (`UploadClass`)

All **57** classes have a per-class doc and a row in [Component-Catalog.md](Component-Catalog.md). See the RU section table for group coverage.

**Total:** 57 ✅ per-class; 11 group docs.

---
