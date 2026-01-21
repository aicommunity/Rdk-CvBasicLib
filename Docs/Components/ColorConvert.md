## ColorConvert — преобразование цветовых пространств (Rdk-CvBasicLib)

**Класс**: `ColorConvert` (реализация в `UBAColorConvert.cpp`) — преобразует изображения между цветовыми пространствами (BGR/RGB/GRAY и т.п.).  
**Storage-компоненты**: регистрируется через `UploadClass("ColorConvert", ...)` и используется в пайплайнах обработки.

### Регистрация и класс

```mermaid
classDiagram
    UComponent <|-- ColorConvert
    class ColorConvert {
        +colorModeIn : enum
        +colorModeOut : enum
        +inputBitmap : UProperty
        +outputBitmap : UProperty
    }
```

### Входы/выходы
- Вход: `UBitmap` (изображение) в исходном цветовом пространстве.
- Выход: `UBitmap` в целевом цветовом пространстве.

### Storage-инстансы
- В `ClDesc`/`Configs`: `ClassName = "ColorConvert"`; параметры определяют режим (например, BGR→GRAY).

```mermaid
flowchart LR
    src[Source/Camera] --> cc[ColorConvert]
    cc --> next[Next UBA component]
```

Пояснение: блок-схема показывает поток данных/сигналов (входы → компонент → выходы).

### Типовой сценарий (Sequence)

```mermaid
sequenceDiagram
    participant S as UStorage
    participant Src as Source
    participant CC as ColorConvert
    S->>CC: ADefault + ABuild
    loop each frame
        Src-->>CC: UBitmap frame
        S->>CC: ACalculate()
        CC-->>S: converted UBitmap
    end
```

Пояснение: диаграмма последовательности показывает типовой сценарий взаимодействия и порядок вызовов.

---

## ColorConvert — color space converter (Rdk-CvBasicLib)

**Class**: `ColorConvert` — converts `UBitmap` between color spaces (e.g. BGR→GRAY) as part of UBA pipelines.

