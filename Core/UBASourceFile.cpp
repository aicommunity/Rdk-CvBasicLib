/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBASOURCE_FILE_CPP
#define UBASOURCE_FILE_CPP

#include <algorithm>
#include "UBASourceFile.h"

namespace RDK {

// ������
// --------------------------
// ������������ � �����������
// --------------------------
UBASourceFile::UBASourceFile(void)
: FileName("FileName",this, &UBASourceFile::SetFileName)
{
}

UBASourceFile::~UBASourceFile(void)
{
}
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
bool UBASourceFile::SetFileName(const std::string &value)
{
 Ready=false;
 return true;
}
// --------------------------

// --------------------------
// ������ ���������� �������
// --------------------------
/// ���������� ������� ����, ��� ����������� ��� ���������
bool UBASourceFile::IsLoad(void) const
{
 return LoadFlag;
}
// --------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
UBASourceFile* UBASourceFile::New(void)
{
 return new UBASourceFile;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBASourceFile::ADefault(void)
{
 return true;
}

// ����� �������� �����.
bool UBASourceFile::AReset(void)
{
 LoadFlag=false;
 return true;
}

// ��������� ������ ����� �������
bool UBASourceFile::ACalculate(void)
{
 if(!IsLoad())
 {
  std::string::size_type i=FileName->find_last_of(".");
  if(i == std::string::npos)
   return true;
  std::string ext=FileName->substr(i+1);
  std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
  if(ext == "jpg" || ext == "jpeg")
  {
   if(LoadJpegFromFile(FileName->c_str(), *Output))
	LoadFlag=true;
  }
  else
  if(ext == "bmp")
  {
   if(LoadBitmapFromFile(FileName->c_str(), *Output))
	LoadFlag=true;
   Output->ReflectionX();
  }
 }
 return true;
}
// --------------------------
}
#endif


