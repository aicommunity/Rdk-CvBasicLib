## Geometric Transformations — геометрические преобразования (Rdk-CvBasicLib)

### Назначение

Компоненты `UBAResize*`, `UBARotate*`, `UBAFlipImage*` выполняют геометрические преобразования изображений: изменение размера, поворот и отражение. Используются в пайплайнах предобработки перед детекцией/классификацией.

---

### UML-диаграмма классов

```mermaid
classDiagram
    UNet <|-- UBAResize
    UBAResize <|-- UBAResizeEdges

    UNet <|-- UBARotate
    UBARotate <|-- UBARotateSimple

    UNet <|-- UBAFlipImage
    UBAFlipImage <|-- UBAFlipImageSimple

    class UBAResize {
        +NewWidth : int
        +NewHeight : int
        +Input : UBitmap
        +Output : UBitmap
        +GetNewWidth() int
        +GetNewHeight() int
        +SetNewWidth(int) bool
        +SetNewHeight(int) bool
        +BCalculate(UBitmap&,UBitmap&) bool
        +BCalculate(UBitmap&,int,int) bool
        +operator()(UBitmap&,UBitmap&) bool
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBARotate {
        +Angle : float
        +Enlarge : bool
        +Input : UBitmap
        +Output : UBitmap
        +GetAngle() float
        +SetAngle(float) bool
        +GetEnlarge() bool
        +SetEnlarge(bool) bool
        +operator()(UBitmap&,UBitmap&) bool
        +BCalculate(UBitmap&,UBitmap&) bool
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBAFlipImage {
        +Mode : int
        +Input : UBitmap
        +Output : UBitmap
        +BCalculate(UBitmap&,UBitmap&) bool
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }
```

---

### UBAResize / UBAResizeEdges — изменение размера

#### UML-диаграмма последовательности

```mermaid
sequenceDiagram
    participant Src as Source/PreviousUBA
    participant Resize as UBAResizeEdges
    participant Next as NextUBAComponent

    Src-->>Resize: Input (UBitmap)
    Resize->>Resize: ACalculate() / AFCCalculate()
    Note over Resize: Чтение NewWidth/NewHeight<br/>Вызов BCalculate(input, output)
    Resize-->>Next: Output (resized UBitmap)
```

#### UML-диаграмма активности (UBAResizeEdges::BCalculate)

```mermaid
flowchart TD
    Start([Start]) --> ReadParams[Прочитать NewWidth, NewHeight]
    ReadParams --> CheckSize{Размеры > 0?}
    CheckSize -->|Нет| ZeroOut[Output = пустое изображение]
    CheckSize -->|Да| Resize[Выполнить cv::resize<br/>с сохранением пропорций<br/>или с обрезкой до NewWidth x NewHeight]
    Resize --> WriteOut[Записать в Output]
    WriteOut --> End([End])
    ZeroOut --> End
```

#### Свойства и методы

| Свойство/Метод | Тип | Назначение |
|----------------|-----|------------|
| `NewWidth` | `int` | Желаемая ширина выходного изображения |
| `NewHeight` | `int` | Желаемая высота выходного изображения |
| `Input` | `UBitmap` | Входное изображение |
| `Output` | `UBitmap` | Изменённое по размеру изображение |
| `BCalculate(UBitmap&, UBitmap&)` | `bool` | Виртуальный метод, реализуемый в `UBAResizeEdges` |

---

### UBARotate / UBARotateSimple — поворот изображения

#### UML-диаграмма последовательности

```mermaid
sequenceDiagram
    participant Src as Source
    participant Rot as UBARotateSimple
    participant Next as NextUBAComponent

    Src-->>Rot: Input (UBitmap)
    Rot->>Rot: ACalculate() / AFCCalculate()
    Note over Rot: Чтение Angle, Enlarge<br/>Вызов BCalculate(input, output)
    Rot-->>Next: Output (rotated UBitmap)
```

#### UML-диаграмма активности (UBARotateSimple::BCalculate)

```mermaid
flowchart TD
    Start([Start]) --> ReadParams[Прочитать Angle, Enlarge]
    ReadParams --> CheckEnlarge{Enlarge?}
    CheckEnlarge -->|Да| CalcNewSize[Вычислить размеры<br/>с учётом поворота]
    CheckEnlarge -->|Нет| KeepSize[Сохранить исходный размер]
    CalcNewSize --> Rotate[Выполнить cv::warpAffine<br/>с матрицей поворота на Angle]
    KeepSize --> Rotate
    Rotate --> Crop[При необходимости обрезать<br/>выходное изображение]
    Crop --> WriteOut[Записать в Output]
    WriteOut --> End([End])
```

#### Свойства и методы

