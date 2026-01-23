# Диаграммы Rdk-CvBasicLib

## RU

### Назначение

Диаграммы структуры библиотеки Rdk-CvBasicLib и основных последовательностей обработки изображений.

### Диаграммы

- [Image-Processing-Pipeline.md](Image-Processing-Pipeline.md) - пайплайн обработки изображений
- [Object-Detection-Flow.md](Object-Detection-Flow.md) - поток детекции объектов

### Соглашения по UML (Mermaid)

- **Диаграммы классов** (`classDiagram`)  
  - Показывают иерархию наследования (`UNet <|-- MyComponent`) и ключевые свойства/методы.  
  - В компонентах Rdk-CvBasicLib всегда отражаются методы жизненного цикла: `New`, `ADefault`, `ABuild`, `AReset`, `ACalculate`.

- **Диаграммы последовательности** (`sequenceDiagram`)  
  - Описывают жизненный цикл компонента: создание, инициализация, сборка, многократные вызовы `ACalculate`, сброс.  
  - Участники: `UStorage`, сам компонент, источники (`TCapture`/`UBASource*`) и следующие компоненты пайплайна.

- **Диаграммы состояний** (`stateDiagram-v2`)  
  - Используются для компонентов с явными состояниями (`Uninitialized`, `Defaulted`, `Built`, `Ready`, `Calculating`, `Resetting`).  
  - Переходы привязаны к вызовам `ADefault`, `ABuild`, `ACalculate`, `AReset`.

- **Диаграммы активности** (`flowchart TD/LR`)  
  - Раскрывают алгоритм внутри `ACalculate`/`ABuild`: поток данных, ветвления (`if/else`) и циклы.  
  - Узлы описывают шаги обработки (чтение входных свойств, вычисление, запись выходов).

- **Диаграммы компонентов** (`graph TB/LR`)  
  - Показывают связи между компонентами (источники, обработчики, детекторы, классификаторы, сохранение результатов).  
  - Узлы — компоненты (`TCapture*`, `UBA*`, `UDetectorBase`, `UCR*` и т.п.), рёбра — поток данных/сигналов.

---

## EN

### Purpose

Diagrams of Rdk-CvBasicLib library structure and main image processing sequences.

### Diagrams

- [Image-Processing-Pipeline.md](Image-Processing-Pipeline.md) - image processing pipeline
- [Object-Detection-Flow.md](Object-Detection-Flow.md) - object detection flow
