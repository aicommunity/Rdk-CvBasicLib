/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBASOURCE_CPP
#define UBASOURCE_CPP

#include "UBASource.h"

namespace RDK {

// ������
// --------------------------
// ������������ � �����������
// --------------------------
UBASource::UBASource(void)
: Output("Output",this)
{
}

UBASource::~UBASource(void)
{
}
// --------------------------

// --------------------------
// ������ ���������� �������
// --------------------------
// ��������������� ������ �������� �����������
bool UBASource::SetOutputData(int index, const UBitmap &bitmap)
{
 if(index<0 || index>0)
  return false;

 if(!Build())
  return false;

 *Output=bitmap;

 return true;
}
// --------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
UBASource* UBASource::New(void)
{
 return new UBASource;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBASource::ADefault(void)
{
 return true;
}

// ����� �������� �����.
bool UBASource::AReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBASource::ACalculate(void)
{
 return true;
}
// --------------------------
}
#endif


