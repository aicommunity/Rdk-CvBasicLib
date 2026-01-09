#ifndef UMDMATRIX_MUX_H
#define UMDMATRIX_MUX_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK{

template<class T>
class UMDMatrixMux: public UNet
{
protected: // 
///  ,    ,   
UProperty<std::vector<bool>,UMDMatrixMux<T>, ptPubParameter> InputActivities;

public: // 
///   
UProperty<std::vector<MDMatrix<T>>,UMDMatrixMux<T>, ptPubInput> InputMatrixData;

///  
/// 0 -    
/// 1 -    
/// 2 -       
/// 3 -       
UProperty<int,UMDMatrixMux<T>, ptPubParameter> Mode;

public: // 
//   
UProperty<MDMatrix<T>,UMDMatrixMux<T>, ptPubOutput | ptState> OutputMatrixData;

public: // 
// --------------------------
//   
// --------------------------
UMDMatrixMux(void);
virtual ~UMDMatrixMux(void);


// --------------------------
//    
// --------------------------
public:
//         
virtual UMDMatrixMux<T>* New(void);
// --------------------------


// --------------------------
//    
// --------------------------
protected:
//        
virtual bool ADefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool ABuild(void);

//   .
virtual bool AReset(void);

//    
virtual bool ACalculate(void);
// --------------------------
};

// --------------------------
//   
// --------------------------
template<class T>
UMDMatrixMux<T>::UMDMatrixMux(void)
 :
  InputActivities("InputActivities",this),
  InputMatrixData("InputMatrixData",this),
  Mode("Mode",this),
  OutputMatrixData("OutputMatrixData",this)
{
}

template<class T>
UMDMatrixMux<T>::~UMDMatrixMux(void)
{

}

// --------------------------
//    
// --------------------------
//         
template<class T>
UMDMatrixMux<T>* UMDMatrixMux<T>::New(void)
{
 return new UMDMatrixMux<T>;
}
// --------------------------

// --------------------------
//    
// --------------------------
//        
template<class T>
bool UMDMatrixMux<T>::ADefault(void)
{
 Mode=0;

 return true;
}

//     
//   
//    Reset()   Ready  true
//    
template<class T>
bool UMDMatrixMux<T>::ABuild(void)
{
 return true;
}

//   .
template<class T>
bool UMDMatrixMux<T>::AReset(void)
{
 OutputMatrixData->Resize(0,0);
 return true;
}

