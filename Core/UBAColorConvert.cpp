/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAColorConvert_CPP
#define UBAColorConvert_CPP

#include <math.h>
#include "UBAColorConvert.h"
//#include "../../UGraphicsBinarySerialize.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBAColorConvert::UBAColorConvert(void)
: NewColorModel("NewColorModel",this),
  Input("Input",this),
  Output("Output",this)
{
}
UBAColorConvert::~UBAColorConvert(void)
{
}
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBAColorConvert* UBAColorConvert::New(void)
{
 return new UBAColorConvert;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAColorConvert::ADefault(void)
{
 NewColorModel=ubmY8;
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAColorConvert::ABuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBAColorConvert::AReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBAColorConvert::ACalculate(void)
{
// if(Outputs.GetSize()<1 || Inputs.GetSize()<1)
//  return true;

 Output->SetColorModel(NewColorModel,false);
 Input->ConvertTo(*Output);
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------

#endif


