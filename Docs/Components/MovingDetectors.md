## RU

## Moving Detectors — детекторы движения (Rdk-CvBasicLib)

### Назначение

Компоненты `UBAMovingDetector*` и `UBAObjectDetector*` реализуют алгоритмы детекции движущихся объектов и базовые интерфейсы детекции объектов. Используются в пайплайнах видеонаблюдения и анализа движения.

---

## EN

### UML-диаграмма классов

```mermaid
classDiagram
    UNet <|-- UBAMovingDetector
    UBAMovingDetector <|-- UBANightMovingDetector
    UBAMovingDetector <|-- UBACollateMovingDetector

    class UBAObjectDetector {
        <<interface>>
        +Calculate(UBitmap&,Rect*) bool
        +operator()(UBitmap&,Rect*) bool
    }

    class UBANightDetector {
        +HistorySize : int
        +BlockWidth : int
        +BlockHeight : int
        +AdaptiveThresholdPercent : double
        +MoveDetectionPercent : double
        +T1 : double
        +Tr : double
        +Calculate(UBitmap&,Rect*) bool
    }

    class UBAMovingDetector {
        +HistorySize : int
        +Input : UBitmap
        -MovedObjects : UBRect*
        -LocalContrastedImages : UBitmap*
        -CurrentHistorySize : int
        -CurrentFirstHistoryIndex : int
        +GetHistorySize() int
        +SetHistorySize(int) bool
        +GetInputData() const UBitmap*
        +GetMovedObjects() const UBRect*
        +GetLocalContrastedImages() const UBitmap*
        +GetCurrentHistorySize() int
        +GetCurrentFirstHistoryIndex() int
        +HistoryShift() void
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBANightMovingDetector {
        +BlockWidth : int
        +BlockHeight : int
        +AdaptiveThresholdPercent : double
        +MoveDetectionPercent : double
        +T1 : double
        +Tr : double
        +MovingDetectionMode : int
        +HistLeftRange : int
        +HistRightRange : int
        +MovingFrameMode : int
        +GetMovedImage() const UBitmap&
        +GetNumBlocks() int
        +GetCL() const double*
        +GetML() const double*
        +GetSigmaL() const double*
        +GetDiffImage() const UBitmap&
        +GetHistogram() const UBHistogram&
        +GetContrastGrid() const UBRect*
        +GetMovedGrid() const UBRect*
        +New() UBANightMovingDetector*
        +CalcLocalContrasting() bool
        +CalcLocalMap() bool
        +CalcMovedObjects() bool
        +CalcNormalMovedObjects() bool
        +CalcAdaptiveThreshold() bool
        +AFCDefault() bool
        +AFCBuild() bool
        +AFCReset() bool
        +AFCCalculate() bool
    }

    class UBACollateMovingDetector {
        +DiffImage : UBitmap
        +New() UBACollateMovingDetector*
        +AFCDefault() bool
        +AFCBuild() bool
        +AFCReset() bool
        +AFCCalculate() bool
    }
```

---

### UBAMovingDetector — базовый детектор движения

#### UML-диаграмма последовательности

```mermaid
sequenceDiagram
    participant Src as Source/Background
    participant Det as UBAMovingDetector*
    participant Hist as HistoryBuffer
    participant Next as Labeling/ShowObjects

    loop каждый кадр
        Src-->>Det: Input (UBitmap)
        Det->>Det: ACalculate() / AFCCalculate()
        Det->>Hist: Обновление истории кадров
        Det->>Det: Вычисление разности/контраста
        Det->>Det: Обнаружение движущихся объектов
        Det-->>Next: MovedObjects (UBRect*)
    end
```

#### UML-диаграмма состояний

```mermaid
stateDiagram-v2
    [*] --> Uninitialized: New()
    Uninitialized --> Defaulted: ADefault()
    Defaulted --> Built: ABuild()
    Built --> Ready: Ready = true
    Ready --> CollectingHistory: ACalculate() (первые HistorySize кадров)
    CollectingHistory --> Ready: История заполнена
    Ready --> Detecting: ACalculate() (детекция движения)
    Detecting --> Ready: Кадр обработан
    Ready --> Resetting: AReset()
    Resetting --> Ready: История очищена
```

#### UML-диаграмма активности (UBANightMovingDetector::AFCCalculate)

```mermaid
flowchart TD
    Start([Start]) --> ReadInput[Прочитать Input]
    ReadInput --> ShiftHistory["HistoryShift()<br/>обновление буфера истории"]
    ShiftHistory --> CalcLocalContrast["CalcLocalContrasting()<br/>вычисление локального контраста"]
    CalcLocalContrast --> CalcLocalMap["CalcLocalMap()<br/>построение карты локальной зависимости"]
    CalcLocalMap --> CalcMoved["CalcMovedObjects()<br/>обнаружение движущихся объектов"]
    CalcMoved --> CalcAdaptive["CalcAdaptiveThreshold()<br/>расчёт адаптивного порога"]
    CalcAdaptive --> FillOutput["Заполнить MovedObjects<br/>и MovedImage"]
    FillOutput --> End([End])
```

#### Свойства и методы

