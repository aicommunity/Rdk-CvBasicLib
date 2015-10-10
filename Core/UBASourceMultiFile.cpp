/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBASOURCE_MULTI_FILE_CPP
#define UBASOURCE_MULTI_FILE_CPP

#include "UBASourceMultiFile.h"

namespace RDK {

// Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBASourceMultiFile::UBASourceMultiFile(void)
 : FileNames("FileNames",this, &UBASourceMultiFile::SetFileNames)
{
 BuildFlag=false;
}

UBASourceMultiFile::~UBASourceMultiFile(void)
{
 for(size_t i=0;i<DynamicOutputs.size();i++)
  delete DynamicOutputs[i];
}
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
bool UBASourceMultiFile::SetFileNames(const std::vector<std::string> &value)
{
 Ready=false;
 return true;
}
// --------------------------

// --------------------------
// Методы управления данными
// --------------------------
/// Проверяет были ли загружены изображения
bool UBASourceMultiFile::IsLoad(void) const
{
 return LoadFlag;
}
// --------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UBASourceMultiFile* UBASourceMultiFile::New(void)
{
 return new UBASourceMultiFile;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBASourceMultiFile::ADefault(void)
{
 return true;
}

bool UBASourceMultiFile::ABuild(void)
{
 if(BuildFlag)
  return true;
 BuildFlag=true;
 for(size_t i=FileNames->size();i<DynamicOutputs.size();i++)
 {
  DisconnectAll(DynamicOutputs[i]->GetName());
  DelLookupProperty(DynamicOutputs[i]->GetName());
  delete DynamicOutputs[i];
  DynamicOutputs[i]=0;
 }

 for(size_t i=DynamicOutputs.size();i<FileNames->size();i++)
 {
  UPropertyOutputData<UBitmap,UBASourceMultiFile> *output=new UPropertyOutputData<UBitmap,UBASourceMultiFile>(std::string("Output")+sntoa(i+1),this,false);
  DynamicOutputs.push_back(output);
 }
 DynamicOutputs.resize(FileNames->size());

 BuildFlag=false;
 return true;
}


// Сброс процесса счета.
bool UBASourceMultiFile::AReset(void)
{
 LoadFlags.assign(FileNames->size(),false);
 LoadFlag=false;
 return true;
}

// Выполняет расчет этого объекта
bool UBASourceMultiFile::ACalculate(void)
{
 if(!IsLoad())
 {
  LoadFlag=true;
  for(size_t j=0;j<FileNames->size();j++)
  {
   if(!LoadFlags[j])
   {
	std::string::size_type i=(*FileNames)[j].find_last_of(".");
	if(i == std::string::npos)
	 return true;
	std::string ext=(*FileNames)[j].substr(i+1);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
	if(ext == "jpg" || ext == "jpeg")
	{
	 if(LoadJpegFromFile((*FileNames)[j].c_str(), **DynamicOutputs[j]))
	  LoadFlags[j]=true;
	}
	else
	if(ext == "bmp")
	{
	 if(LoadBitmapFromFile((*FileNames)[j].c_str(), **DynamicOutputs[j]))
	  LoadFlags[j]=true;
	 (*DynamicOutputs[j])->ReflectionX();
	}
   }
   LoadFlag&=LoadFlags[j];
  }
 }
 return true;
}
// --------------------------
}
#endif