| Свойство/Метод | Тип | Назначение |
|----------------|-----|------------|
| `Angle` | `float` | Угол поворота в градусах |
| `Enlarge` | `bool` | Увеличивать ли размер изображения, чтобы вместить повёрнутое |
| `Input` | `UBitmap` | Входное изображение |
| `Output` | `UBitmap` | Повёрнутое изображение |
| `BCalculate(UBitmap&, UBitmap&)` | `bool` | Виртуальный метод, реализуемый в `UBARotateSimple` |

---

### UBAFlipImage / UBAFlipImageSimple — отражение изображения

#### UML-диаграмма последовательности

```mermaid
sequenceDiagram
    participant Src as Source
    participant Flip as UBAFlipImageSimple
    participant Next as NextUBAComponent

    Src-->>Flip: Input (UBitmap)
    Flip->>Flip: ACalculate() / AFCCalculate()
    Note over Flip: Чтение Mode<br/>Вызов BCalculate(input, output)
    Flip-->>Next: Output (flipped UBitmap)
```

#### UML-диаграмма активности (UBAFlipImageSimple::BCalculate)

```mermaid
flowchart TD
    Start([Start]) --> ReadMode[Прочитать Mode]
    ReadMode --> SwitchMode{Mode?}
    SwitchMode -->|0 (горизонтально)| FlipH[Выполнить cv::flip<br/>с флагом 1]
    SwitchMode -->|1 (вертикально)| FlipV[Выполнить cv::flip<br/>с флагом 0]
    SwitchMode -->|2 (оба)| FlipBoth[Выполнить cv::flip<br/>с флагом -1]
    FlipH --> WriteOut
    FlipV --> WriteOut
    FlipBoth --> WriteOut
    WriteOut[Записать в Output] --> End([End])
```

#### Свойства и методы

| Свойство/Метод | Тип | Назначение |
|----------------|-----|------------|
| `Mode` | `int` | Режим отражения: `0` — горизонтально, `1` — вертикально, `2` — оба |
| `Input` | `UBitmap` | Входное изображение |
| `Output` | `UBitmap` | Отражённое изображение |
| `BCalculate(UBitmap&, UBitmap&)` | `bool` | Виртуальный метод, реализуемый в `UBAFlipImageSimple` |

---

### UML-диаграмма компонентов

```mermaid
graph LR
    Src[Source/Capture] --> Resize[UBAResize*]
    Resize --> Rotate[UBARotate*]
    Rotate --> Flip[UBAFlipImage*]
    Flip --> Next[Detector/Classifier]
```

---

### Примеры использования (C++)

```cpp
// Изменение размера
auto resize = storage->CreateComponent<RDK::UBAResizeEdges>();
resize->Default();
resize->NewWidth = 640;
resize->NewHeight = 480;
resize->Build();
resize->Input = inputBitmap;
resize->Calculate();
UBitmap resized = resize->Output;

// Поворот
auto rotate = storage->CreateComponent<RDK::UBARotateSimple>();
rotate->Default();
rotate->Angle = 90.0f;
rotate->Enlarge = true;
rotate->Build();
rotate->Input = inputBitmap;
rotate->Calculate();
UBitmap rotated = rotate->Output;

// Отражение
auto flip = storage->CreateComponent<RDK::UBAFlipImageSimple>();
flip->Default();
flip->Mode = 0; // горизонтально
flip->Build();
flip->Input = inputBitmap;
flip->Calculate();
UBitmap flipped = flip->Output;
```

---

### Примеры конфигурации XML

```xml
<Component Id="Resize" Class="ResizeEdges">
    <Parameters>
        <NewWidth>640</NewWidth>
        <NewHeight>480</NewHeight>
    </Parameters>
</Component>

<Component Id="Rotate" Class="RotateSimple">
    <Parameters>
        <Angle>90.0</Angle>
        <Enlarge>true</Enlarge>
    </Parameters>
</Component>

<Component Id="Flip" Class="FlipImageSimple">
    <Parameters>
        <Mode>0</Mode> <!-- 0=horizontal, 1=vertical, 2=both -->
    </Parameters>
</Component>
```

---

### Связь с конфигурационными проектами (`Bin/Configs`)

Компоненты геометрических преобразований часто используются в пайплайнах предобработки:
- **UBAResize** — приведение входных кадров к фиксированному разрешению, требуемому детекторами/классификаторами.
- **UBARotate** — коррекция ориентации камеры или подготовка данных для обучения с аугментацией.
- **UBAFlipImage** — аугментация данных или коррекция зеркального отражения камеры.

Они обычно размещаются между источниками (`TCapture*`, `UBASource*`) и блоками детекции/классификации в конфигурациях `Bin/Configs/*`.

---

## Geometric Transformations — image transformations (Rdk-CvBasicLib)

**Classes**: `UBAResize*`, `UBARotate*`, `UBAFlipImage*` — geometric image transformations (resize, rotation, flipping) used in preprocessing pipelines before detection/classification.
