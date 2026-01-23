## Pipelines, Models & Statistics — пайплайны, модели и статистика (Rdk-CvBasicLib)

### Назначение

Компоненты `UBPipeline*`, `UBAModel` и `UBStatistic*` описывают:
- конвейер обработки изображений (последовательное/параллельное выполнение UBA‑компонентов);
- обёртку модели обработки (`UBAModel`);
- сбор и сохранение статистики и промежуточных результатов (`UBStatistic*`).

---

### UBPipeline / UBParallelPipeline — конвейеры обработки

#### UML-диаграмма классов

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

`UBPipeline` управляет набором дочерних компонентов `UNet` и определяет, какие типы разрешено включать в конвейер. `UBParallelPipeline` реализует параллельную схему исполнения.

#### UML-диаграмма компонентов

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

#### Жизненный цикл

Конкретные методы `ADefault/ABuild/ACalculate` зависят от реализации `UNet`, но типичный жизненный цикл пайплайна:

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

### UBAModel — модель обработки

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

`UBAModel` служит контейнером для составных моделей обработки (например, совокупность нескольких пайплайнов/веток), предоставляя единый выход `Output` и рабочее разрешение (`WorkWidth`, `WorkHeight`).

---

### UBStatistic / UBStatisticSimple — статистика и сохранение кадров

#### UML-диаграмма классов

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

#### Входы/выходы и поведение

- **Вход**: `Input` — вектор изображений (`UBitmap`), которые нужно сохранять/анализировать.  
- **Параметры сохранения**:
  - `SavePath`, `PrefixName`, `FileFormat` (`0` — bmp, `1` — jpeg), `FileNameSuffix`.  
  - `TimeToFileNameFlag`, `OrderIndexToFileNameFlag` — добавление времени/индекса в имя файла.  
  - `NumSkipSteps` — пропуск шагов между сохранениями.  
  - `UseManualStatistic` + `ManualStatisticSwitch` — ручкое включение/выключение сбора.
- **UBStatisticSimple**:
  - `TimeInterval` — минимальный интервал между сохранениями (или число шагов).  
  - `Mode` — режим работы (автоматический/ручной).  
  - `WriteSignal` — флаг разового сохранения в момент вызова `Calculate`.

#### UML-диаграмма последовательности

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

### Примеры использования (C++)

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

### Пример конфигурации XML

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

### Поток данных высокого уровня

```mermaid
flowchart LR
    Src[Capture/Source] --> Pipe[UBPipeline/UBParallelPipeline]
    Pipe --> Model[UBAModel]
    Model --> DetCls[Detectors/UCR*]
    DetCls --> Stat[UBStatistic*]
    Stat --> Files[Saved images/stats]
```

Эти компоненты связывают вместе цепочки обработки, логически оформляя “модель обработки” и обеспечивая сохранение промежуточных и финальных результатов в проектах `Bin/Configs/*`.

