/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBACrop_CPP
#define UBACrop_CPP

#include <math.h>
#include "UBACrop.h"
#include "../../UGraphicsBinarySerialize.h"

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBACrop::UBACrop(void)
: Input("Input",this,0),
  CropRect("CropRect",this,1),
  Output("Output",this,0)
{
}
UBACrop::~UBACrop(void)
{
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------

// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBACrop* UBACrop::New(void)
{
 return new UBACrop;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBACrop::ADefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBACrop::ABuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBACrop::AReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBACrop::ACalculate(void)
{
 if(!Input || !Output)
  return true;

 Output->SetRes(CropRect->Width, CropRect->Height, Input->GetColorModel());
 Input->GetRect(CropRect->X,CropRect->Y, *Output);
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------

#endif


