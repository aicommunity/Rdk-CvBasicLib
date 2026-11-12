## RU

## Pipelines, Models & Statistics — пайплайны, модели и статистика (Rdk-CvBasicLib)

### Назначение

Компоненты `UBPipeline*`, `UBAModel` и `UBStatistic*` описывают:
- конвейер обработки изображений (последовательное/параллельное выполнение UBA‑компонентов);
- обёртку модели обработки (`UBAModel`);
- сбор и сохранение статистики и промежуточных результатов (`UBStatistic*`).

---

## EN

## Pipelines, Models & Statistics — pipelines, models, and statistics (Rdk-CvBasicLib)

### UBPipeline / UBParallelPipeline — pipelines processing

#### Class diagram

```mermaid
classDiagram
    UNet <|-- UBPipeline
    UBPipeline <|-- UBParallelPipeline

    class UBPipeline {
        +New() UBPipeline*
        +CheckComponentType(comp) bool
        +AAddComponent(comp, pointer) bool
        +ADelComponent(comp) bool
    }

    class UBParallelPipeline {
        +New() UBParallelPipeline*
        +ADefault() bool
        +AReset() bool
        +ACalculate() bool
    }
```

`UBPipeline` manages set child components `UNet` и defines, which types allowed include в pipeline. `UBParallelPipeline` implements parallel execution scheme.

#### Component diagram

```mermaid
graph LR
    Src[Capture/Source] --> Pipe[UBPipeline]
    Pipe --> CC[ColorConvert]
    Pipe --> CR[Crop/Reduce]
    Pipe --> BG[Background/Binarization]
    Pipe --> DET[Detector/Segmentator]
    Pipe --> CLS[UCR*]
    Pipe --> STAT[UBStatistic*]
```

#### Lifecycle cycle

Specific methods `ADefault/ABuild/ACalculate` depend от implementation `UNet`, но typical lifecycle cycle pipeline:

```mermaid
sequenceDiagram
    participant Storage as UStorage
    participant Pipe as UBPipeline/UBParallelPipeline
    participant C1 as UBAComponent1
    participant C2 as UBAComponent2

    Storage->>Pipe: New()
    Storage->>Pipe: ADefault()
    Note over Pipe: Добавление компонентов и настройка связей
    Storage->>Pipe: ABuild()

    loop каждый шаг
        Storage->>Pipe: ACalculate()
        Pipe->>C1: ACalculate()
        C1-->>C2: данные по свойствам
        Pipe->>C2: ACalculate()
    end
```

---

### UBAModel — model processing

```mermaid
classDiagram
    class UBAModel {
        +Output : UBitmap
        +WorkWidth : int
        +WorkHeight : int
        +New() UBAModel*
        +ADefault() bool
        +AMDefault() bool
        +ABuild() bool
        +AMBuild() bool
        +AReset() bool
        +AMReset() bool
        +ACalculate() bool
        +AMCalculate() bool
    }
```

`UBAModel` serves as a container for composite model processing (for example, a collection of several pipelines/branches), providing a single output `Output` and working resolution (`WorkWidth`, `WorkHeight`).

---

### UBStatistic / UBStatisticSimple — statistics и saving frames

#### Class diagram

```mermaid
classDiagram
    class UBStatistic {
        +SavePath : string
        +PrefixName : string
        +SubFolderAfterResetFlag : bool
        +ReflectionXFlag : bool
        +InputIndexMode : int
        +TimeToFileNameFlag : bool
        +OrderIndexToFileNameFlag : bool
        +NumSkipSteps : int
        +FileFormat : int
        +FileNameSuffix : int
        +ExcludeModelFileName : bool
        +UseManualStatistic : bool
        +ManualStatisticSwitch : bool
        +Input : vector<UBitmap>
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBStatisticSimple {
        +TimeInterval : int
        +Mode : int
        +WriteSignal : bool
        +New() UBStatisticSimple*
        +AFSDefault() bool
        +AFSBuild() bool
        +AFSReset() bool
        +AFSCalculate() bool
        +Save() bool
    }
```

#### Inputs/outputs и behavior

- **Input**: `Input` — vector images (`UBitmap`), which need save/analyze.  
- **Parameters saves**:
  - `SavePath`, `PrefixName`, `FileFormat` (`0` — bmp, `1` — jpeg), `FileNameSuffix`.  
  - `TimeToFileNameFlag`, `OrderIndexToFileNameFlag` — addition time/index в имя file.  
  - `NumSkipSteps` — skip steps between saves.  
  - `UseManualStatistic` + `ManualStatisticSwitch` — manual enable/disable collection.
- **UBStatisticSimple**:
  - `TimeInterval` — minimum interval between saves (или number steps).  
  - `Mode` — mode work (automatic/manual).  
  - `WriteSignal` — one-shot save flag at the moment `Calculate` is called.

#### Sequence diagram

```mermaid
sequenceDiagram
    participant Pipe as UBPipeline
    participant Stat as UBStatisticSimple
    loop каждый шаг
        Pipe-->>Stat: Input (vector<UBitmap>)
        Stat->>Stat: ACalculate()/AFSCalculate()
        alt Условия сохранения выполнены
            Stat->>Stat: Save()
        end
    end
```

---

### Usage Examples (C++)

```cpp
// Пайплайн
auto pipe = storage->CreateComponent<RDK::UBPipeline>();
pipe->Default();
// ... добавить компоненты в pipe ...
pipe->Build();

// Статистика
auto stat = storage->CreateComponent<RDK::UBStatisticSimple>();
stat->Default();
stat->SavePath = "Stats/Run1";
stat->PrefixName = "Frame";
stat->FileFormat = 1;       // jpeg
stat->TimeInterval = 5;     // условный интервал
stat->Build();

for (int step = 0; step < 1000; ++step) {
    pipe->Calculate();
    // заполняем stat->Input где-то в конфиге/коде
    stat->Calculate();
}
```

---

### Example configuration XML

```xml
<Component Id="MainPipeline" Class="UBPipeline">
    <Parameters/>
</Component>

<Component Id="ParallelPipeline" Class="UBParallelPipeline">
    <Parameters/>
</Component>

<Component Id="StatFrames" Class="UBStatisticSimple">
    <Parameters>
        <SavePath>Results/Frames</SavePath>
        <PrefixName>Frame</PrefixName>
        <FileFormat>1</FileFormat> <!-- jpeg -->
        <TimeInterval>10</TimeInterval>
        <Mode>0</Mode>
    </Parameters>
</Component>
```

---

### Flow data high level

```mermaid
flowchart LR
    Src[Capture/Source] --> Pipe[UBPipeline/UBParallelPipeline]
    Pipe --> Model[UBAModel]
    Model --> DetCls[Detectors/UCR*]
    DetCls --> Stat[UBStatistic*]
    Stat --> Files[Saved images/stats]
```

Эти components link together chain processing, logically structuring “model processing” и ensuring saving intermediate и final results в projectх `Bin/Configs/*`.
