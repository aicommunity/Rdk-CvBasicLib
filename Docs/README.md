# Rdk-CvBasicLib - Документация

## RU

### Назначение

**Rdk-CvBasicLib** предоставляет компоненты компьютерного зрения на базе OpenCV. Библиотека включает компоненты для захвата видео, обработки изображений, детекции объектов, классификации и сегментации.

### Краткий обзор

Библиотека включает компоненты для:
- Захвата видео и изображений (камеры, IP-камеры, файлы)
- Обработки изображений (фильтры, преобразования, морфология)
- Детекции объектов
- Классификации изображений
- Сегментации изображений

### Быстрый старт

#### Захват видео с камеры

```cpp
// Создание компонента захвата
auto capture = storage->CreateComponent<UCapture>("Capture");
capture->DeviceIndex = 0;
capture->Default();
capture->Build();

// Захват кадра
capture->Calculate();
auto frame = capture->OutputImage();
```

#### Обработка изображения

```cpp
// Создание фильтра
auto filter = storage->CreateComponent<UImageFilter>("Filter");
filter->InputImage.AttachTo(&capture->OutputImage);
filter->FilterType = "Gaussian";
filter->Build();
filter->Calculate();
```

### Связь с корневой документацией

Для обзорной информации см. корневую документацию проекта:
- `Docs/Libraries/Rdk-CvBasicLib.md` - обзор библиотеки (в корневом репозитории)

### Детальная документация

- [Architecture.md](Architecture.md) - архитектура библиотеки
- [Usage-Examples.md](Usage-Examples.md) - примеры использования
- [API-Overview.md](API-Overview.md) - обзор API
- [Component-Catalog.md](Component-Catalog.md) - каталог компонентов
- [Rdk-CvBasicLib-Overview.md](Rdk-CvBasicLib-Overview.md) - дополнительный обзор библиотеки
- [FAQ.md](FAQ.md) - часто задаваемые вопросы

---

## EN

### Purpose

**Rdk-CvBasicLib** provides computer vision components based on OpenCV. The library includes components for video capture, image processing, object detection, classification, and segmentation.

### Brief Overview

The library includes components for:
- Video and image capture (cameras, IP cameras, files)
- Image processing (filters, transformations, morphology)
- Object detection
- Image classification
- Image segmentation

### Quick Start

#### Capturing Video from Camera

```cpp
// Create capture component
auto capture = storage->CreateComponent<UCapture>("Capture");
capture->DeviceIndex = 0;
capture->Default();
capture->Build();

// Capture frame
capture->Calculate();
auto frame = capture->OutputImage();
```

#### Processing Image

```cpp
// Create filter
auto filter = storage->CreateComponent<UImageFilter>("Filter");
filter->InputImage.AttachTo(&capture->OutputImage);
filter->FilterType = "Gaussian";
filter->Build();
filter->Calculate();
```

### Link to Root Documentation

For overview information see root project documentation:
- `Docs/Libraries/Rdk-CvBasicLib.md` - library overview (in root repository)

### Detailed Documentation

- [Architecture.md](Architecture.md) - library architecture
- [Usage-Examples.md](Usage-Examples.md) - usage examples
- [API-Overview.md](API-Overview.md) - API overview
- [Component-Catalog.md](Component-Catalog.md) - component catalog
- [Rdk-CvBasicLib-Overview.md](Rdk-CvBasicLib-Overview.md) - additional library overview
- [FAQ.md](FAQ.md) - frequently asked questions
