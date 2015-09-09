/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAFlipImageH
#define UBAFlipImageH
//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// Базовый класс поворота изображения
class RDK_LIB_TYPE UBAFlipImage: public UNet
{
public: // Параметры
/// Способ отражения
/// 0 - не отражать
/// 1 - вокруг горизонтальной оси
/// 2 - вокруг вертикальной оси
ULProperty<int, UBAFlipImage> Mode;

protected: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBAFlipImage> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBAFlipImage> Output;

protected: // Временные переменные
UBitmap Buffer;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAFlipImage(void);
virtual ~UBAFlipImage(void);
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
class RDK_LIB_TYPE UBAFlipImageSimple: public UBAFlipImage
{
public: // Методы
// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBAFlipImageSimple* New(void);

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

