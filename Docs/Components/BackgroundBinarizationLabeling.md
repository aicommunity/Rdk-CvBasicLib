## RU

## Background / Difference / Binarization / Labeling / Looping / GUI — фон, разность, бинаризация и разметка (Rdk-CvBasicLib)

### Назначение

Группа компонентов `UBABackground*`, `UBADifferenceFrame*`, `UBABinarization*`, `UBALabeling*`, `UBALooping*`, `UBAGuiSelection*`, `UBAShowObjects*` реализует этапы фоново‑разностной обработки, пороговой сегментации и визуализации/разметки в пайплайнах компьютерного зрения.

---

## EN

### UML-диаграмма классов (обзор)

```mermaid
classDiagram
    UNet <|-- UBABackground
    UBABackground <|-- UBABackgroundAvg
    UBABackground <|-- UBABackgroundExponnential
    UBABackground <|-- UBADeltaBackgroundExponnential
    UBABackground <|-- UBABackgroundSimpleAdaptive
    UBABackground <|-- UBABackgroundDependDiff

    UNet <|-- UBADifferenceFrame
    UBADifferenceFrame <|-- UBADifferenceFrameSimple

    UNet <|-- UBABinarization
    UBABinarization <|-- UBABinarizationSimple
    UBABinarization <|-- UBABinarizationSimpleAdaptiveThreshold
    UBABinarization <|-- UBABinarizationOtsu

    UNet <|-- UBALabeling
    UBALabeling <|-- UBALabelingSimple

    UNet <|-- UBALooping
    UBALooping <|-- UBALoopingSimple
    UBALooping <|-- UBALoopingSobel

    UNet <|-- UBAGuiSelection
    UBAGuiSelection <|-- UBAGuiSelectionRect

    UNet <|-- UBAShowObjects
    UBAShowObjects <|-- UBAShowObjectsSimple
```

---

### UBABackground* — оценка фона

#### UML (базовый класс и примеры наследников)

```mermaid
classDiagram
    class UBABackground {
        +Input : UBitmap
        +Background : UBitmap
        +IsBGReady : bool
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBABackgroundAvg {
        +HistorySize : int
        -History : UBitmapVector
        -CurrentHistoryIndex : int
        -CurrentHistorySize : int
        +New() UBABackgroundAvg*
        +BCalculate(UBitmap&,UBitmap&) bool
    }

    class UBABackgroundExponnential {
        +tempoUpdate : double
        +New() UBABackgroundExponnential*
        +BCalculate(UBitmap&,UBitmap&) bool
    }
```

#### Идея

- `UBABackground` хранит текущий фон (`Background`) и признак готовности (`IsBGReady`).  
- Наследники реализуют разные стратегии обновления фона: скользящее среднее, экспоненциальное сглаживание, адаптивные модели с учётом переднего плана.

---

### UBADifferenceFrame* — разность кадров

```mermaid
classDiagram
    class UBADifferenceFrame {
        +Input1 : UBitmap
        +Input2 : UBitmap
        +Output : UBitmap
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBADifferenceFrameSimple {
        +New() UBADifferenceFrameSimple*
        +BCalculate(UBitmap&,UBitmap&,UBitmap&) bool
    }
```

Компоненты вычисляют покадровую разность (`Input1 - Input2`) и используются как часть цепочки детекции движения и вычисления фона.

---

### UBABinarization* — бинаризация

```mermaid
classDiagram
    class UBABinarization {
        +Input : UBitmap
        +Output : UBitmap
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBABinarizationSimple {
        +Threshold : UColorT
        +New() UBABinarizationSimple*
        +BCalculate(UBitmap&,UBitmap&) bool
    }

    class UBABinarizationOtsu {
        +minThreshold : int
        +Mask : UBitmap
        +New() UBABinarizationOtsu*
        +BCalculate(UBitmap&,UBitmap&,UBitmap&) bool
    }
```

Конфигурационный алиас `TBinarizationSimpleAdaptiveThreshold` соответствует `UBABinarizationSimpleAdaptiveThreshold` (адаптивный порог).

`UBABinarizationSimpleAdaptiveThreshold` добавляет адаптивный порог с учётом фона, статистик и карт счётчиков переднего/заднего плана.

---

### UBALabeling* — разметка компонент

```mermaid
classDiagram
    class UBALabeling {
        +Input : UBitmap
        +Zones : MDMatrix<double>
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBALabelingSimple {
        +New() UBALabelingSimple*
        +LCalculate(UBitmap&,MDMatrix<double>&) void
    }
```

