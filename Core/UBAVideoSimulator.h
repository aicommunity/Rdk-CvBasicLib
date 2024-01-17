/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAVIDEO_SIMULATOR_H
#define UBAVIDEO_SIMULATOR_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

struct RDK_LIB_TYPE UBVSObject
{
int ObjectX,ObjectY;
int ObjectWidth,ObjectHeight;
int XShift,YShift;
UColorT Color;
UColorT Color2;
UColorT Color3;
UColorT Color4;
bool Visible;
int MovingDirection;

// 0 - однотонный объект
// 1 - с вертикальным градиентом
int Mode;

public:
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBVSObject(void);
// --------------------------
bool operator == (const UBVSObject &copy) const;

bool operator != (const UBVSObject &copy) const;
};

// struct UBVSObject
RDK_LIB_TYPE USerStorageXML& operator << (USerStorageXML& storage, const UBVSObject &data);
RDK_LIB_TYPE USerStorageXML& operator >> (USerStorageXML& storage, UBVSObject &data); 
RDK_LIB_TYPE USerStorageBinary& operator << (USerStorageBinary& storage, const UBVSObject &data);
RDK_LIB_TYPE USerStorageBinary& operator >> (USerStorageBinary& storage, UBVSObject &data);  

/// Базовый класс симуляции сцен
class RDK_LIB_TYPE UBAVideoSimulator: public UNet
{
public: // Параметры
/// Режим оформления фона эмулятора
/// 0 - не создавать фон
/// 1 - однотонный фон с BgMode
UProperty<int,UBAVideoSimulator, ptPubParameter> BgMode;

/// Цвет фона
UProperty<UColorT ,UBAVideoSimulator, ptPubParameter> BgColor;

/// Флаг скрытия всех объектов с изображения
UProperty<bool,UBAVideoSimulator, ptPubParameter> HideAllFlag;

/// Число объектов
UProperty<int,UBAVideoSimulator, ptPubParameter> NumObjects;

/// Граница рабочей области
UProperty<UBRect,UBAVideoSimulator, ptPubParameter> WorkArea;

/// Включить отображение сетки
ULProperty<bool, UBAVideoSimulator> ShowGrid;

/// Шаг отрисовки сетки (в пикселях)
ULProperty<int, UBAVideoSimulator> PixelGridStep;

/// Цвет сетки
ULProperty<UColorT, UBAVideoSimulator> PixelGridColor;

/// Толщина линии сетки
ULProperty<int, UBAVideoSimulator> PixelGridWidth;

protected: // Входные и выходные данные
UPropertyInputData<UBitmap, UBAVideoSimulator, ptPubInput | ptState> InputData;

/// Входное изображение
UPropertyInputData<UBitmap, UBAVideoSimulator> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBAVideoSimulator> Output;

/// Массив объектов
UProperty<std::vector<UBVSObject>, UBAVideoSimulator, ptPubParameter> Objects;

protected: // Данные
/// Текущий управляемый объект
int CurrentObjectIndex;

protected: // Временные переменные
UAGraphics *Graphics;

UBitmap Canvas;


public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAVideoSimulator(void);
virtual ~UBAVideoSimulator(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
/// Режим оформления фона эмулятора
/// (не используется)
const int& GetBgMode(void) const;
bool SetBgMode(const int &value);

/// Флаг скрытия всех объектов с изображения
const bool& GetHideAllFlag(void) const;
bool SetHideAllFlag(const bool &value);

/// Граница рабочей области
const UBRect& GetWorkArea(void) const;
bool SetWorkArea(const UBRect &value);
// ---------------------

// ---------------------
// Методы управления данными
// ---------------------
/// Удаляет все объекты
void ClearObjects(void);

/// Число объектов
const int& GetNumObjects(void) const;
bool SetNumObjects(const int &value);

/// Массив объектов
const UBVSObject& GetObjectData(int index) const;
bool SetObjectData(int index, const UBVSObject &data);
const UBVSObject& GetCurrentObjectData(void) const;
bool SetCurrentObjectData(const UBVSObject &data);

/// Текущий управляемый объект
int GetCurrentObjectIndex(void) const;
bool SetCurrentObjectIndex(int value);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AReset(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFSDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFSBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFSReset(void);

/// Выполняет расчет этого объекта
virtual bool AFSCalculate(void);
// --------------------------
};

/// Осуществляет симуляцию простых двумерных сцен
class RDK_LIB_TYPE UBAVideoSimulatorSimple: public UBAVideoSimulator
{
protected: // Параметры


public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAVideoSimulatorSimple(void);
virtual ~UBAVideoSimulatorSimple(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBAVideoSimulatorSimple* New(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
// --------------------------
protected:
void CreateFillBackground(UBitmap &canvas);

/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFSDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFSBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFSReset(void);

/// Выполняет расчет этого объекта
virtual bool AFSCalculate(void);
// --------------------------
};

/// Осуществляет симуляцию простых двумерных сцен и создает еще один выход с верным бинарным кадром
class RDK_LIB_TYPE UBAVideoSimulatorSimpleBin: public UBAVideoSimulator
{
protected: // Параметры
    /// Выходное бинкарное изображение
    UPropertyOutputData<UBitmap, UBAVideoSimulatorSimpleBin> BinarOutput;
    ///количесво первых кадров, считающихся фоном
    ULProperty<int, UBAVideoSimulatorSimpleBin> countFirstCleanBgFrame;
    ///счетчик того, что выше
    int nCounterBG;
    UBitmap CanvasBin;


public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAVideoSimulatorSimpleBin(void);
virtual ~UBAVideoSimulatorSimpleBin(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBAVideoSimulatorSimpleBin* New(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
// --------------------------
protected:
void CreateFillBackground(UBitmap &canvas);


///Функцмия рисования
void DrawSimple(UBitmap &canvas, int isBin);

/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFSDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFSBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFSReset(void);

/// Выполняет расчет этого объекта
virtual bool AFSCalculate(void);
// --------------------------
};
}

#endif

