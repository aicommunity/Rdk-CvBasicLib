#ifndef UMDMATRIX_MUX_H
#define UMDMATRIX_MUX_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK{

template<class T>
class UMDMatrixMux: public UNet
{
protected: // ���������
/// ������ ������, ����������� ����� ����� ������������, � ����� ���
ULProperty<std::vector<bool>,UMDMatrixMux<T> > InputActivities;

public: // ������
/// ������� ������ ������
UPropertyInputCData<MDMatrix<T>,UMDMatrixMux<T> > InputMatrixData;

/// ����� ������
/// 0 - ������ ������ � ������
/// 1 - ������ ������ � ������
/// 2 - ������ ������ � ������ � ������������ ��������
/// 3 - ������ ������ � ������ � ������������ �����
UProperty<int,UMDMatrixMux<T>> Mode;

public: // ������
// ������� ������ ������
UPropertyOutputData<MDMatrix<T>,UMDMatrixMux<T>, ptPubOutput | ptState> OutputMatrixData;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UMDMatrixMux(void);
virtual ~UMDMatrixMux(void);


// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
public:
// �������� ������ ��� ����� ������ ����� ������� ����� ������
virtual UMDMatrixMux<T>* New(void);
// --------------------------


// --------------------------
// ������� ������ ���������� ������
// --------------------------
protected:
// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
virtual bool ABuild(void);

// ����� �������� �����.
virtual bool AReset(void);

// ��������� ������ ����� �������
virtual bool ACalculate(void);
// --------------------------
};

// --------------------------
// ������������ � �����������
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
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
template<class T>
UMDMatrixMux<T>* UMDMatrixMux<T>::New(void)
{
 return new UMDMatrixMux<T>;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
template<class T>
bool UMDMatrixMux<T>::ADefault(void)
{
 Mode=0;

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
template<class T>
bool UMDMatrixMux<T>::ABuild(void)
{
 return true;
}

// ����� �������� �����.
template<class T>
bool UMDMatrixMux<T>::AReset(void)
{
 OutputMatrixData->Resize(0,0);
 return true;
}

// ��������� ������ ����� �������
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
  // ������ � ������
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

  // ������ � ������
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

  /// 2 - ������ ������ � ������ � ������������ ��������
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

  /// 3 - ������ ������ � ������ � ������������ �����
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
protected: // ���������
/// ������ ������, ����������� ����� ����� ������������, � ����� ���
ULProperty<std::vector<bool>,UMDScalarMux<T> > InputActivities;

protected: // ������
/// ������� ������ ������
UPropertyInputCData<T,UMDScalarMux<T> > InputMatrixData;

/// ����� ������
/// 0 - ������ ������ � ������
/// 1 - ������ ������ � ������
/// 2 - ������ ������ � ������ � ������������ ��������
/// 3 - ������ ������ � ������ � ������������ �����
UProperty<int,UMDScalarMux<T>> Mode;

public: // ������
// ������� ������ ������
UPropertyOutputData<MDMatrix<T>,UMDScalarMux<T>, ptPubOutput | ptState> OutputMatrixData;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UMDScalarMux(void);
virtual ~UMDScalarMux(void);

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
public:
// �������� ������ ��� ����� ������ ����� ������� ����� ������
virtual UMDScalarMux<T>* New(void);
// --------------------------


// --------------------------
// ������� ������ ���������� ������
// --------------------------
protected:
// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
virtual bool ABuild(void);

// ����� �������� �����.
virtual bool AReset(void);

// ��������� ������ ����� �������
virtual bool ACalculate(void);
// --------------------------
};

// --------------------------
// ������������ � �����������
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
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
template<class T>
UMDScalarMux<T>* UMDScalarMux<T>::New(void)
{
 return new UMDScalarMux<T>;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
template<class T>
bool UMDScalarMux<T>::ADefault(void)
{
 Mode=0;

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
template<class T>
bool UMDScalarMux<T>::ABuild(void)
{
 return true;
}

// ����� �������� �����.
template<class T>
bool UMDScalarMux<T>::AReset(void)
{
 OutputMatrixData->Resize(0,0);
 return true;
}

// ��������� ������ ����� �������
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
  // ������ � ������
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

  // ������ � ������
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

  /// 2 - ������ ������ � ������ � ������������ ��������
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

  /// 3 - ������ ������ � ������ � ������������ �����
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
