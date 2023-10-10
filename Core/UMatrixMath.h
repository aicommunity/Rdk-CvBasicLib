#ifndef UMATRIX_MATH_H
#define UMATRIX_MATH_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK{

template<class T>
class UMatrixMath: public UNet
{
protected: // ���������
// ������� ������ ������
UPropertyInputCData<MDMatrix<T>,UMatrixMath<T> > InputMatrixData;

// ����� ������
// 0 - ��������
// 1 - ���������
// 2 - ���������

// ������� ��������� (���������� ��� ������� ������� ����� �������)
// 10 - ������� �����
// 11 - ����������������

int Mode;

public: // ������
// ������� ������ ������
UPropertyOutputData<MDMatrix<T>,UMatrixMath<T>, ptPubOutput | ptState> OutputMatrixData;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UMatrixMath(void);
virtual ~UMatrixMath(void);
// --------------------------
// ������ ���������� �����������
// --------------------------
const int& GetMode(void) const;
bool SetMode(const int &value);
// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
public:
// �������� ������ ��� ����� ������ ����� ������� ����� ������
virtual UMatrixMath<T>* New(void);
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
UMatrixMath<T>::UMatrixMath(void)
 : InputMatrixData("InputMatrixData",this),

   OutputMatrixData("OutputMatrixData",this)
{
 AddLookupProperty("Mode",ptPubParameter, new UVProperty<int,UMatrixMath>(this,&UMatrixMath::SetMode,&UMatrixMath::GetMode));
}

template<class T>
UMatrixMath<T>::~UMatrixMath(void)
{

}

// --------------------------
// ������ ���������� �����������
// --------------------------
template<class T>
const int& UMatrixMath<T>::GetMode(void) const
{
 return Mode;
}

template<class T>
bool UMatrixMath<T>::SetMode(const int &value)
{
 if(Mode==value)
  return true;

 Mode=value;
 return true;
}
// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
template<class T>
UMatrixMath<T>* UMatrixMath<T>::New(void)
{
 return new UMatrixMath<T>;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
template<class T>
bool UMatrixMath<T>::ADefault(void)
{
 Mode=0;

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
template<class T>
bool UMatrixMath<T>::ABuild(void)
{
 return true;
}

// ����� �������� �����.
template<class T>
bool UMatrixMath<T>::AReset(void)
{
 OutputMatrixData->ToZero();
 return true;
}

// ��������� ������ ����� �������
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
