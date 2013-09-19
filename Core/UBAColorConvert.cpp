/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAColorConvert_CPP
#define UBAColorConvert_CPP

#include <math.h>
#include "UBAColorConvert.h"
#include "../../UGraphicsBinarySerialize.h"

namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAColorConvert::UBAColorConvert(void)
: Input("Input",this,0),
  Output("Output",this,0)
{
 AddLookupProperty("NewColorModel",ptPubParameter, new UVProperty<UBMColorModel,UBAColorConvert>(this,&UBAColorConvert::SetNewColorModel,&UBAColorConvert::GetNewColorModel));
}
UBAColorConvert::~UBAColorConvert(void)
{
}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// Новый режим изображения
const UBMColorModel& UBAColorConvert::GetNewColorModel(void) const
{
 return NewColorModel;
}

bool UBAColorConvert::SetNewColorModel(const UBMColorModel &value)
{
 if(NewColorModel == value)
  return true;

 NewColorModel=value;
 return true;
}
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBAColorConvert* UBAColorConvert::New(void)
{
 return new UBAColorConvert;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAColorConvert::ADefault(void)
{
 NewColorModel=ubmY8;
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAColorConvert::ABuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBAColorConvert::AReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBAColorConvert::ACalculate(void)
{
// if(Outputs.GetSize()<1 || Inputs.GetSize()<1)
//  return true;

 Output->SetColorModel(NewColorModel,false);
 Input->ConvertTo(*Output);
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------

#endif


