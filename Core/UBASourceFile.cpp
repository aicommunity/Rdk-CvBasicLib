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

// Методы
// --------------------------
// Конструкторы и деструкторы
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
// Методы управления параметрами
// --------------------------
bool UBASourceFile::SetFileName(const std::string &value)
{
 Ready=false;
 return true;
}
// --------------------------

// --------------------------
// Методы управления данными
// --------------------------
/// Возвращает признак того, что изображение уже загружено
bool UBASourceFile::IsLoad(void) const
{
 return LoadFlag;
}
// --------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UBASourceFile* UBASourceFile::New(void)
{
 return new UBASourceFile;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBASourceFile::ADefault(void)
{
 return true;
}

// Сброс процесса счета.
bool UBASourceFile::AReset(void)
{
 LoadFlag=false;
 return true;
}

// Выполняет расчет этого объекта
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


