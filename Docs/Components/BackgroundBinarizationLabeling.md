## RU

## Background / Difference / Binarization / Labeling / Looping / GUI — фон, разность, бинаризация и разметка (Rdk-CvBasicLib)

### Назначение

Группа компонентов `UBABackground*`, `UBADifferenceFrame*`, `UBABinarization*`, `UBALabeling*`, `UBALooping*`, `UBAGuiSelection*`, `UBAShowObjects*` реализует этапы фоново‑разностной обработки, пороговой сегментации и визуализации/разметки в пайплайнах компьютерного зрения.

---

## EN

## Background / Difference / Binarization / Labeling / Looping / GUI — фон, difference, binarization, and labeling (Rdk-CvBasicLib)

### Class diagram (overview)

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

### UBABackground* — estimation background

#### UML (base class и examples descendants)

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

#### Idea

- `UBABackground` stores current фон (`Background`) и readiness flag (`IsBGReady`).  
- Descendants implement different strategies update background: moving average, exponential smoothing, adaptive models с accounting foreground plan.

---

### UBADifferenceFrame* — difference frames

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

Components compute per-frame difference (`Input1 - Input2`) и are used как part chain detection motion и computation background.

---

### UBABinarization* — binarization

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

Configuration alias `TBinarizationSimpleAdaptiveThreshold` matches `UBABinarizationSimpleAdaptiveThreshold` (adaptive threshold).

`UBABinarizationSimpleAdaptiveThreshold` adds adaptive threshold с accounting background, statistics и maps counters foreground/background plan.

---

### UBALabeling* — labeling component

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

`Zones` contains labels/description of connected components (coordinates, areas, etc.), used downstream by detectors/visualizers.

---

### UBALooping* — cyclic processing

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

Provide repeated application simple operators (в т.ч. Sobel‑filter) к sequence frames.

---

### UBAGuiSelection* и UBAShowObjects* — GUI и visualization

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

Are used для interactive selection rectangles, display зон detection и labels objects over source images.

---

### Sequence diagram (фон → difference → binarization → labeling)

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

### Example configuration XML (simplified)

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

### Flow data component в library

```mermaid
flowchart LR
    Src[Capture/Source] --> Bg[UBABackground*]
    Bg --> Diff[UBADifferenceFrame*]
    Diff --> Bin[UBABinarization*]
    Bin --> Lab[UBALabeling*]
    Lab --> Vis[UBAShowObjects*]
    Vis --> Out[Display/Recorder]
```

Эти components form typical pipeline “фон + motion + binarization + labeling”, used во many configurations `Bin/Configs/*` для tasks detection motion, segmentation по threshold и visualization results.
