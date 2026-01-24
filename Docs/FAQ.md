# FAQ - Rdk-CvBasicLib

## RU

### Общие вопросы

#### Что такое Rdk-CvBasicLib?

Rdk-CvBasicLib - это библиотека компонентов компьютерного зрения на базе OpenCV. Она включает компоненты для захвата видео, обработки изображений, детекции объектов, классификации и сегментации.

#### Какие основные категории компонентов входят в библиотеку?

- **Захват видео и изображений** - камеры, IP-камеры, файлы
- **Обработка изображений** - фильтры, преобразования, морфология
- **Детекция объектов** - различные алгоритмы детекции
- **Классификация изображений** - классификаторы
- **Сегментация** - сегментация изображений

### Захват видео

#### Как захватить видео с камеры?

Используйте компоненты из категории CaptureAndSources:
```cpp
auto capture = storage->CreateComponent<UCapture>("Capture");
capture->DeviceIndex = 0; // Индекс камеры
capture->Build();
```

#### Как захватить видео из файла?

```cpp
auto capture = storage->CreateComponent<UCapture>("Capture");
capture->FileName = "video.mp4";
capture->Build();
```

### Обработка изображений

#### Как применить фильтр к изображению?

Используйте компоненты обработки изображений:
```cpp
auto filter = storage->CreateComponent<UImageFilter>("Filter");
filter->InputImage.AttachTo(&capture->OutputImage);
filter->FilterType = "Gaussian";
filter->Build();
```

#### Как выполнить цветовое преобразование?

Используйте `ColorConvert`:
```cpp
auto converter = storage->CreateComponent<UColorConvert>("Converter");
converter->InputImage.AttachTo(&source->OutputImage);
converter->ConversionType = "BGR2GRAY";
converter->Build();
```

### Детекция объектов

#### Как детектировать объекты на изображении?

Используйте компоненты детекции:
```cpp
auto detector = storage->CreateComponent<UObjectDetector>("Detector");
detector->InputImage.AttachTo(&source->OutputImage);
detector->DetectorType = "HaarCascade";
detector->Build();
detector->Calculate();
auto detections = detector->Detections();
```

### Классификация

#### Как классифицировать изображение?

Используйте компоненты классификации:
```cpp
auto classifier = storage->CreateComponent<UImageClassifier>("Classifier");
classifier->InputImage.AttachTo(&source->OutputImage);
classifier->ModelPath = "model.xml";
classifier->Build();
classifier->Calculate();
auto classLabel = classifier->ClassLabel();
```

### Сегментация

#### Как выполнить сегментацию изображения?

Используйте компоненты сегментации:
```cpp
auto segmentator = storage->CreateComponent<UImageSegmentator>("Segmentator");
segmentator->InputImage.AttachTo(&source->OutputImage);
segmentator->SegmentMethod = "Watershed";
segmentator->Build();
```

### Интеграция с OpenCV

#### Как получить доступ к OpenCV Mat из компонента?

Многие компоненты предоставляют доступ к внутренним OpenCV структурам через свойства или методы. См. [API-Overview.md](API-Overview.md) для деталей.

### Производительность

#### Как оптимизировать обработку изображений?

- Используйте уменьшение разрешения где возможно
- Кэшируйте результаты обработки
- Используйте GPU ускорение (если доступно)
- Минимизируйте копирование изображений

### Устранение неполадок

#### Камера не захватывает видео

- Проверьте индекс устройства
- Убедитесь, что камера доступна
- Проверьте права доступа
- См. логи приложения

#### Изображение не обрабатывается

- Проверьте формат входного изображения
- Убедитесь, что компонент правильно построен
- Проверьте параметры обработки

### Дополнительные ресурсы

