/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAMovingDetectorH
#define UBAMovingDetectorH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// Базовый класс детектирования зон обнаружения движения
class RDK_LIB_TYPE UBAMovingDetector: public UNet
{
public: // Параметры
/// Число изображений в истории
int HistorySize;

protected: // Данные
/// Текущее входное изображение
UPropertyInputData<UBitmap, UBAMovingDetector> Input;

/// Выходные данные
UBRect* MovedObjects;

/// Обработанные изображения
UBitmap* LocalContrastedImages;

/// Текущий размер истории
int CurrentHistorySize;

/// Текущий первый кадр истории
int CurrentFirstHistoryIndex;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBAMovingDetector(void);
~UBAMovingDetector(void);
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
/// Число изображений в истории
int GetHistorySize(void) const;
bool SetHistorySize(int value);
// --------------------------

// --------------------------
// Методы доступа к данным
// --------------------------
/// Текущее входное изображение
const UBitmap* GetInputData(void) const;

/// Выходные данные
const UBRect* GetMovedObjects(void) const;

/// Обработанные изображения
const UBitmap* GetLocalContrastedImages(void) const;

/// Текущий размер истории
int GetCurrentHistorySize(void) const;

/// Текущий первый кадр истории
int GetCurrentFirstHistoryIndex(void) const;
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
/// Сдвигает историю
void HistoryShift(void);

/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild(void);

/// Сброс процесса счета.
virtual bool AReset(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFCDefault(void)=0;

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFCBuild(void)=0;

/// Сброс процесса счета.
virtual bool AFCReset(void)=0;

/// Выполняет расчет этого объекта
virtual bool AFCCalculate(void)=0;
// --------------------------
};

// Поиск объектов в ночных условиях
// Алгоритм взят из статьи
// "A real-time object detecting and tracking system for outdoor night surveillance"
// Kaiqi Huang, Liangsheng Wang, Tieniu Tan, Steve Maybank
class RDK_LIB_TYPE UBANightMovingDetector: public UBAMovingDetector
{
public: // Параметры
/// Размер блока изображения
int BlockWidth, BlockHeight;

/// Процент вычисления адаптивного порога
double AdaptiveThresholdPercent;

/// Процент пикселей, предолевших адаптивный порог,
/// дающий обнаружение
double MoveDetectionPercent;

/// Пороги
double T1;

/// Коэффициент расстояния между кадрами
double Tr;

/// Режим определения движения
/// 0 - по гистограмме
/// 1 - по критерию псевдоконстраста abs(a-b)/max(a,b)
int MovingDetectionMode;

/// Диапазон анализа гистограммы
int HistLeftRange, HistRightRange;

/// Режим формирования движущегося кадра
/// 0 - Отдельные пиксели
/// 1 - Блоки
int MovingFrameMode;

protected: // Данные
/// Число блоков
int NumBlocks;

int XBlocks,YBlocks;

/// Массив локальных контрастов
double* CL;

/// Массив средних
double* ML;

/// Массив СКО
double* SigmaL;

/// Изображение разностного кадра
UBitmap DiffImage;

/// Изображение с обнаружением движущихся объектов
UBitmap MovedImage;

/// Гистограмма
UBHistogram Histogram;

/// Сетка контрастных объектов
UBRect* ContrastGrid;

/// Сетка движущихся объектов
UBRect* MovedGrid;


protected: // Общие временные переменные
/// Размер изображения
int Width,Height;

protected: // Временные переменные для вычисления локального контраста
protected: // Временные переменные для вычисления карты локальной зависимости
/// Данные карты
double* MCm;
double* ICm;

/// Порог отсева малых ложных изменений
double* T;
double TT;


protected: // Временные переменные для обнаружения движущихся объектов
NCC2D Correlation;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBANightMovingDetector(void);
~UBANightMovingDetector(void);
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
/// Размер блока изображения
int GetBlockWidth(void) const;
bool SetBlockWidth(int value);
int GetBlockHeight(void) const;
bool SetBlockHeight(int value);

/// Режим определения движения
int GetMovingDetectionMode(void) const;
bool SetMovingDetectionMode(int value);

/// Диапазон анализа гистограммы
int GetHistLeftRange(void) const;
bool SetHistLeftRange(int value);
int GetHistRightRange(void) const;
bool SetHistRightRange(int value);

/// Режим формирования движущегося кадра
int GetMovingFrameMode(void) const;
bool SetMovingFrameMode(int value);
// --------------------------

// --------------------------
// Методы доступа к данным
// --------------------------
/// Изображение с обнаружением движущихся объектов
const UBitmap& GetMovedImage(void) const;

/// Число блоков
int GetNumBlocks(void) const;

/// Массив локальных контрастов
const double* GetCL(void) const;

/// Массив средних
const double* GetML(void) const;

/// Массив СКО
const double* GetSigmaL(void) const;

/// Изображение разностного кадра
const UBitmap& GetDiffImage(void) const;

/// Гистограмма
const UBHistogram& GetHistogram(void) const;

/// Сетка контрастных объектов
const UBRect* GetContrastGrid(void) const;
const UBRect& GetContrastGrid(int i) const;

/// Сетка движущихся объектов
const UBRect* GetMovedGrid(void) const;
const UBRect& GetMovedGrid(int i) const;
// --------------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
UBANightMovingDetector* New(void);
// ---------------------

// ---------------------
// Скрытые методы счета
// ---------------------
protected:
/// Установка разрешения входных изображений
bool SetRes(int width, int height);

/// Вычисление локального контраста
virtual bool CalcLocalContrasting(void);

/// Построение карты локальной зависимости
virtual bool CalcLocalMap(void);

/// Обнаружение движущихся объектов
virtual bool CalcMovedObjects(void);

/// Обнаружение движущихся объектов на основе нормировки разности
virtual bool CalcNormalMovedObjects(void);

/// Расчет адаптивного порога
virtual bool CalcAdaptiveThreshold(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFCDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFCBuild(void);

/// Сброс процесса счета.
virtual bool AFCReset(void);

/// Выполняет расчет этого объекта
virtual bool AFCCalculate(void);
// --------------------------

};


//
class RDK_LIB_TYPE UBACollateMovingDetector: public UBAMovingDetector
{
public:
/// Изображение разностного кадра
UBitmap DiffImage;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBACollateMovingDetector(void);
~UBACollateMovingDetector(void);
// --------------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
UBACollateMovingDetector* New(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFCDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFCBuild(void);

/// Сброс процесса счета.
virtual bool AFCReset(void);

/// Выполняет расчет этого объекта
virtual bool AFCCalculate(void);
// --------------------------
};

}

#endif