//    
template<class T>
bool UMDMatrixMux<T>::ACalculate(void)
{
 // Безопасное получение размеров и данных
 size_t input_matrix_size = InputMatrixData->size();
 if(input_matrix_size == 0)
 {
  OutputMatrixData->Resize(0,0);
  return true;
 }

 size_t input_activities_size = InputActivities->size();
 if(input_activities_size < input_matrix_size)
  InputActivities->resize(input_matrix_size, true);

 // Получаем копию данных InputActivities для безопасного доступа
 // (std::vector<bool> имеет специальную реализацию с proxy объектами)
 std::vector<bool> activities_copy = *InputActivities;
 size_t activities_size = activities_copy.size();

 size_t i=0;
 switch(Mode)
 {
  //   
  case 0:
  {
   int new_rows=0;//((*InputMatrixData)[0])?(*InputMatrixData)[0]->GetRows():0;
   int new_cols=-1;//((*InputMatrixData)[0])?(*InputMatrixData)[0]->GetCols():0;

   do
//   for(size_t i=1;i<InputMatrixData->size();i++)
   {
    // Проверка границ перед доступом
    if(i >= activities_size || i >= input_matrix_size)
     break;
     
    if(activities_copy[i])
    {
     new_rows+=InputMatrixData[i].GetRows();
     if(new_cols>InputMatrixData[i].GetCols() || new_cols<0)
      new_cols=InputMatrixData[i].GetCols();
    }
    ++i;
   } while(i < input_matrix_size);
   
   // Проверка: если нет активных входов или некорректные размеры, выходим
   if(new_rows <= 0 || new_cols <= 0)
   {
    OutputMatrixData->Resize(0,0);
    return true;
   }
   
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;
   int row=0;
   for(size_t i2=0;i2<input_matrix_size;i2++)
   {
    if(i2 < activities_size && activities_copy[i2])
    {
     const MDMatrix<T> &input=InputMatrixData[i2];
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

  //   
  case 1:
  {
   int new_rows=-1;//((*InputMatrixData)[0])?(*InputMatrixData)[0]->GetRows():0;
   int new_cols=0;//((*InputMatrixData)[0])?(*InputMatrixData)[0]->GetCols():0;

   do
//   for(size_t i=1;i<InputMatrixData->size();i++)
   {
    // Проверка границ перед доступом
    if(i >= activities_size || i >= input_matrix_size)
     break;
     
    if(activities_copy[i])
    {
     new_cols+=InputMatrixData[i].GetCols();
     if(new_rows>InputMatrixData[i].GetRows() || new_rows<0)
      new_rows=InputMatrixData[i].GetRows();
    }
    ++i;
   } while(i < input_matrix_size);
   
   // Проверка: если нет активных входов или некорректные размеры, выходим
   if(new_rows <= 0 || new_cols <= 0)
   {
    OutputMatrixData->Resize(0,0);
    return true;
   }
   
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;
   int col=0;
   for(size_t i2=0;i2<input_matrix_size;i2++)
   {
    if(i2 < activities_size && activities_copy[i2])
    {
     const MDMatrix<T> &input=InputMatrixData[i2];
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

  /// 2 -       
  case 2:
  {
   int new_rows=-1;
   int new_cols=0;

   do
   {
    // Проверка границ перед доступом
    if(i >= activities_size || i >= input_matrix_size)
     break;
     
    if(activities_copy[i])
    {
     new_cols+=InputMatrixData[i].GetCols();
     if(new_rows>InputMatrixData[i].GetRows() || new_rows<0)
      new_rows=InputMatrixData[i].GetRows();
    }
    ++i;
   } while(i < input_matrix_size);
   
   // Проверка: если нет активных входов или некорректные размеры, выходим
   if(new_rows <= 0 || new_cols <= 0)
   {
    OutputMatrixData->Resize(0,0);
    return true;
   }
   
   OutputMatrixData->Resize(new_rows, new_cols);

   MDMatrix<T> &output=*OutputMatrixData;

   int col=0;
   int j=0;
   do {
    for(size_t i2=0;i2<input_matrix_size;i2++)
    {
     if(i2 < activities_size && activities_copy[i2])
     {
      const MDMatrix<T> &input=InputMatrixData[i2];

      for(int k=0;k<new_rows;k++)
       output(k,col)=input(k,j);

      ++col;
     }
    }
    ++j;
   } while (col<output.GetCols());
  }
  break;

  /// 3 -       
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
protected: // Input activities
/// Input activities vector
UProperty<std::vector<bool>,UMDScalarMux<T>, ptPubParameter> InputActivities;

protected: // 
///   
UProperty<std::vector<T>,UMDScalarMux<T>, ptPubInput> InputMatrixData;

///  
/// 0 -    
/// 1 -    
/// 2 -       
/// 3 -       
UProperty<int,UMDScalarMux<T>, ptPubParameter> Mode;

public: // 
//   
UProperty<MDMatrix<T>,UMDScalarMux<T>, ptPubOutput | ptState> OutputMatrixData;

public: // 
// --------------------------
//   
// --------------------------
UMDScalarMux(void);
virtual ~UMDScalarMux(void);

// --------------------------
//    
// --------------------------
public:
//         
virtual UMDScalarMux<T>* New(void);
// --------------------------


// --------------------------
//    
// --------------------------
protected:
//        
virtual bool ADefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool ABuild(void);

//   .
virtual bool AReset(void);

//    
virtual bool ACalculate(void);
// --------------------------
};

// --------------------------
//   
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
//    
// --------------------------
//         
template<class T>
UMDScalarMux<T>* UMDScalarMux<T>::New(void)
{
 return new UMDScalarMux<T>;
}
// --------------------------

// --------------------------
//    
// --------------------------
//        
template<class T>
bool UMDScalarMux<T>::ADefault(void)
{
 Mode=0;

 return true;
}

//     
//   
//    Reset()   Ready  true
//    
template<class T>
bool UMDScalarMux<T>::ABuild(void)
{
 return true;
}

//   .
template<class T>
bool UMDScalarMux<T>::AReset(void)
{
 OutputMatrixData->Resize(0,0);
 return true;
}

//    
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
  //   
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
   for(size_t i2=0;i2<InputMatrixData->size();i2++)
   {
    if(InputActivities[i2])
    {
     output(row,0)=InputMatrixData[i2];
     ++row;
    }
   }
  }
  break;

  //   
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
   for(size_t i2=0;i2<InputMatrixData->size();i2++)
   {
    if(InputActivities[i2])
    {
     output(0,col)=InputMatrixData[i2];
     ++col;
    }
   }
  }
  break;

  /// 2 -       
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
    for(size_t i2=0;i2<InputMatrixData->size();i2++)
    {
     if(InputActivities[i2])
     {
      output(0,col)=InputMatrixData[i2];
      ++col;
     }
    }
    ++j;
   } while (col<output.GetCols());
  }
  break;

  /// 3 -       
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
