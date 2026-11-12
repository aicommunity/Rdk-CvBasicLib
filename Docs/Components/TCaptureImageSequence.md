# TCaptureImageSequence

## RU

**Класс**: `TCaptureImageSequence` — захват последовательности изображений из файлов (каталог/маска пути).
**Регистрация**: `Core/Basic.cpp` → `UploadClass<TCaptureImageSequence>("TCaptureImageSequence","Capture")`.
**Базовый класс**: `TCapture`.
**Групповой документ**: [`CaptureAndSources.md`](CaptureAndSources.md)

### Ключевые свойства

| Свойство | Тип | Флаги | Назначение |
|----------|-----|-------|------------|
| `Path` | string | parameter | Путь к каталогу/шаблону файлов |
| `IsPathRelativeFromConfig` | bool | parameter | Относительный путь от конфига |
| `RepeatFlag` | bool | parameter | Циклический повтор последовательности |
| `CaptureDelay` | int | parameter | Задержка между кадрами |
| `NumImages` | int | state | Число кадров |
| `CurrentImageIndex` | int | state | Текущий индекс |
| `CurrentImageFileName` | string | state | Имя текущего файла |

Сверяйте полный набор с `Core/TCaptureImageSequence.h` и базовым `TCapture`.

### Каталог

[Component-Catalog.md](../Component-Catalog.md)

---

### Ключевые свойства / Favorites

| Свойство | Роль |
|----------|------|
| `Path` / `IsPathRelativeFromConfig` | Каталог кадров |
| `EnableCapture` / `RepeatFlag` / `CaptureDelay` | Захват |
| `DesiredFps` / `DesiredWidth` / `DesiredHeight` | Параметры потока |
| `NumImages` / `CurrentImageIndex` | Состояние последовательности |

ClDesc: `Bin/ClDesc/CvBasicLib/ru-RU/TCaptureImageSequence.xml` (уже мог иметь таблицу свойств — Favorites синхронизированы).

## EN

**Class**: `TCaptureImageSequence` — capture an image sequence from files (directory/path pattern).
**Registration**: `Core/Basic.cpp` → `UploadClass<TCaptureImageSequence>("TCaptureImageSequence","Capture")`.
**Base class**: `TCapture`.
**Group doc**: [`CaptureAndSources.md`](CaptureAndSources.md)

### Key properties

| Property | Type | Flags | Purpose |
|----------|------|-------|---------|
| `Path` | string | parameter | Directory / file pattern path |
| `IsPathRelativeFromConfig` | bool | parameter | Path relative to config |
| `RepeatFlag` | bool | parameter | Loop the sequence |
| `CaptureDelay` | int | parameter | Delay between frames |
| `NumImages` | int | state | Frame count |
| `CurrentImageIndex` | int | state | Current index |
| `CurrentImageFileName` | string | state | Current file name |

Keep tables synced with `Core/TCaptureImageSequence.h` and base `TCapture`.

### Catalog

[Component-Catalog.md](../Component-Catalog.md)
