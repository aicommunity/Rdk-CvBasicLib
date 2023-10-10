/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBALoopingH
#define UBALoopingH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

// Базовый класс выделения контуров
class RDK_LIB_TYPE UBALooping: public UNet
{
protected: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBALooping> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBALooping> Output;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBALooping(void);
virtual ~UBALooping(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
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
// Скрытые методы управления счетом трекинга
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

// Выделяет контура простым фильтром
class RDK_LIB_TYPE UBALoopingSimple: public UBALooping
{
public: // Методы
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBALoopingSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------

// --------------------------
// Скрытые методы управления счетом трекинга
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


// Выделяет контура фильтром собеля
class RDK_LIB_TYPE UBALoopingSobel: public UBALooping
{
public: // Методы
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBALoopingSobel* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------

// --------------------------
// Скрытые методы управления счетом трекинга
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
//---------------------------------------------------------------------------
#endif
