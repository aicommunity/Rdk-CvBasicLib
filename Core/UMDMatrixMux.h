#ifndef UMDMATRIX_MUX_H
#define UMDMATRIX_MUX_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK{

template<class T>
class UMDMatrixMux: public UNet
{
protected: // Параметры
/// Массив флагов, описывающих какие входы использовать, а какие нет
ULProperty<std::vector<bool>,UMDMatrixMux<T> > InputActivities;

public: // Данные
/// Входной вектор матриц
UPropertyInputCData<MDMatrix<T>,UMDMatrixMux<T> > InputMatrixData;

/// Режим работы
/// 0 - сборка матриц в высоту
/// 1 - сборка матриц в ширину
/// 2 - сборка матриц в ширину с чередованием столбцов
/// 3 - сборка матриц в высоту с чередованием строк
UProperty<int,UMDMatrixMux<T>> Mode;

public: // Данные
// Выходой вектор матриц
UPropertyOutputData<MDMatrix<T>,UMDMatrixMux<T>, ptPubOutput | ptState> OutputMatrixData;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UMDMatrixMux(void);
virtual ~UMDMatrixMux(void);


// --------------------------
// Системные методы управления объектом
// --------------------------
public:
// Выделяет память для новой чистой копии объекта этого класса
virtual UMDMatrixMux<T>* New(void);
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
UMDMatrixMux<T>::UMDMatrixMux(void)
 :
  InputActivities("InputActivities",this),
  InputMatrixData("InputMatrixData",this),