`Zones` содержит метки/описание связных компонент (координаты, площади и т.п.), используемых последующими детекторами/визуализаторами.

---

### UBALooping* — циклическая обработка

```mermaid
class UBALooping {
    +Input : UBitmap
    +Output : UBitmap
    +ADefault() bool
    +ABuild() bool
    +AReset() bool
    +ACalculate() bool
}

class UBALoopingSimple {
    +New() UBALoopingSimple*
    +BCalculate(UBitmap&,UBitmap&) bool
}

class UBALoopingSobel {
    +New() UBALoopingSobel*
    +BCalculate(UBitmap&,UBitmap&) bool
}
```

Обеспечивают повторяющееся применение простых операторов (в т.ч. Sobel‑фильтра) к последовательности кадров.

---

### UBAGuiSelection* и UBAShowObjects* — GUI и визуализация

```mermaid
classDiagram
    class UBAGuiSelection {
        +Input : UBitmap
        +Output : UBitmap
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBAGuiSelectionRect {
        +MouseState : UMouse
        +CurrentX,CurrentY : int
        +PreviousX,PreviousY : int
        +IWidth,IHeight : int
        +TIWidth,TIHeight : int
        +New() UBAGuiSelectionRect*
        +BCalculate(UBitmap&,UBitmap&) bool
    }

    class UBAShowObjects {
        +PenColor : UColorT
        +PenWidth : int
        +EnableShowFlag : bool
        +Input : UBitmap
        +Output : UBitmap
        +ObjectsColor : vector<UColorT>
        +ObjectsName : vector<string>
        +ObjectsId : MDMatrix<int>
        +SetActivity(bool) bool
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBAShowObjectsSimple {
        +Zones : vector<UBPoint>
        +MatrixPoints : MDMatrix<double>
        +New() UBAShowObjectsSimple*
    }
```

Используются для интерактивного выбора прямоугольников, отображения зон детекции и подписей объектов поверх исходного изображения.

---

### UML-диаграмма последовательности (фон → разность → бинаризация → разметка)

```mermaid
sequenceDiagram
    participant Src as Source/Camera
    participant Bg as UBABackground*
    participant Diff as UBADifferenceFrame*
    participant Bin as UBABinarization*
    participant Lab as UBALabeling*
    participant Vis as UBAShowObjects*

    loop каждый кадр
        Src-->>Bg: Input (UBitmap)
        Bg->>Bg: ACalculate() / AFBgCalculate()
        Bg-->>Diff: Background
        Src-->>Diff: Input1
        Diff->>Diff: ACalculate() / AFDiffCalculate()
        Diff-->>Bin: Input
        Bin->>Bin: ACalculate() / AFBgCalculate()
        Bin-->>Lab: бинаризованное изображение
        Lab->>Lab: ACalculate() / AFBgCalculate()
        Lab-->>Vis: Zones / маска
        Vis->>Vis: ACalculate() (отрисовка зон на Output)
    end
```

---

### Пример конфигурации XML (упрощённый)

```xml
<Component Id="Background" Class="BackgroundAvg">
    <Parameters>
        <HistorySize>30</HistorySize>
    </Parameters>
</Component>

<Component Id="Diff" Class="DifferenceFrameSimple">
    <Parameters/>
</Component>

<Component Id="Bin" Class="BinarizationSimple">
    <Parameters>
        <Threshold>128</Threshold>
    </Parameters>
</Component>

<Component Id="Label" Class="LabelingSimple">
    <Parameters/>
</Component>

<Component Id="Show" Class="ShowObjectsSimple">
    <Parameters>
        <PenColor>#00FF00</PenColor>
        <PenWidth>2</PenWidth>
    </Parameters>
</Component>
```

---

### Поток данных компонента в библиотеке

```mermaid
flowchart LR
    Src[Capture/Source] --> Bg[UBABackground*]
    Bg --> Diff[UBADifferenceFrame*]
    Diff --> Bin[UBABinarization*]
    Bin --> Lab[UBALabeling*]
    Lab --> Vis[UBAShowObjects*]
    Vis --> Out[Display/Recorder]
```

Эти компоненты формируют типичный контур “фон + движение + бинаризация + разметка”, используемый во множестве конфигураций `Bin/Configs/*` для задач детекции движения, сегментации по порогу и визуализации результатов.
