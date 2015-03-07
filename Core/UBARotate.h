/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBARotateH
#define UBARotateH
#include "../../../Engine/UNet.h"
#include "../../UBitmap.h"

namespace RDK {

/// Базовый класс поворота изображения
class RDK_LIB_TYPE UBARotate: public UNet
{
protected: // Параметры
/// Угол поворота (градусы)
float Angle;

/// Флаг расширения
bool Enlarge;

protected: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBARotate> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBARotate> Output;

protected: // Временные переменные
UBitmap Buffer;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBARotate(void);
virtual ~UBARotate(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
/// Угол поворота (градусы)
float GetAngle(void) const;
bool SetAngle(float angle);

/// Флаг расширения
bool GetEnlarge(void) const;
bool SetEnlarge(bool enlarge);
// ---------------------

// ---------------------
// Операторы
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, UBitmap &output, float angle, bool enlarge=false);
// ---------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
virtual bool BCalculate(UBitmap &input, UBitmap &output)=0;

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

/// Поворачивает изображение на заданный угол
class RDK_LIB_TYPE UBARotateSimple: public UBARotate
{
public: // Методы
// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBARotateSimple* New(void);

virtual bool BCalculate(UBitmap &input, UBitmap &output);
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

