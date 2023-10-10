/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAObjectDetectorH
#define UBAObjectDetectorH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

// Базовый класс масштабирования изображения
class RDK_LIB_TYPE UBAObjectDetector
{
public:
// Тип результата
struct Rect { int X,Y,Width,Height; };

public: // Методы
// ---------------------
// Методы счета
// ---------------------
virtual bool Calculate(const UBitmap& input, Rect* objects)=0;
// ---------------------

// ---------------------
// Операторы
// ---------------------
bool operator () (const UBitmap& input, Rect* objects);
// ---------------------
};

// Поиск объектов в ночных условиях
// Алгоритм взят из статьи
// "A real-time object detecting and tracking system for outdoor night surveillance"
// Kaiqi Huang, Liangsheng Wang, Tieniu Tan, Steve Maybank
class RDK_LIB_TYPE UBANightDetector: public UBAObjectDetector
{
public: // Параметры
// Число изображений в истории
int HistorySize;

// Размер блока изображения
int BlockWidth, BlockHeight;

// Процент вычисления адаптивного порога
double AdaptiveThresholdPercent;

// Процент пикселей, предолевших адаптивный порог,
// дающий обнаружение
double MoveDetectionPercent;

// Пороги
double T1;

// Коэффициент расстояния между кадрами
double Tr;

protected: // Данные
// Размер карты
int MapWidth, MapHeight;



protected: // Общие временные переменные
// Текущее входное изображение
const UBitmap* Input;

// Размер изображения
int Width,Height;

// Обработанные изображения
UBitmap* LocalContrastedImages;

// Текущий размер истории
int CurrentHistorySize;

// Текущий первый кадр истории
int CurrentFirstHistoryIndex;

public: // Временные переменные для вычисления локального контраста
// Число блоков
int NumBlocks;

// Массив локальных контрастов
double* CL;

// Массив средних
double* ML;

// Массив СКО
double* SigmaL;

protected: // Временные переменные для вычисления карты локальной зависимости
// Число элементов карты
int NumMaps;

// Данные карты
double* MCm;
double* ICm;

// Изображение разностного кадра
UBitmap DiffImage;

// Изображение с обнаружением движущихся объектов
UBitmap MovedImage;

// Порог отсева малых ложных изменений
double* T;
double TT;

public:
// Гистограмма
UBHistogram Histogram;

// Сетка контрастных объектов
UBRect* ContrastGrid;

// Сетка движущихся объектов
UBRect* MovedGrid;



protected: // Временные переменные для обнаружения движущихся объектов
NCC2D Correlation;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBANightDetector(void);
~UBANightDetector(void);
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
// Число изображений в истории
int GetHistorySize(void) const;
bool SetHistorySize(int value);
// --------------------------

// --------------------------
// Методы доступа к данным
// --------------------------
// Изображение с обнаружением движущихся объектов
const UBitmap& GetMovedImage(void) const;
// --------------------------

// ---------------------
// Методы счета
// ---------------------
bool Calculate(const UBitmap& input, Rect* objects);
// ---------------------

// ---------------------
// Скрытые методы счета
// ---------------------
protected:
// Вычисление локального контраста
bool CalcLocalContrasting(void);

// Построение карты локальной зависимости
bool CalcLocalMap(void);

// Обнаружение движущихся объектов
bool CalcMovedObjects(void);

// Расчет адаптивного порога
bool CalcAdaptiveThreshold(void);
// ---------------------
};


}

#endif
