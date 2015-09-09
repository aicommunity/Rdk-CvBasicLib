/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBAFlipImage.h"
#include <math.h>
#include <string.h>

namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAFlipImage::UBAFlipImage(void)
: Mode("Mode",this),
  Input("Input",this),
  Output("Output",this)
{
}

UBAFlipImage::~UBAFlipImage(void)
{
}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------

// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAFlipImage::ADefault(void)
{
 Mode=0;
 return AFCDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAFlipImage::ABuild(void)
{
 return AFCBuild();
}

// Сброс процесса счета.
bool UBAFlipImage::AReset(void)
{
 return AFCReset();
}

// Выполняет расчет этого объекта
bool UBAFlipImage::ACalculate(void)
{
 return AFCCalculate();
}
// --------------------------



// Поворачивает изображение на заданный угол
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBAFlipImageSimple* UBAFlipImageSimple::New(void)
{
 return new UBAFlipImageSimple;
}

bool UBAFlipImageSimple::BCalculate(UBitmap &input, UBitmap &output)
{
 switch(Mode)
 {
 case 1:
  input.ReflectionX(&output);
 break;

 case 2:
  input.ReflectionY(&output);
 break;

 }

 return true;
}
// ---------------------


// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAFlipImageSimple::AFCDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAFlipImageSimple::AFCBuild(void)
{
 return true;
}

// Сброс процесса счета.
bool UBAFlipImageSimple::AFCReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBAFlipImageSimple::AFCCalculate(void)
{
 return BCalculate(*Input, *Output);
}
// --------------------------
}
//---------------------------------------------------------------------------

