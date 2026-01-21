## Detectors / Segmentators / Savers — детекторы, сегментаторы и сохранение результатов (Rdk-CvBasicLib)

**Классы**: `UDetectorBase`, `UDetResSaverPVOC`, `USegmentatorBase`, `UClassifierBase`, `UClassifierResSaver` и связанные UBA-компоненты визуализации (`UBShowRect`, `ShowObjectsSimple`, `TLabelingSimple`).  
Они реализуют базовые интерфейсы детекции/сегментации и сохранение/отображение результатов.

### Классы

```mermaid
classDiagram
    UComponent <|-- UClassifierBase
    UComponent <|-- UDetectorBase
    UComponent <|-- USegmentatorBase
    UComponent <|-- UClassifierResSaver
    UComponent <|-- UDetResSaverPVOC
    UComponent <|-- UBShowRect
    UComponent <|-- ShowObjectsSimple
    UComponent <|-- TLabelingSimple
```

### Входы/выходы
- `UDetectorBase` / `USegmentatorBase`: вход — изображения/признаки; выход — bounding boxes, маски, классы.
- `UClassifierResSaver` / `UDetResSaverPVOC`: вход — результаты; выход — файлы результатов (например, формат PASCAL VOC).
- Визуализация: вход — объекты/маски; выход — размеченное изображение.

### Storage-инстансы
- Конфигурируются путями к файлам результатов, параметрами визуализации и типами детектируемых объектов.

```mermaid
flowchart LR
    img[UBitmap] --> det[UDetectorBase]
    det --> saver[UDetResSaverPVOC]
    det --> vis[UBShowRect]
```

Пояснение: блок-схема показывает поток данных/сигналов (входы → компонент → выходы).

---

## Detectors / Segmentators / Savers (Rdk-CvBasicLib)

**Classes**: base detector/segmentator/classifier and result saver components forming the output end of CV pipelines.

