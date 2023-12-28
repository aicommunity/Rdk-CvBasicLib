/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBABitmapSource_H
#define UBABitmapSource_H

#include "../../Rdk-CvBasicLib/Core/UBASource.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// Базовый класс - источник изображений
class RDK_LIB_TYPE UBABitmapSource: public UNet
{
protected: // Параметры
/// Параметры изображений источников
UProperty<std::vector<UBitmapParam>,UBABitmapSource> SourceParamaters;

UPropertyOutputData<UBitmap, UBABitmapSource> Output;

protected: // Временные переменные

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABitmapSource(void);
virtual ~UBABitmapSource(void);
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

/// Простой класс-источник изображений
/// Предоставляет изображения-выходы, но не осуществляет никакого преобразования
class RDK_LIB_TYPE UBABitmapSourceSimple: public UBABitmapSource
{
protected: // Параметры

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABitmapSourceSimple(void);
virtual ~UBABitmapSourceSimple(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBABitmapSourceSimple* New(void);

bool BCalculate(void);
// ---------------------


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

/// Класс источник изображений, считываемых из файла
/// Under construction
class RDK_LIB_TYPE UBABitmapSourceFile: public UBABitmapSource
{
protected: // Параметры

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABitmapSourceFile(void);
virtual ~UBABitmapSourceFile(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBABitmapSourceFile* New(void);
// ---------------------


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


/// Простой класс-источник изображений
class RDK_LIB_TYPE UBASourceFreezeFrame: public UBASource
{
protected: // Входы и выходы
UPropertyInputData<bool, UBASourceFreezeFrame, ptPubInput | ptState> FreezeFlag;

protected:

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBASourceFreezeFrame(void);
virtual ~UBASourceFreezeFrame(void);
// --------------------------

protected:
// --------------------------
// Методы управления данными
// --------------------------
// --------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
/// Выделяет память для новой чистой копии объекта этого класса
virtual UBASourceFreezeFrame* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

/// Сброс процесса счета.
virtual bool AReset(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------
};

}

#endif

