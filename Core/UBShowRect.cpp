/* ***********************************************************
@Copyright Alexsandr Nikolskiy, 2011.
E-mail:        alexxxniko@gmail.com
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBShowRect_CPP
#define UBShowRect_CPP
#include "UBShowRect.h"
#include <math.h>
//#include "../../UGraphicsXMLSerialize.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {


// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBShowRect::UBShowRect(void)
 : MatrixZones("MatrixZones",this),
   RectZones("RectZones",this),
   ShowFlags("ShowFlags",this)
{
}

UBShowRect::~UBShowRect(void)
{

}
// ---------------------


// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBShowRect* UBShowRect::New(void)
{
 return new UBShowRect;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров сплиттинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBShowRect::AFSDefault(void)
{
// SetNumInputs(2);
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBShowRect::AFSBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBShowRect::AFSReset(void)
{
 Output->Fill(0);
 return true;
}

// Выполняет расчет этого объекта
bool UBShowRect::AFSCalculate(void)
{
 if(MatrixZones)
 {
  MDMatrix<double> &matrix=*MatrixZones;
  MDMatrix<int> show_flags=*ShowFlags;
  if(show_flags.GetRows() != matrix.GetRows() || show_flags.GetCols()<=0)
  {
   show_flags.Assign(matrix.GetRows(),1,1);
  }
  for(int i=0;i<matrix.GetRows();i++)
  {
   if(show_flags(i,0) == 0)
	continue;
   if(int(ObjectsColor->size())>i)
	Graphics.SetPenColor((*ObjectsColor)[i]);
   else
	Graphics.SetPenColor(PenColor);
   Graphics.Rect(int(matrix(i,0)),int(matrix(i,1)),int(matrix(i,0)+matrix(i,2)),int(matrix(i,1)+matrix(i,3)));

   if(int(ObjectsName->size())>i)
    Graphics.Text((*ObjectsName)[i],int(matrix(i,0)),int(matrix(i,1)));

   if(int(ObjectsId->GetSize())>i)
	Graphics.Text(sntoa((*ObjectsId)(0,i)),int(matrix(i,0)),int(matrix(i,1)));
  }
 }

 if(RectZones)
  for(size_t i=0;i<RectZones->size();i++)
  {
   UBRect &rect=(*RectZones)[i];
   if(ObjectsColor->size()>i)
	Graphics.SetPenColor((*ObjectsColor)[i]);
   else
	Graphics.SetPenColor(PenColor);
   Graphics.Rect(rect.X,rect.Y,rect.X+rect.Width,rect.Y+rect.Height);

   if(ObjectsName->size()>i)
	Graphics.Text((*ObjectsName)[i],rect.X,rect.Y);

   if(ObjectsId->GetSize()>int(i))
    Graphics.Text(sntoa((*ObjectsId)(0,int(i))),rect.X,rect.Y);
  }
 return true;
}
// --------------------------


}
#endif

