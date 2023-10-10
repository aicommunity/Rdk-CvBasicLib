#ifndef UBALabeling_CPP
#define UBALabeling_CPP
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBALabeling.h"
#include <math.h>

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBALabeling::UBALabeling(void)
: Input("Input",this),
 Zones("Zones",this)
{
}

UBALabeling::~UBALabeling(void)
{
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBALabeling::ADefault(void)
{
 return AFBgDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBALabeling::ABuild(void)
{
 return AFBgBuild();
}

// ����� �������� ����� ��� ������ ��������
bool UBALabeling::AReset(void)
{
 return AFBgReset();
}

// ��������� ������ ����� �������
bool UBALabeling::ACalculate(void)
{
 return AFBgCalculate();
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBALabeling::AFBgDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBALabeling::AFBgBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBALabeling::AFBgReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBALabeling::AFBgCalculate(void)
{
 return true;
}
// --------------------------



// ---------------------
// ������ �����
// ---------------------
// ---------------------
// ������������ � �����������
// ---------------------
UBALabelingSimple::UBALabelingSimple(void)
{

}

UBALabelingSimple::~UBALabelingSimple(void)
{

}
// ---------------------


// �������� ����� ����� ����� �������
UBALabelingSimple* UBALabelingSimple::New(void)
{
 return new UBALabelingSimple;
}

void UBALabelingSimple::LCalculate(UBitmap &bmp, MDMatrix<double> &output)
{

}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBALabelingSimple::AFBgDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBALabelingSimple::AFBgBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBALabelingSimple::AFBgReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBALabelingSimple::AFBgCalculate(void)
{
 Zones->Resize(0,4);

 UBColor *data=Input->GetData();

 for(int i=0;i<Input->GetLength();i++)
  if(*data++ >0)
  {
   Zones->Resize(1,4);
   (*Zones)(0,0)=0;
   (*Zones)(0,1)=0;
   (*Zones)(0,2)=Input->GetWidth();
   (*Zones)(0,3)=Input->GetHeight();
   break;
  }

// LCalculate(*Input, *Zones);
 return true;
}
// --------------------------


}
//---------------------------------------------------------------------------

#endif
