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

### Пример 4: Комплексный конвейер обработки видео

```cpp
// Создание полного конвейера обработки видео с камеры
auto capture = storage->CreateComponent<TCaptureCamera>();
capture->CameraIndex = 0;
capture->Width = 1920;
capture->Height = 1080;
capture->Build();

// Предобработка изображения
auto colorConvert = storage->CreateComponent<UBAColorConvert>();
colorConvert->ColorSpace = CS_GRAY;
colorConvert->Build();

auto resize = storage->CreateComponent<UBAResize>();
resize->Width = 640;
resize->Height = 480;
resize->Build();

auto blur = storage->CreateComponent<UBABlur>();
blur->KernelSize = 5;
blur->Build();

// Детекция объектов
auto detector = storage->CreateComponent<UBAObjectDetector>();
detector->ConfidenceThreshold = 0.5;
detector->Build();

// Связывание компонентов
colorConvert->InputImage = capture->OutputFrame;
resize->InputImage = colorConvert->OutputImage;
blur->InputImage = resize->OutputImage;
detector->InputImage = blur->OutputImage;

// Обработка в цикле
while (true) {
    capture->Calculate();
    colorConvert->Calculate();
    resize->Calculate();
    blur->Calculate();
    detector->Calculate();
    
    // Обработка результатов детекции
    for (const auto& obj : detector->DetectedObjects) {
        std::cout << "Объект: " << obj.ClassName 
                  << ", Уверенность: " << obj.Confidence << std::endl;
    }
    
    // Задержка для контроля FPS
    std::this_thread::sleep_for(std::chrono::milliseconds(33)); // ~30 FPS
}
```

### Пример 5: Обработка изображений с обработкой ошибок

```cpp
// Безопасная обработка изображений с проверкой ошибок
auto imageSource = storage->CreateComponent<UBABitmapSourceFile>();
imageSource->FileName = "input.jpg";
imageSource->Build();

try {
    // Загрузка изображения
    if (!imageSource->LoadImage()) {
        throw std::runtime_error("Не удалось загрузить изображение");
    }
    
    auto inputImage = imageSource->OutputImage;
    
    // Проверка валидности изображения
    if (inputImage.IsEmpty()) {
        throw std::runtime_error("Изображение пустое");
    }
    
    // Обработка изображения
    auto processor = storage->CreateComponent<UBAResize>();
    processor->InputImage = inputImage;
    processor->Width = 800;
    processor->Height = 600;
    processor->Build();
    
    processor->Calculate();
    
    if (processor->OutputImage.IsEmpty()) {
        throw std::runtime_error("Ошибка обработки изображения");
    }
    
    // Сохранение результата
    auto imageSink = storage->CreateComponent<UBABitmapSinkFile>();
    imageSink->InputImage = processor->OutputImage;
    imageSink->FileName = "output.jpg";
    imageSink->Build();
    imageSink->SaveImage();
    
} catch (const RDK::UException& e) {
    std::cerr << "Ошибка обработки изображения: " << e.what() << std::endl;
    // Обработка ошибки, например, использование изображения по умолчанию
}
```

### Пример 6: Оптимизированная обработка видео потока

```cpp
// Оптимизированная обработка видео с кэшированием и буферизацией
auto capture = storage->CreateComponent<TCaptureCamera>();
capture->CameraIndex = 0;
capture->Build();

// Предобработка (выполняется один раз)
auto preprocessor = storage->CreateComponent<UBAColorConvert>();
preprocessor->ColorSpace = CS_GRAY;
preprocessor->Build();

// Детектор (переиспользуется для каждого кадра)
auto detector = storage->CreateComponent<UBAObjectDetector>();
detector->Build();

// Буфер для промежуточных результатов
UBitmap processedFrame;
bool frameProcessed = false;

// Обработка с пропуском кадров для производительности
int frameSkip = 2; // Обрабатывать каждый 3-й кадр
int frameCounter = 0;

while (true) {
    capture->Calculate();
    frameCounter++;
    
    // Пропуск кадров для оптимизации
    if (frameCounter % (frameSkip + 1) != 0) {
        continue;
    }
    
    // Предобработка
    preprocessor->InputImage = capture->OutputFrame;
    preprocessor->Calculate();
    
    // Детекция
    detector->InputImage = preprocessor->OutputImage;
    detector->Calculate();
    
    // Обработка результатов
    if (!detector->DetectedObjects.empty()) {
        std::cout << "Обнаружено объектов: " 
                  << detector->DetectedObjects.size() << std::endl;
    }
}
```

### Пример 7: Интеграция с ML библиотеками

```cpp
// Использование CvBasicLib для предобработки перед ML
auto capture = storage->CreateComponent<TCaptureCamera>();
capture->CameraIndex = 0;
capture->Build();

// Предобработка для ML модели
auto resize = storage->CreateComponent<UBAResize>();
resize->Width = 224;  // Стандартный размер для многих ML моделей
resize->Height = 224;
resize->Build();

auto normalize = storage->CreateComponent<UBANormalize>();
normalize->NormalizationType = NT_MeanStd;
normalize->Mean = 0.485;
normalize->StdDev = 0.229;
normalize->Build();

// Связывание компонентов
resize->InputImage = capture->OutputFrame;
normalize->InputImage = resize->OutputImage;

// Обработка кадра
capture->Calculate();
resize->Calculate();
normalize->Calculate();

// Теперь нормализованное изображение готово для ML модели
// Historical note: optional ML libs are deprecated — see Docs/Libraries/Optional-ML-Libraries.md
auto preprocessedImage = normalize->OutputImage;

// Использование в ML компоненте
// auto classifier = storage->CreateComponent<UTfClassifier>();
// classifier->InputImage = preprocessedImage;
// classifier->Calculate();
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

### Example 4: Complex Video Processing Pipeline

```cpp
// Creating complete video processing pipeline from camera
auto capture = storage->CreateComponent<TCaptureCamera>();
capture->CameraIndex = 0;
capture->Width = 1920;
capture->Height = 1080;
capture->Build();

