# Примеры использования Rdk-CvBasicLib

## RU

### Пример 1: Захват с камеры

```cpp
// Создание компонента захвата с камеры
auto capture = storage->CreateComponent<TCaptureCamera>();
capture->CameraIndex = 0;
capture->Build();

// Захват кадра
capture->Calculate();
auto frame = capture->OutputFrame;
```

### Пример 2: Обработка изображения

```cpp
// Конвертация в grayscale
auto colorConvert = storage->CreateComponent<UBAColorConvert>();
colorConvert->InputImage = inputImage;
colorConvert->ColorSpace = CS_GRAY;
colorConvert->Build();
colorConvert->Calculate();

// Изменение размера
auto resize = storage->CreateComponent<UBAResize>();
resize->InputImage = colorConvert->OutputImage;
resize->Width = 640;
resize->Height = 480;
resize->Build();
resize->Calculate();
```

### Пример 3: Детекция объектов

```cpp
// Создание детектора
auto detector = storage->CreateComponent<UBAObjectDetector>();
detector->InputImage = processedImage;
detector->Build();

// Детекция
detector->Calculate();
auto objects = detector->DetectedObjects;
```

### Интеграция с Rdk

```cpp
bool RdkLoadPredefinedLibraries(std::list<ULibrary*> &libs_list)
{
    libs_list.push_back(&RDK::CvBasicLibrary);
    // ...
}
```

---

## EN

### Example 1: Camera Capture

```cpp
// Creating camera capture component
auto capture = storage->CreateComponent<TCaptureCamera>();
capture->CameraIndex = 0;
capture->Build();

// Capturing frame
capture->Calculate();
auto frame = capture->OutputFrame;
```

### Example 2: Image Processing

```cpp
// Convert to grayscale
auto colorConvert = storage->CreateComponent<UBAColorConvert>();
colorConvert->InputImage = inputImage;
colorConvert->ColorSpace = CS_GRAY;
colorConvert->Build();
colorConvert->Calculate();

// Resize
auto resize = storage->CreateComponent<UBAResize>();
resize->InputImage = colorConvert->OutputImage;
resize->Width = 640;
resize->Height = 480;
resize->Build();
resize->Calculate();
```

### Example 3: Object Detection

```cpp
// Creating detector
auto detector = storage->CreateComponent<UBAObjectDetector>();
detector->InputImage = processedImage;
detector->Build();

// Detection
detector->Calculate();
auto objects = detector->DetectedObjects;
```

### Integration with Rdk
