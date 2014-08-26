#ifndef UBA_REDUCE_CPP
#define UBA_REDUCE_CPP

#include "UBAReduce.h"


namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAReduce::UBAReduce(void)
: Input("Input",this,0),
  Output("Output",this,0)
{
 AddLookupProperty("NumCols",ptPubParameter, new UVProperty<int,UBAReduce>(this,&UBAReduce::SetNumCols,&UBAReduce::GetNumCols));
 AddLookupProperty("NumRows",ptPubParameter, new UVProperty<int,UBAReduce>(this,&UBAReduce::SetNumRows,&UBAReduce::GetNumRows));
}
UBAReduce::~UBAReduce(void)
{

}
// ---------------------
// Методы управления параметрами
// ---------------------
/// Номер строки и столбца для сохранения
const int& UBAReduce::GetNumCols(void) const
{
 return NumCols;
}

const int& UBAReduce::GetNumRows(void) const
{
 return NumRows;
}

bool UBAReduce::SetNumCols(const int &value)
{
 if(NumCols == value)
  return true;

 if(value == 0)
  return false;

 NumCols=value;
  return true;
}

bool UBAReduce::SetNumRows(const int &value)
{
 if(NumRows == value)
  return true;

 if(value == 0)
  return false;

 NumRows=value;
  return true;
}

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBAReduce* UBAReduce::New(void)
{
 return new UBAReduce;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAReduce::ADefault(void)
{
 NumCols=1;
 NumRows=1;
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAReduce::ABuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBAReduce::AReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBAReduce::ACalculate(void)
{
 if(!Input->GetData())
  return true;

 Input->Reduce(NumCols, NumRows, Output);
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------
#endif