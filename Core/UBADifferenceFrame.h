/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBADifferenceFrameH
#define UBADifferenceFrameH

#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

/// Базовый класс построения разнострого кадра
class RDK_LIB_TYPE UBADifferenceFrame: public UNet
{
public: // Входные и выходные данные
/// Входное изображение 1
UPropertyInputData<UBitmap, UBADifferenceFrame> Input1;

/// Входное изображение 2
UPropertyInputData<UBitmap, UBADifferenceFrame> Input2;

protected:
/// Выходное изображение
UPropertyOutputData<UBitmap, UBADifferenceFrame> Output;


public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBADifferenceFrame(void);
virtual ~UBADifferenceFrame(void);
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
virtual bool AFDiffDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFDiffBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFDiffReset(void);

/// Выполняет расчет этого объекта
virtual bool AFDiffCalculate(void);
// --------------------------
};

/// Вычисляет простой разностный кадр
class RDK_LIB_TYPE UBADifferenceFrameSimple: public UBADifferenceFrame
{
public: // Методы
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBADifferenceFrameSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &deduction, UBitmap &output);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFDiffDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFDiffBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFDiffReset(void);

/// Выполняет расчет этого объекта
virtual bool AFDiffCalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif

