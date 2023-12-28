/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBACrop_CPP
#define UBACrop_CPP

#include <math.h>
#include "UBACrop.h"
//#include "../../UGraphicsBinarySerialize.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBACrop::UBACrop(void)
: Input("Input",this),
  CropRect("CropRect",this),
  Output("Output",this)
{
}
UBACrop::~UBACrop(void)
{
}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------

// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBACrop* UBACrop::New(void)
{
 return new UBACrop;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBACrop::ADefault(void)
{
 CropRect->Assign(1,4,0);
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBACrop::ABuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBACrop::AReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBACrop::ACalculate(void)
{
 if(!Input.IsConnected())
  return true;

 MDMatrix<int> &crop_rect=*CropRect;

 if(crop_rect.FindMinValue()<0)
 {
  Output->Clear();
  return true;
 }

 if(crop_rect.GetRows() == 0 || crop_rect.GetCols() == 0)
 {
  Output->Clear();
  return true;
 }

 int width=Input->GetWidth()-crop_rect(0,0)-crop_rect(0,2);
 int height=Input->GetHeight()-crop_rect(0,1)-crop_rect(0,3);

 if(width<0 || height<0)
 {
  Output->Clear();
  return true;
 }

 Output->SetRes(width, height, Input->GetColorModel());
 Input->GetRect(crop_rect(0,0), crop_rect(0,1), *Output);
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------

#endif