// Image preprocessing
auto colorConvert = storage->CreateComponent<UBAColorConvert>();
colorConvert->ColorSpace = CS_GRAY;
colorConvert->Build();

auto resize = storage->CreateComponent<UBAResize>();
resize->Width = 640;
resize->Height = 480;
resize->Build();

auto blur = storage->CreateComponent<UBABlur>();
blur->KernelSize = 5;
blur->Build();

// Object detection
auto detector = storage->CreateComponent<UBAObjectDetector>();
detector->ConfidenceThreshold = 0.5;
detector->Build();

// Linking components
colorConvert->InputImage = capture->OutputFrame;
resize->InputImage = colorConvert->OutputImage;
blur->InputImage = resize->OutputImage;
detector->InputImage = blur->OutputImage;

// Processing loop
while (true) {
    capture->Calculate();
    colorConvert->Calculate();
    resize->Calculate();
    blur->Calculate();
    detector->Calculate();
    
    // Processing detection results
    for (const auto& obj : detector->DetectedObjects) {
        std::cout << "Object: " << obj.ClassName 
                  << ", Confidence: " << obj.Confidence << std::endl;
    }
    
    // Delay for FPS control
    std::this_thread::sleep_for(std::chrono::milliseconds(33)); // ~30 FPS
}
```

### Example 5: Image Processing with Error Handling

```cpp
// Safe image processing with error checking
auto imageSource = storage->CreateComponent<UBABitmapSourceFile>();
imageSource->FileName = "input.jpg";
imageSource->Build();

try {
    // Loading image
    if (!imageSource->LoadImage()) {
        throw std::runtime_error("Failed to load image");
    }
    
    auto inputImage = imageSource->OutputImage;
    
    // Validating image
    if (inputImage.IsEmpty()) {
        throw std::runtime_error("Image is empty");
    }
    
    // Processing image
    auto processor = storage->CreateComponent<UBAResize>();
    processor->InputImage = inputImage;
    processor->Width = 800;
    processor->Height = 600;
    processor->Build();
    
    processor->Calculate();
    
    if (processor->OutputImage.IsEmpty()) {
        throw std::runtime_error("Image processing error");
    }
    
    // Saving result
    auto imageSink = storage->CreateComponent<UBABitmapSinkFile>();
    imageSink->InputImage = processor->OutputImage;
    imageSink->FileName = "output.jpg";
    imageSink->Build();
    imageSink->SaveImage();
    
} catch (const RDK::UException& e) {
    std::cerr << "Image processing error: " << e.what() << std::endl;
    // Error handling, e.g., using default image
}
```

### Example 6: Optimized Video Stream Processing

```cpp
// Optimized video processing with caching and buffering
auto capture = storage->CreateComponent<TCaptureCamera>();
capture->CameraIndex = 0;
capture->Build();

// Preprocessing (executed once)
auto preprocessor = storage->CreateComponent<UBAColorConvert>();
preprocessor->ColorSpace = CS_GRAY;
preprocessor->Build();

// Detector (reused for each frame)
auto detector = storage->CreateComponent<UBAObjectDetector>();
detector->Build();

// Buffer for intermediate results
UBitmap processedFrame;
bool frameProcessed = false;

// Processing with frame skipping for performance
int frameSkip = 2; // Process every 3rd frame
int frameCounter = 0;

while (true) {
    capture->Calculate();
    frameCounter++;
    
    // Frame skipping for optimization
    if (frameCounter % (frameSkip + 1) != 0) {
        continue;
    }
    
    // Preprocessing
    preprocessor->InputImage = capture->OutputFrame;
    preprocessor->Calculate();
    
    // Detection
    detector->InputImage = preprocessor->OutputImage;
    detector->Calculate();
    
    // Processing results
    if (!detector->DetectedObjects.empty()) {
        std::cout << "Objects detected: " 
                  << detector->DetectedObjects.size() << std::endl;
    }
}
```

### Example 7: Integration with ML Libraries

```cpp
// Using CvBasicLib for preprocessing before ML
auto capture = storage->CreateComponent<TCaptureCamera>();
capture->CameraIndex = 0;
capture->Build();

// Preprocessing for ML model
auto resize = storage->CreateComponent<UBAResize>();
resize->Width = 224;  // Standard size for many ML models
resize->Height = 224;
resize->Build();

auto normalize = storage->CreateComponent<UBANormalize>();
normalize->NormalizationType = NT_MeanStd;
normalize->Mean = 0.485;
normalize->StdDev = 0.229;
normalize->Build();

// Linking components
resize->InputImage = capture->OutputFrame;
normalize->InputImage = resize->OutputImage;

// Processing frame
capture->Calculate();
resize->Calculate();
normalize->Calculate();

// Now normalized image is ready for ML model
// Historical: optional ML libs are deprecated — see Docs/Libraries/Optional-ML-Libraries.md
auto preprocessedImage = normalize->OutputImage;

// Using in ML component
// auto classifier = storage->CreateComponent<UTfClassifier>();
// classifier->InputImage = preprocessedImage;
// classifier->Calculate();
```

### Integration with Rdk
