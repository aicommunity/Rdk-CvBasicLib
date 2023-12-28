#ifndef UMATRIX_MATH_H
#define UMATRIX_MATH_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK{

template<class T>
class UMatrixMath: public UNet
{
protected: // Параметры
// Входной вектор матриц
UPropertyInputCData<MDMatrix<T>,UMatrixMath<T> > InputMatrixData;

// Режим работы
// 0 - сложение
// 1 - вычитание
// 2 - умножение

// Унарные операторы (игнорируют все входные матрицы кроме нулевой)
// 10 - унарный минус
// 11 - транспонирование
UProperty<int,UMatrixMath<T>> Mode;

public: // Данные
// Выходой вектор матриц
UPropertyOutputData<MDMatrix<T>,UMatrixMath<T>, ptPubOutput | ptState> OutputMatrixData;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UMatrixMath(void);
virtual ~UMatrixMath(void);

// --------------------------
// Системные методы управления объектом
// --------------------------
public:
// Выделяет память для новой чистой копии объекта этого класса
virtual UMatrixMath<T>* New(void);
// --------------------------


// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool ABuild(void);

// Сброс процесса счета.
virtual bool AReset(void);

// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------
};

// --------------------------
// Конструкторы и деструкторы
// --------------------------
template<class T>
UMatrixMath<T>::UMatrixMath(void)
 : InputMatrixData("InputMatrixData",this),
   OutputMatrixData("OutputMatrixData",this),
   Mode("Mode",this)
{
}

template<class T>
UMatrixMath<T>::~UMatrixMath(void)
{

}

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
template<class T>
UMatrixMath<T>* UMatrixMath<T>::New(void)
{
 return new UMatrixMath<T>;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
template<class T>
bool UMatrixMath<T>::ADefault(void)
{
 Mode=0;

 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
template<class T>
bool UMatrixMath<T>::ABuild(void)
{
 return true;
}

// Сброс процесса счета.
template<class T>
bool UMatrixMath<T>::AReset(void)
{
 OutputMatrixData->ToZero();
 return true;
}

// Выполняет расчет этого объекта
template<class T>
bool UMatrixMath<T>::ACalculate(void)
{
 if(InputMatrixData->size() == 0)
 {
  OutputMatrixData->Resize(0,0);
  return true;
 }

 switch(Mode)
 {
  case 0:
  {
   if((*InputMatrixData)[0])
   {
	int aRows=(*InputMatrixData)[0]->GetRows();
	int aCols=(*InputMatrixData)[0]->GetCols();

	for(size_t i=1; i<InputMatrixData->size(); i++)
	{
	 if( ((*InputMatrixData)[i]->GetRows()!=aRows)||((*InputMatrixData)[i]->GetCols()!=aCols) )
	  return true;
	}

	MDMatrix<T> temp;
	temp.Resize(aRows, aCols);
	temp=*(*InputMatrixData)[0];

	for(size_t i=1; i<InputMatrixData->size(); i++)
	{
	 if((*InputMatrixData)[i])
	 {
	  MDMatrix<T> &input=*(*InputMatrixData)[i];

	  temp+=input;
	 }
	}

	OutputMatrixData->Resize(aRows, aCols);
	MDMatrix<T> &output=*OutputMatrixData;
	output=temp;
   }
  }
  break;

  case 1:
  {
   if((*InputMatrixData)[0])
   {
	int aRows=(*InputMatrixData)[0]->GetRows();
	int aCols=(*InputMatrixData)[0]->GetCols();

	for(size_t i=1; i<InputMatrixData->size(); i++)
	{
	 if( ((*InputMatrixData)[i]->GetRows()!=aRows)||((*InputMatrixData)[i]->GetCols()!=aCols) )
	  return true;
	}

	MDMatrix<T> temp;
	temp.Resize(aRows, aCols);
	temp=*(*InputMatrixData)[0];

	for(size_t i=1; i<InputMatrixData->size(); i++)
	{
	 if((*InputMatrixData)[i])
	 {
	  MDMatrix<T> &input=*(*InputMatrixData)[i];

	  temp-=input;
	 }
	}

	OutputMatrixData->Resize(aRows, aCols);
	MDMatrix<T> &output=*OutputMatrixData;
	output=temp;
   }
  }
  break;

  case 2:
  {
   if((*InputMatrixData)[0])
   {
	int aRows=(*InputMatrixData)[0]->GetRows();
	int aCols=(*InputMatrixData)[0]->GetCols();

	MDMatrix<T> temp;
	temp.Resize(aRows, aCols);
	temp=*(*InputMatrixData)[0];

	for(size_t i=1; i<InputMatrixData->size(); i++)
	{
	 if((*InputMatrixData)[i])
	 {
	  MDMatrix<T> &input=*(*InputMatrixData)[i];
	  if(temp.GetCols()==input.GetRows())
	  {
	   if(temp.GetRows()!=input.GetCols())
		temp.Resize(temp.GetRows(), input.GetCols());

	   temp=temp*input;
	  }
	 }
	}

	OutputMatrixData->Resize(temp.GetRows(), temp.GetCols());
	MDMatrix<T> &output=*OutputMatrixData;
	output=temp;
   }
  }
  break;

  case 10:
  {
   if((*InputMatrixData)[0])
   {
	*OutputMatrixData=-*(*InputMatrixData)[0];
   }
  }
  break;

  case 11:
  {
   if((*InputMatrixData)[0])
   {
	(*InputMatrixData)[0]->Transpose(*OutputMatrixData);
   }
  }
  break;
 }


 return true;
}
// --------------------------


}


#endif
