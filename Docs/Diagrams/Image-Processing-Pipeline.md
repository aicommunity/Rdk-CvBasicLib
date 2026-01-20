# Пайплайн обработки изображений

## RU

### Типичный пайплайн обработки

```mermaid
flowchart LR
    Capture["Захват (TCaptureCamera)"]
    Convert["Конвертация (UBAColorConvert)"]
    Resize["Изменение_размера (UBAResize)"]
    Process["Обработка (UBABackground)"]
    Output[Выход]
    
    Capture --> Convert
    Convert --> Resize
    Resize --> Process
    Process --> Output
```

### Последовательность обработки

```mermaid
sequenceDiagram
    participant Camera as TCaptureCamera
    participant Convert as UBAColorConvert
    participant Resize as UBAResize
    participant Process as UBABackground
    
    Camera->>Camera: CaptureFrame()
    Camera->>Convert: OutputFrame
    Convert->>Convert: ConvertToGrayscale()
    Convert->>Resize: OutputImage
    Resize->>Resize: Resize(640x480)
    Resize->>Process: OutputImage
    Process->>Process: SubtractBackground()
    Process->>Process: ProcessedImage
```

---

## EN

### Typical Processing Pipeline

```mermaid
flowchart LR
    Capture_EN["Capture (TCaptureCamera)"]
    Convert_EN["Convert (UBAColorConvert)"]
    Resize_EN["Resize (UBAResize)"]
    Process_EN["Process (UBABackground)"]
    Output_EN[Output]
    
    Capture_EN --> Convert_EN
    Convert_EN --> Resize_EN
    Resize_EN --> Process_EN
    Process_EN --> Output_EN
```

The diagram represents a typical computer vision chain: acquire frame → convert colors → resize → apply processing/background operations → produce output image or mask.

### Processing Sequence

The sequence diagram in the RU section shows the per-frame execution order and data handoff between components through their output/input properties.