  OutputMatrixData("OutputMatrixData",this),
  Mode("Mode",this)
{
}

template<class T>
UMDMatrixMux<T>::~UMDMatrixMux(void)
{

}

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
template<class T>
UMDMatrixMux<T>* UMDMatrixMux<T>::New(void)
{
 return new UMDMatrixMux<T>;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
template<class T>
bool UMDMatrixMux<T>::ADefault(void)
{
 Mode=0;

 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
template<class T>
bool UMDMatrixMux<T>::ABuild(void)
{
 return true;
}

// Сброс процесса счета.
template<class T>
bool UMDMatrixMux<T>::AReset(void)
{
 OutputMatrixData->Resize(0,0);
 return true;
}

// Выполняет расчет этого объекта
template<class T>
bool UMDMatrixMux<T>::ACalculate(void)
{
 if(InputMatrixData->size() == 0)
 {
  OutputMatrixData->Resize(0,0);
  return true;
 }

 if(InputActivities->size()<InputMatrixData->size())
  InputActivities->resize(InputMatrixData->size(),true);

 size_t i=0;
 switch(Mode)
 {
  // Сборка в высоту
  case 0:
  {
   int new_rows=0;//((*InputMatrixData)[0])?(*InputMatrixData)[0]->GetRows():0;
   int new_cols=-1;//((*InputMatrixData)[0])?(*InputMatrixData)[0]->GetCols():0;

   do
//   for(size_t i=1;i<InputMatrixData->size();i++)
   {
    if(InputActivities[i])
    {
     new_rows+=InputMatrixData[i].GetRows();
     if(new_cols>InputMatrixData[i].GetCols() || new_cols<0)
      new_cols=InputMatrixData[i].GetCols();
    }
    ++i;
   } while(i<InputMatrixData->size());
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;
   int row=0;
   for(size_t i=0;i<InputMatrixData->size();i++)
   {
    if(InputActivities[i])
    {
     const MDMatrix<T> &input=InputMatrixData[i];
     for(int j=0;j<input.GetRows();j++)
     {
      for(int k=0;k<new_cols;k++)
       output(row,k)=input(j,k);

      ++row;
     }
    }
   }
  }
  break;

  // Сборка в ширину
  case 1:
  {
   int new_rows=-1;//((*InputMatrixData)[0])?(*InputMatrixData)[0]->GetRows():0;
   int new_cols=0;//((*InputMatrixData)[0])?(*InputMatrixData)[0]->GetCols():0;

   do
//   for(size_t i=1;i<InputMatrixData->size();i++)
   {
    if(InputActivities[i])
    {
     new_cols+=InputMatrixData[i].GetCols();
     if(new_rows>InputMatrixData[i].GetRows() || new_rows<0)
      new_rows=InputMatrixData[i].GetRows();
    }
    ++i;
   } while(i<InputMatrixData->size());
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;
   int col=0;
   for(size_t i=0;i<InputMatrixData->size();i++)
   {
    if(InputActivities[i])
    {
     const MDMatrix<T> &input=InputMatrixData[i];
     for(int j=0;j<input.GetCols();j++)
     {
      for(int k=0;k<new_rows;k++)
       output(k,col)=input(k,j);

      ++col;
     }
    }
   }
  }
  break;

  /// 2 - сборка матриц в ширину с чередованием столбцов
  case 2:
  {
   int new_rows=-1;
   int new_cols=0;

   do
   {
    if(InputActivities[i])
    {
     new_cols+=InputMatrixData[i].GetCols();
     if(new_rows>InputMatrixData[i].GetRows() || new_rows<0)
      new_rows=InputMatrixData[i].GetRows();
    }
    ++i;
   } while(i<InputMatrixData->size());
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;

   int col=0;
   int j=0;
   do {
    for(size_t i=0;i<InputMatrixData->size();i++)
    {
     if(InputActivities[i])
     {
      const MDMatrix<T> &input=InputMatrixData[i];

      for(int k=0;k<new_rows;k++)
       output(k,col)=input(k,j);

      ++col;
     }
    }
    ++j;
   } while (col<output.GetCols());
  }
  break;

  /// 3 - сборка матриц в высоту с чередованием строк
  case 3:
  {

  }
  break;
 }

 return true;
}
// --------------------------


template<class T>
class UMDScalarMux: public UNet
{
protected: // Параметры
/// Массив флагов, описывающих какие входы использовать, а какие нет
ULProperty<std::vector<bool>,UMDScalarMux<T> > InputActivities;

protected: // Данные
/// Входной вектор матриц
UPropertyInputCData<T,UMDScalarMux<T> > InputMatrixData;

/// Режим работы
/// 0 - сборка матриц в высоту
/// 1 - сборка матриц в ширину
/// 2 - сборка матриц в ширину с чередованием столбцов
/// 3 - сборка матриц в высоту с чередованием строк
UProperty<int,UMDScalarMux<T>> Mode;

public: // Данные
// Выходой вектор матриц
UPropertyOutputData<MDMatrix<T>,UMDScalarMux<T>, ptPubOutput | ptState> OutputMatrixData;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UMDScalarMux(void);
virtual ~UMDScalarMux(void);

// --------------------------
// Системные методы управления объектом
// --------------------------
public:
// Выделяет память для новой чистой копии объекта этого класса
virtual UMDScalarMux<T>* New(void);
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
UMDScalarMux<T>::UMDScalarMux(void)
 :
  InputActivities("InputActivities",this),
  InputMatrixData("InputMatrixData",this),
  Mode("Mode",this),
  OutputMatrixData("OutputMatrixData",this)
{
}

template<class T>
UMDScalarMux<T>::~UMDScalarMux(void)
{

}

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
template<class T>
UMDScalarMux<T>* UMDScalarMux<T>::New(void)
{
 return new UMDScalarMux<T>;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
template<class T>
bool UMDScalarMux<T>::ADefault(void)
{
 Mode=0;

 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
template<class T>
bool UMDScalarMux<T>::ABuild(void)
{
 return true;
}

// Сброс процесса счета.
template<class T>
bool UMDScalarMux<T>::AReset(void)
{
 OutputMatrixData->Resize(0,0);
 return true;
}

// Выполняет расчет этого объекта
template<class T>
bool UMDScalarMux<T>::ACalculate(void)
{
 if(InputMatrixData->size() == 0)
 {
  OutputMatrixData->Resize(0,0);
  return true;
 }

 if(InputActivities->size()<InputMatrixData->size())
  InputActivities->resize(InputMatrixData->size(),true);

 size_t i=0;
 switch(Mode)
 {
  // Сборка в высоту
  case 0:
  {
   int new_rows=0;
   int new_cols=-1;

   do
   {
	if((*InputMatrixData)[i] && (*InputActivities)[i])
	{
	 new_rows++;
	 new_cols=1;
	}
	++i;
   } while(i<InputMatrixData->size());
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;
   int row=0;
   for(size_t i=0;i<InputMatrixData->size();i++)
   {
    if(InputActivities[i])
    {
     output(row,0)=InputMatrixData[i];
     ++row;
    }
   }
  }
  break;

  // Сборка в ширину
  case 1:
  {
   int new_rows=-1;
   int new_cols=0;

   do
   {
    if(InputActivities[i])
    {
     new_cols++;
     new_rows=1;
    }
    ++i;
   } while(i<InputMatrixData->size());
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;
   int col=0;
   for(size_t i=0;i<InputMatrixData->size();i++)
   {
    if(InputActivities[i])
    {
     output(0,col)=InputMatrixData[i];
     ++col;
    }
   }
  }
  break;

  /// 2 - сборка матриц в ширину с чередованием столбцов
  case 2:
  {
   int new_rows=-1;
   int new_cols=0;

   do
   {
    if(InputActivities[i])
    {
     new_cols++;
     new_rows=1;
    }
    ++i;
   } while(i<InputMatrixData->size());
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;

   int col=0;
   int j=0;
   do {
    for(size_t i=0;i<InputMatrixData->size();i++)
    {
     if(InputActivities[i])
     {
      output(0,col)=InputMatrixData[i];
      ++col;
     }
    }
    ++j;
   } while (col<output.GetCols());
  }
  break;

  /// 3 - сборка матриц в высоту с чередованием строк
  case 3:
  {

  }
  break;
 }

 return true;
}
// --------------------------

}


#endif
