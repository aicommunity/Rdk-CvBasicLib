/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBABinarizationH
#define UBABinarizationH
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

/// Базовый класс построения разнострого кадра
class RDK_LIB_TYPE UBABinarization: public UNet
{
public: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBABinarization> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBABinarization> Output;


public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABinarization(void);
virtual ~UBABinarization(void);
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
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFBgDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBgBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFBgReset(void);

/// Выполняет расчет этого объекта
virtual bool AFBgCalculate(void);
// --------------------------
};

/// Вычисляет простой разностный кадр
class RDK_LIB_TYPE UBABinarizationSimple: public UBABinarization
{
protected: // Параметры
/// Порог по каналам
ULProperty<UColorT, UBABinarizationSimple> Threshold;

protected: // Временные переменные

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABinarizationSimple(void);
virtual ~UBABinarizationSimple(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBABinarizationSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFBgDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBgBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFBgReset(void);

/// Выполняет расчет этого объекта
virtual bool AFBgCalculate(void);
// --------------------------
};



//----------------------------------------------------------------------------
///ПРОСТОЙ РАЗНОСТНЫЙ КАДР С АДАПТИВНОЙ МОДЕЛЬЮ ПОРОГА
///
//----------------------------------------------------------------------------

class RDK_LIB_TYPE UBABinarizationSimpleAdaptiveThreshold: public UBABinarization
{
protected: // Параметры
/// Порог по каналам
UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> Threshold;

///Фон
UPropertyInputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> Background;

ULProperty<double, UBABinarizationSimpleAdaptiveThreshold> KAlpha;
ULProperty<double, UBABinarizationSimpleAdaptiveThreshold> KGamma;

///Начальное пороговое значени, при варианте без первого накомпления порога 1
ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> startThreshold;

UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> counterFG;

ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> stableBGflag;

///Варианты работы бинаризатора
ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> modeTypes;

UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> counterBG;

ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> unstableFlag;

///Выход для чего-то другого
UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> Threshold2;
UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> output2;

///максимально возможный порог в  пикселе
ULProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold> maxDinamThreshold;

///Инвертированный порог
UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> invThreshold;

///Статистика по тому, какое количесво разниц текущего кадра и фона
/// попадают в диапазоны 0-1, 1-2... 13-14, >14.
std::vector<double> ThresholdStats;

///количесво первых кадров, считающихся фоном
ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> countFirstCleanBgFrame;

///Вариант первоначального наколения порога
ULProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold> firstThTypes;

///минимально возможный порог в  пикселе
ULProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold> minDinamThreshold;

///счетчик того, что выше выше
int nCounter;

protected: // Временные переменные

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABinarizationSimpleAdaptiveThreshold(void);
virtual ~UBABinarizationSimpleAdaptiveThreshold(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBABinarizationSimpleAdaptiveThreshold* New(void);

bool BCalculate0(UBitmap &Background, UBitmap &input, UBitmap &output);
bool BCalculate1(UBitmap &Background, UBitmap &input, UBitmap &Threshold, UBitmap &output, UBitmap &counterFG);
bool BCalculate2(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                 UBitmap &output, UBitmap &counterFG,UBitmap &counterBG);
///Рабочая версия
bool BCalculate3(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                 UBitmap &output, UBitmap &counterFG,UBitmap &counterBG);
///Средений порог по всем countFirstCleanBgFrame первым пикселям
bool BCalculateFirstThreshold1(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                               UBitmap &output);
///Максимальный порог по всем countFirstCleanBgFrame первым пикселям
bool BCalculateFirstThreshold2(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                               UBitmap &output);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFBgDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBgBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFBgReset(void);

/// Выполняет расчет этого объекта
virtual bool AFBgCalculate(void);
// --------------------------
};




//----------------------------------------------------------------------------
///РАЗНОСТЫЙ КАДР С ПОМОЩЬЮ МЕТОДА ОЦУ
//----------------------------------------------------------------------------
class RDK_LIB_TYPE UBABinarizationOtsu: public UBABinarization
{
protected: // Параметры
//Минимальный порог, чтобы порог по Оцу все не засветил
ULProperty<int, UBABinarizationOtsu> minThreshold;
///Зоны интереса - маска
UPropertyInputData<UBitmap, UBABinarizationOtsu> Mask;


//int minThreshold;
// Порог по каналам
//ULProperty<UColorT, UBABinarizationSimple> Threshold;

protected: // Временные переменные

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABinarizationOtsu(void);
virtual ~UBABinarizationOtsu(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBABinarizationOtsu* New(void);

bool BCalculate(UBitmap &input, UBitmap &output, UBitmap &mask);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFBgDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBgBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFBgReset(void);

/// Выполняет расчет этого объекта
virtual bool AFBgCalculate(void);
// --------------------------
};


}
//---------------------------------------------------------------------------
#endif

