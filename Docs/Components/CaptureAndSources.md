## RU

## Capture & Sources — захват и источники изображений (Rdk-CvBasicLib)

### Назначение

Компоненты семейства `TCapture*` и `UBA*Source*` обеспечивают захват изображений из внешних устройств (камеры, IP‑камеры), последовательностей файлов и внутренних bitmap‑источников, формируя единый поток `UBitmap` для дальнейшей обработки в UBA‑пайплайнах.

---

## EN

## Capture & Sources — capture and image sources (Rdk-CvBasicLib)

### Class diagram

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

**TCapture** — abstract base class for frame capture (cameras/files), managing states `Created / Initialization / Connected / Active / Paused / Disconnected`.

---

### TCapture / TCaptureCamera / TCaptureCameraIp / TCaptureImageSequence

#### UML (main properties and methods)

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

#### Sequence diagram (typical cycle captureа)

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

#### State diagram TCapture

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

#### Inputs/outputs and properties

- **Output**: `OutputImage` — current frame `UBitmap`.  
- **Main parameters**:
  - `DesiredFps`, `CaptureTimeout`, `CloseTimeout`, `ReconnectTimeout`, `RestartMode`.  
  - `DesiredWidth`, `DesiredHeight`, `DesiredResolutionFlag`.  
  - `EnableCapture`, `Paused`, `FlipX`, `FlipY`, `RotationAngle`, `FixedRotation`.
- **State**:
  - `CaptureState`, `NumFrames`, `CaptureFps`, `RealFps`, `FramePosition`, `FrameTime`.
- **TCaptureCameraIp**:
  - `Address`, `Login`, `Password` — IP camera connection parameters.
- **TCaptureImageSequence**:
  - `Path`, `IsPathRelativeFromConfig`, `RepeatFlag`, `CaptureDelay`.  

#### Usage example (C++)

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

#### UML (main relationships)

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

#### Sequence diagram (example for UBASourceFile)

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

#### Inputs/outputs and properties

- **UBASource**
  - `Input` / `Output` (`UBitmap`) — base source that can forward or override data.
- **UBASourceFile**
  - `FileName` — path to a single file; `IsLoad()` — successful load indicator.
- **UBASourceMultiFile**
  - `FileNames` — path list; dynamically creates output properties `Output[i]` for each file.
- **UBABitmapSource / UBABitmapSourceSimple / UBABitmapSourceFile**
  - `SourceParamaters` — bitmap generation/storage parameters.  
  - `Output` — resulting frame.
- **UBASourceFreezeFrame**
  - `FreezeFlag` — when `true`, holds the last output frame even if the input changes.

#### XML configuration examples

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

### Component diagram (capture and sources in pipeline)

```mermaid
graph LR
    Cam[TCapture*] --> Pre[UBA Preprocessing]
    Src[UBASource*/UBABitmapSource*] --> Pre
    FileSrc[UBASourceFile/UBASourceMultiFile] --> Pre
    Freeze[UBASourceFreezeFrame] --> Pre
```

Sources and capture components form the entry point of most configurations в `Bin/Configs/*`, feeding `UBitmap` frames into UBA pipelines (`ColorConvert`, `Crop`, `Reduce`, фон, binarization, detection, etc.).
