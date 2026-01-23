## Capture & Sources — захват и источники изображений (Rdk-CvBasicLib)

### Назначение

Компоненты семейства `TCapture*` и `UBA*Source*` обеспечивают захват изображений из внешних устройств (камеры, IP‑камеры), последовательностей файлов и внутренних bitmap‑источников, формируя единый поток `UBitmap` для дальнейшей обработки в UBA‑пайплайнах.

---

### UML-диаграмма классов

```mermaid
classDiagram
    UNet <|-- TCapture
    TCapture <|-- TCaptureCamera
    TCaptureCamera <|-- TCaptureCameraIp
    TCapture <|-- TCaptureImageSequence

    UNet <|-- UBASource
    UBASource <|-- UBASourceFile
    UNet <|-- UBASourceMultiFile

    UNet <|-- UBABitmapSource
    UBABitmapSource <|-- UBABitmapSourceSimple
    UBABitmapSource <|-- UBABitmapSourceFile

    UBASource <|-- UBASourceFreezeFrame
```

**TCapture** — абстрактный базовый класс захвата кадров (камеры/файлы), управляющий состояниями `Created / Initialization / Connected / Active / Paused / Disconnected`.

---

### TCapture / TCaptureCamera / TCaptureCameraIp / TCaptureImageSequence

#### UML (основные свойства и методы)

```mermaid
classDiagram
    class TCapture {
        +DesiredFps : double
        +CloseTimeout : int
        +ReconnectTimeout : int
        +CaptureTimeout : int
        +RestartMode : int
        +DesiredWidth : int
        +DesiredHeight : int
        +DesiredResolutionFlag : bool
        +CameraType : int
        +OutputImage : UBitmap
        +CaptureTime : unsigned long long
        +EnableCapture : bool
        +Paused : bool
        +FlipX : bool
        +FlipY : bool
        +RelevData : bool
        +RotationAngle : double
        +FixedRotation : int
        +NumFrames : unsigned long long
        +CaptureFps : double
        +RealFps : double
        +CaptureState : int
        +FramePosition : unsigned long long
        +FrameTime : double
        +StartCapture() bool
        +StopCapture() bool
        +PauseCapture() bool
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class TCaptureCamera {
        +ADefault1() bool
        +ABuild1() bool
        +AReset1() bool
        +ACalculate1() bool
        +ASetEnableCapture(bool) bool
        +AStartCapture() bool
        +AStopCapture() bool
    }

    class TCaptureCameraIp {
        +Address : string
        +Login : string
        +Password : string
        +SetAddress(...) bool
        +SetLogin(...) bool
        +SetPassword(...) bool
    }

    class TCaptureImageSequence {
        +Path : string
        +IsPathRelativeFromConfig : bool
        +RepeatFlag : bool
        +CaptureDelay : int
        +NumImages : int
        +CurrentImageIndex : int
        +CurrentImageFileName : string
    }
```

#### UML-диаграмма последовательности (типичный цикл захвата)

```mermaid
sequenceDiagram
    participant Storage as UStorage
    participant Cap as TCaptureCamera/TCaptureImageSequence
    participant Pipeline as UBPipeline

    Storage->>Cap: New()
    Storage->>Cap: ADefault()
    Note over Cap: Настройка DesiredFps,<br/>разрешения и таймаутов
    Storage->>Cap: ABuild()

    Storage->>Cap: StartCapture()
    loop пока EnableCapture=true
        Cap->>Cap: ACalculate()
        Cap-->>Pipeline: OutputImage (UBitmap)
    end
    Storage->>Cap: StopCapture()
```

#### UML-диаграмма состояний TCapture

```mermaid
stateDiagram-v2
    [*] --> Created
    Created --> Initialization: ADefault()
    Initialization --> Connected: ABuild()
    Connected --> Active: StartCapture()
    Active --> Paused: PauseCapture()
    Paused --> Active: SetPaused(false)
    Active --> Disconnected: StopCapture()
    Disconnected --> Reconnect: SetReconnectTimeout()/RestartMode
    Reconnect --> Active: StartCapture()
```

#### Входы/выходы и свойства

- **Выход**: `OutputImage` — текущий кадр `UBitmap`.  
- **Основные параметры**:
  - `DesiredFps`, `CaptureTimeout`, `CloseTimeout`, `ReconnectTimeout`, `RestartMode`.  
  - `DesiredWidth`, `DesiredHeight`, `DesiredResolutionFlag`.  
  - `EnableCapture`, `Paused`, `FlipX`, `FlipY`, `RotationAngle`, `FixedRotation`.
