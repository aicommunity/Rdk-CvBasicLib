#ifndef UBALabeling_CPP
#define UBALabeling_CPP
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBALabeling.h"
#include <math.h>

namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBALabeling::UBALabeling(void)
: Input("Input",this),
 Zones("Zones",this)
{
}

UBALabeling::~UBALabeling(void)
{
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBALabeling::ADefault(void)
{
 return AFBgDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBALabeling::ABuild(void)
{
 return AFBgBuild();
}

// Сброс процесса счета без потери настроек
bool UBALabeling::AReset(void)
{
 return AFBgReset();
}

// Выполняет расчет этого объекта
bool UBALabeling::ACalculate(void)
{
 return AFBgCalculate();
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBALabeling::AFBgDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBALabeling::AFBgBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBALabeling::AFBgReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBALabeling::AFBgCalculate(void)
{
 return true;
}
// --------------------------



// ---------------------
// Методы счета
// ---------------------
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBALabelingSimple::UBALabelingSimple(void)
{

}

UBALabelingSimple::~UBALabelingSimple(void)
{

}
// ---------------------


// Создание новой копии этого объекта
UBALabelingSimple* UBALabelingSimple::New(void)
{
 return new UBALabelingSimple;
}

void UBALabelingSimple::LCalculate(UBitmap &bmp, MDMatrix<double> &output)
{

}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBALabelingSimple::AFBgDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBALabelingSimple::AFBgBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBALabelingSimple::AFBgReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBALabelingSimple::AFBgCalculate(void)
{
 Zones->Resize(0,4);

 UBColor *data=Input->GetData();

 for(int i=0;i<Input->GetLength();i++)
  if(*data++ >0)
  {
   Zones->Resize(1,4);
   (*Zones)(0,0)=0;
   (*Zones)(0,1)=0;
   (*Zones)(0,2)=Input->GetWidth();
   (*Zones)(0,3)=Input->GetHeight();
   break;
  }

// LCalculate(*Input, *Zones);
 return true;
}
// --------------------------


}
//---------------------------------------------------------------------------

#endif
