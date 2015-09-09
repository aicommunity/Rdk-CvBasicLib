/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBAFlipImage.h"
#include <math.h>
#include <string.h>

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBAFlipImage::UBAFlipImage(void)
: Mode("Mode",this),
  Input("Input",this),
  Output("Output",this)
{
}

UBAFlipImage::~UBAFlipImage(void)
{
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAFlipImage::ADefault(void)
{
 Mode=0;
 return AFCDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAFlipImage::ABuild(void)
{
 return AFCBuild();
}

// ����� �������� �����.
bool UBAFlipImage::AReset(void)
{
 return AFCReset();
}

// ��������� ������ ����� �������
bool UBAFlipImage::ACalculate(void)
{
 return AFCCalculate();
}
// --------------------------



// ������������ ����������� �� �������� ����
// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBAFlipImageSimple* UBAFlipImageSimple::New(void)
{
 return new UBAFlipImageSimple;
}

bool UBAFlipImageSimple::BCalculate(UBitmap &input, UBitmap &output)
{
 switch(Mode)
 {
 case 1:
  input.ReflectionX(&output);
 break;

 case 2:
  input.ReflectionY(&output);
 break;

 }

 return true;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAFlipImageSimple::AFCDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAFlipImageSimple::AFCBuild(void)
{
 return true;
}

// ����� �������� �����.
bool UBAFlipImageSimple::AFCReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBAFlipImageSimple::AFCCalculate(void)
{
 return BCalculate(*Input, *Output);
}
// --------------------------
}
//---------------------------------------------------------------------------