- **Состояние**:
  - `CaptureState`, `NumFrames`, `CaptureFps`, `RealFps`, `FramePosition`, `FrameTime`.
- **TCaptureCameraIp**:
  - `Address`, `Login`, `Password` — параметры подключения к IP‑камере.
- **TCaptureImageSequence**:
  - `Path`, `IsPathRelativeFromConfig`, `RepeatFlag`, `CaptureDelay`.  

#### Пример использования (C++)

```cpp
auto cap = storage->CreateComponent<RDK::TCaptureImageSequence>();
cap->Default();
cap->Path = "Data/Images/*.png";
cap->RepeatFlag = true;
cap->CaptureDelay = 40; // мс между кадрами
cap->Build();

cap->StartCapture();
while (cap->GetCaptureState() == RDK_CAPTURE_ACTIVE) {
    cap->Calculate();
    UBitmap frame = cap->OutputImage;
    // передаём frame дальше в UBPipeline
}
cap->StopCapture();
```

---

### UBASource / UBASourceFile / UBASourceMultiFile / UBABitmapSource* / UBASourceFreezeFrame

#### UML (основные связи)

```mermaid
classDiagram
    class UBASource {
        +Input : UBitmap
        +Output : UBitmap
        +SetOutputData(...) bool
        +New() UBASource*
        +ADefault() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBASourceFile {
        +FileName : string
        +IsLoad() bool
        +New() UBASourceFile*
        +ADefault() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBASourceMultiFile {
        +FileNames : vector<string>
        +IsLoad() bool
        +New() UBASourceMultiFile*
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBABitmapSource {
        +SourceParamaters : vector<UBitmapParam>
        +Output : UBitmap
        +ADefault() bool
        +ABuild() bool
        +AReset() bool
        +ACalculate() bool
    }

    class UBASourceFreezeFrame {
        +FreezeFlag : bool
        +Output : UBitmap
        +ADefault() bool
        +AReset() bool
        +ACalculate() bool
    }
```

#### UML-диаграмма последовательности (пример для UBASourceFile)

```mermaid
sequenceDiagram
    participant Storage as UStorage
    participant Src as UBASourceFile
    participant Next as UBAPipeline/UBA*

    Storage->>Src: New() + ADefault()
    Storage->>Src: SetFileName("image.png")
    Storage->>Src: ABuild()

    loop каждый шаг
        Storage->>Src: ACalculate()
        Src-->>Next: Output (UBitmap)
    end
```

#### Входы/выходы и свойства

- **UBASource**
  - `Input` / `Output` (`UBitmap`) — базовый источник, который может пробрасывать или переопределять данные.
- **UBASourceFile**
  - `FileName` — путь к единичному файлу; `IsLoad()` — индикатор успешной загрузки.
- **UBASourceMultiFile**
  - `FileNames` — список путей; динамически создаёт выходные свойства `Output[i]` для каждого файла.
- **UBABitmapSource / UBABitmapSourceSimple / UBABitmapSourceFile**
  - `SourceParamaters` — параметры генерации/хранения bitmap‑данных.  
  - `Output` — результирующий кадр.
- **UBASourceFreezeFrame**
  - `FreezeFlag` — при `true` удерживает последний кадр на выходе, даже если вход меняется.

#### Примеры XML‑конфигурации

```xml
<!-- Источник одного файла -->
<Component Id="SrcImage" Class="SourceFile">
    <Parameters>
        <FileName>Data/input.png</FileName>
    </Parameters>
</Component>

<!-- Источник списка файлов -->
<Component Id="SrcMulti" Class="SourceMultiFile">
    <Parameters>
        <FileNames>
            <elem>Data/frame_0001.png</elem>
            <elem>Data/frame_0002.png</elem>
        </FileNames>
    </Parameters>
</Component>
```

---

### Компонентная диаграмма (захват и источники в пайплайне)

```mermaid
graph LR
    Cam[TCapture*] --> Pre[UBA Preprocessing]
    Src[UBASource*/UBABitmapSource*] --> Pre
    FileSrc[UBASourceFile/UBASourceMultiFile] --> Pre
    Freeze[UBASourceFreezeFrame] --> Pre
```

Источники и захваты образуют начальное звено большинства конфигураций в `Bin/Configs/*`, подавая `UBitmap` кадры в UBA‑конвейеры (`ColorConvert`, `Crop`, `Reduce`, фон, бинаризация, детекция и т.д.).

