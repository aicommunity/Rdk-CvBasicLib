/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAResizeH
#define UBAResizeH

#include "../../../Engine/UNet.h"
#include "../../UBitmap.h"

namespace RDK {

/// Базовый класс масштабирования изображения
class UBAResize: public UNet
{
protected: // Параметры
/// Новый размер
int NewWidth,NewHeight;

protected: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBAResize> Input;

/// Выходное изображение
UPropertyInputData<UBitmap, UBAResize> Output;

protected: // Временные переменные
UBitmap Buffer;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAResize(void);
virtual ~UBAResize(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
/// Новый размер
int GetNewWidth(void) const;
int GetNewHeight(void) const;
bool SetNewWidth(int value);
bool SetNewHeight(int value);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
virtual bool BCalculate(UBitmap &input, UBitmap &output)=0;
bool BCalculate(UBitmap &input, int width, int height);
bool BCalculate(UBitmap &input, UBitmap &output, int width, int height);
// ---------------------

// ---------------------
// Операторы
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, int width, int height);
bool operator () (UBitmap &input, UBitmap &output, int width, int height);
// ---------------------

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

/// Изменяет размер изображения по четырем угловым точкам
class UBAResizeEdges: public UBAResize
{
public: // Методы
// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBAResizeEdges* New(void);

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
