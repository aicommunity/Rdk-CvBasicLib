#ifndef UBA_REDUCE_CPP
#define UBA_REDUCE_CPP

#include "UBAReduce.h"


namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAReduce::UBAReduce(void)
: Input("Input",this),
  Output("Output",this),
  NumCols("NumCols",this),
  NumRows("NumRows",this)
{
}
UBAReduce::~UBAReduce(void)
{

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

 Input->Reduce(NumCols, NumRows, &Output.v);
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------
#endif
