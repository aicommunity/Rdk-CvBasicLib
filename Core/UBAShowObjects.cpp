/* ***********************************************************
@Copyright Aleksandr Bakhshiev, 2011.
E-mail:        palexab@gmail.com
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAShowObjects_CPP
#define UBAShowObjects_CPP
#include "UBAShowObjects.h"
#include <math.h>
//#include "../../UGraphicsXMLSerialize.h"
//#include "../../../Application/UIVisualController.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

//UBAShowObjectsRect UBGuiSelectionRect;

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAShowObjects::UBAShowObjects(void)
 : PenColor("PenColor",this),
   PenWidth("PenWidth",this),
   EnableShowFlag("EnableShowFlag",this),
   Input("Input",this),
   Output("Output",this),
   ObjectsColor("ObjectsColor", this),
   ObjectsName("ObjectsName", this),
   ObjectsId("ObjectsId", this)

{
}

UBAShowObjects::~UBAShowObjects(void)
{

}
// ---------------------



// --------------------------
// Методы управления параметрами
// --------------------------

bool UBAShowObjects::SetActivity(const bool &activity)
{
 if(!activity)
  Output->Fill(0);
 return UNet::SetActivity(activity);
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAShowObjects::ADefault(void)
{
 // Цвет рамки
 PenColor.v.c=0x00FF0000;

 EnableShowFlag=true;

 // Толщина рамки
 PenWidth=1;
 return AFSDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAShowObjects::ABuild(void)
{
 return AFSBuild();
}

// Сброс процесса счета без потери настроек
bool UBAShowObjects::AReset(void)
{
 Graphics.SetFont(GetDefaultFont());
 Graphics.SetFont(GetFont("Tahoma",20));

 return AFSReset();
}

// Выполняет расчет этого объекта
bool UBAShowObjects::ACalculate(void)
{
 Canvas.SetRes(Input->GetWidth(),Input->GetHeight(),ubmRGB24);
 Input->ConvertTo(Canvas);

 if(!EnableShowFlag)
 {
  *Output=Canvas;
  return true;
 }

 if(!Input->GetData())
 {
  *Output=Canvas;
  return true;
 }

 Graphics.SetCanvas(&Canvas);

 Graphics.SetPenWidth(PenWidth);
 Graphics.SetPenColor(PenColor);

 if(!AFSCalculate())
  return false;

 *Output=Canvas;
 return true;
}
// --------------------------

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAShowObjectsSimple::UBAShowObjectsSimple(void)
 : Zones("Zones",this),
   MatrixPoints("MatrixPoints",this)
{
}

UBAShowObjectsSimple::~UBAShowObjectsSimple(void)
{

}
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBAShowObjectsSimple* UBAShowObjectsSimple::New(void)
{
 return new UBAShowObjectsSimple;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров сплиттинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAShowObjectsSimple::AFSDefault(void)
{
// SetNumInputs(2);
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAShowObjectsSimple::AFSBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBAShowObjectsSimple::AFSReset(void)
{
 Output->Fill(0);
 return true;
}

// Выполняет расчет этого объекта
bool UBAShowObjectsSimple::AFSCalculate(void)
{
 if(Zones.IsConnected())
  for(size_t i=0;i<Zones->size();i++)
  {
   if(ObjectsColor->size()>i)
	Graphics.SetPenColor((*ObjectsColor)[i]);
   else
	Graphics.SetPenColor(PenColor);
   Graphics.Pixel((*Zones)[i].X,(*Zones)[i].Y);
  }

 if(MatrixPoints.IsConnected() && MatrixPoints->GetCols()>1)
  for(int i=0;i<MatrixPoints->GetRows();i++)
  {
   if(int(ObjectsColor->size())>i)
	Graphics.SetPenColor((*ObjectsColor)[i]);
   else
	Graphics.SetPenColor(PenColor);
   Graphics.Pixel(int((*MatrixPoints)(i,0)),int((*MatrixPoints)(i,1)));
  }
 return true;
}
// --------------------------


}
#endif