- [Architecture.md](Architecture.md) - архитектура библиотеки
- [Component-Catalog.md](Component-Catalog.md) - каталог компонентов
- [Usage-Examples.md](Usage-Examples.md) - примеры использования
- [Rdk-CvBasicLib-Overview.md](Rdk-CvBasicLib-Overview.md) - дополнительный обзор
- [Docs/Troubleshooting/Troubleshooting-Guide.md](../../../Docs/Troubleshooting/Troubleshooting-Guide.md) - общее руководство по устранению неполадок

---

## EN

### General Questions

#### What is Rdk-CvBasicLib?

Rdk-CvBasicLib is a computer vision component library based on OpenCV. It includes components for video capture, image processing, object detection, classification, and segmentation.

#### What are the main component categories in the library?

- **Video and Image Capture** - cameras, IP cameras, files
- **Image Processing** - filters, transformations, morphology
- **Object Detection** - various detection algorithms
- **Image Classification** - classifiers
- **Segmentation** - image segmentation

### Video Capture

#### How do I capture video from a camera?

Use components from CaptureAndSources category:
```cpp
auto capture = storage->CreateComponent<UCapture>("Capture");
capture->DeviceIndex = 0; // Camera index
capture->Build();
```

#### How do I capture video from a file?

```cpp
auto capture = storage->CreateComponent<UCapture>("Capture");
capture->FileName = "video.mp4";
capture->Build();
```

### Image Processing

#### How do I apply a filter to an image?

Use image processing components:
```cpp
auto filter = storage->CreateComponent<UImageFilter>("Filter");
filter->InputImage.AttachTo(&capture->OutputImage);
filter->FilterType = "Gaussian";
filter->Build();
```

#### How do I perform color conversion?

Use `ColorConvert`:
```cpp
auto converter = storage->CreateComponent<UColorConvert>("Converter");
converter->InputImage.AttachTo(&source->OutputImage);
converter->ConversionType = "BGR2GRAY";
converter->Build();
```

### Object Detection

#### How do I detect objects in an image?

Use detection components:
```cpp
auto detector = storage->CreateComponent<UObjectDetector>("Detector");
detector->InputImage.AttachTo(&source->OutputImage);
detector->DetectorType = "HaarCascade";
detector->Build();
detector->Calculate();
auto detections = detector->Detections();
```

### Classification

#### How do I classify an image?

Use classification components:
```cpp
auto classifier = storage->CreateComponent<UImageClassifier>("Classifier");
classifier->InputImage.AttachTo(&source->OutputImage);
classifier->ModelPath = "model.xml";
classifier->Build();
classifier->Calculate();
auto classLabel = classifier->ClassLabel();
```

### Segmentation

#### How do I segment an image?

Use segmentation components:
```cpp
auto segmentator = storage->CreateComponent<UImageSegmentator>("Segmentator");
segmentator->InputImage.AttachTo(&source->OutputImage);
segmentator->SegmentMethod = "Watershed";
segmentator->Build();
```

### OpenCV Integration

#### How do I access OpenCV Mat from a component?

Many components provide access to internal OpenCV structures through properties or methods. See [API-Overview.md](API-Overview.md) for details.

### Performance

#### How do I optimize image processing?

- Use resolution reduction where possible
- Cache processing results
- Use GPU acceleration (if available)
- Minimize image copying

### Troubleshooting

#### Camera doesn't capture video

- Check device index
- Ensure camera is available
- Check access permissions
- See application logs

#### Image doesn't process

- Check input image format
- Ensure component is properly built
- Check processing parameters

### Additional Resources

- [Architecture.md](Architecture.md) - library architecture
- [Component-Catalog.md](Component-Catalog.md) - component catalog
- [Usage-Examples.md](Usage-Examples.md) - usage examples
- [Rdk-CvBasicLib-Overview.md](Rdk-CvBasicLib-Overview.md) - additional overview
- [Docs/Troubleshooting/Troubleshooting-Guide.md](../../../Docs/Troubleshooting/Troubleshooting-Guide.md) - general troubleshooting guide