| Свойство/Метод | Тип | Назначение |
|----------------|-----|------------|
| `HistorySize` | `int` | Размер истории кадров для анализа движения |
| `Input` | `UBitmap` | Входное изображение |
| `MovedObjects` | `UBRect*` | Массив обнаруженных движущихся объектов (защищённое поле) |
| `LocalContrastedImages` | `UBitmap*` | Буфер изображений с локальным контрастом |
| `GetMovedObjects()` | `const UBRect*` | Получить массив обнаруженных объектов |
| `HistoryShift()` | `void` | Сдвиг буфера истории |

---

### UBANightMovingDetector — детектор движения для ночных условий

#### Алгоритм

Реализует алгоритм из статьи "A real-time object detecting and tracking system for outdoor night surveillance" (Kaiqi Huang et al.):

1. **Локальный контраст** — вычисление контраста в блоках изображения.
2. **Карта локальной зависимости** — построение карты изменений между кадрами.
3. **Адаптивный порог** — динамический порог для выделения движущихся объектов.
4. **Обнаружение движения** — идентификация блоков с движением выше порога.

#### Свойства и методы

| Свойство/Метод | Тип | Назначение |
|----------------|-----|------------|
| `BlockWidth`, `BlockHeight` | `int` | Размер блока для анализа локального контраста |
| `AdaptiveThresholdPercent` | `double` | Процент для вычисления адаптивного порога |
| `MoveDetectionPercent` | `double` | Процент пикселей, преодолевших порог, для обнаружения |
| `T1`, `Tr` | `double` | Пороги для фильтрации ложных срабатываний |
| `MovingDetectionMode` | `int` | Режим детекции движения (`0` — стандартный, `1` — нормализованный) |
| `HistLeftRange`, `HistRightRange` | `int` | Диапазон гистограммы для анализа |
| `MovingFrameMode` | `int` | Режим обработки кадров (`0` — стандартный, `1` — альтернативный) |
| `GetMovedImage()` | `const UBitmap&` | Получить изображение с выделенными движущимися объектами |
| `GetContrastGrid()` | `const UBRect*` | Получить сетку контрастных объектов |
| `GetMovedGrid()` | `const UBRect*` | Получить сетку движущихся объектов |

---

### UBACollateMovingDetector — упрощённый детектор движения

#### Особенности

- Более простая реализация детекции движения на основе разностного кадра.
- Публичное поле `DiffImage` для визуализации разности.
- Используется в случаях, когда не требуется сложный анализ локального контраста.

---

### UBAObjectDetector / UBANightDetector — интерфейс детекции объектов

#### UML-диаграмма компонентов

```mermaid
graph LR
    Src[Source/Background] --> Det[UBAMovingDetector*]
    Det --> Label[UBALabeling*]
    Label --> Show[UBAShowObjects*]
    Det --> ObjDet[UBAObjectDetector*]
    ObjDet --> Next[UDetectorBase/UCR*]
```

---

### Примеры использования (C++)

```cpp
// Ночной детектор движения
auto nightDet = storage->CreateComponent<RDK::UBANightMovingDetector>();
nightDet->Default();
nightDet->HistorySize = 30;
nightDet->BlockWidth = 16;
nightDet->BlockHeight = 16;
nightDet->AdaptiveThresholdPercent = 0.1;
nightDet->MoveDetectionPercent = 0.3;
nightDet->Build();

for (int step = 0; step < 1000; ++step) {
    nightDet->Input = frame;
    nightDet->Calculate();
    const UBRect* objects = nightDet->GetMovedObjects();
    const UBitmap& movedImg = nightDet->GetMovedImage();
    // обработка объектов
}
```

---

### Примеры конфигурации XML

```xml
<Component Id="NightMovingDet" Class="NightMovingDetector">
    <Parameters>
        <HistorySize>30</HistorySize>
        <BlockWidth>16</BlockWidth>
        <BlockHeight>16</BlockHeight>
        <AdaptiveThresholdPercent>0.1</AdaptiveThresholdPercent>
        <MoveDetectionPercent>0.3</MoveDetectionPercent>
        <T1>0.5</T1>
        <Tr>0.3</Tr>
        <MovingDetectionMode>0</MovingDetectionMode>
        <MovingFrameMode>0</MovingFrameMode>
    </Parameters>
</Component>
```

---

### Связь с конфигурационными проектами (`Bin/Configs`)

Компоненты детекции движения используются в пайплайнах видеонаблюдения:
- **UBAMovingDetector** — базовый класс для различных алгоритмов детекции движения.
- **UBANightMovingDetector** — специализированный алгоритм для ночных условий с анализом локального контраста.
- **UBACollateMovingDetector** — упрощённая реализация для быстрой детекции движения.

Они обычно размещаются после компонентов фона (`UBABackground*`) и разностных кадров (`UBADifferenceFrame*`) в конфигурациях `Bin/Configs/*`.

---

## Moving Detectors — motion detection components (Rdk-CvBasicLib)

**Classes**: `UBAMovingDetector*`, `UBAObjectDetector*`, `UBANightDetector` — motion detection algorithms for video surveillance pipelines, including specialized night-time detection with local contrast analysis.
