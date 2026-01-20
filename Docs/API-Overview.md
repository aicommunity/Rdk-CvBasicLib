# Обзор API Rdk-CvBasicLib

## RU

### Основные классы

#### CvBasicLib

Главный класс библиотеки, наследник `ULibrary`.

#### TCapture

Базовый класс для захвата видео и изображений.

**Основные свойства:**
- `OutputFrame` - выходной кадр
- `IsOpened` - статус открытия источника

#### TCaptureCamera

Захват с камеры.

**Основные свойства:**
- `CameraIndex` - индекс камеры
- `Resolution` - разрешение

#### UBAColorConvert

Конвертация цветовых пространств.

**Основные свойства:**
- `InputImage` - входное изображение
- `ColorSpace` - целевое цветовое пространство
- `OutputImage` - выходное изображение

#### UBAObjectDetector

Детектор объектов.

**Основные свойства:**
- `InputImage` - входное изображение
- `DetectedObjects` - обнаруженные объекты

#### UCRClassifier

Базовый классификатор изображений.

**Основные свойства:**
- `InputImage` - входное изображение
- `ClassLabel` - метка класса
- `Confidence` - уверенность классификации

### См. также

- [Reports/04-Rdk-CvBasicLib.md](../../../Reports/04-Rdk-CvBasicLib.md) - детальное описание
- Исходный код: `Libraries/Rdk-CvBasicLib/Core/`

---

## EN

### Main Classes

#### CvBasicLib

Main library class, inherits from `ULibrary`.

#### TCapture

Base class for video and image capture.

**Main Properties:**
- `OutputFrame` - output frame
- `IsOpened` - source open status

#### TCaptureCamera

Camera capture.

**Main Properties:**
- `CameraIndex` - camera index
- `Resolution` - resolution

#### UBAColorConvert

Color space conversion.

**Main Properties:**
- `InputImage` - input image
- `ColorSpace` - target color space
- `OutputImage` - output image

#### UBAObjectDetector

Object detector.

**Main Properties:**
- `InputImage` - input image
- `DetectedObjects` - detected objects

#### UCRClassifier

Base image classifier.

**Main Properties:**
- `InputImage` - input image
- `ClassLabel` - class label
- `Confidence` - classification confidence

### See Also

- [Reports/04-Rdk-CvBasicLib.md](../../../Reports/04-Rdk-CvBasicLib.md) - detailed description
- Source code: `Libraries/Rdk-CvBasicLib/Core/`
