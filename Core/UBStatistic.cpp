/* ***********************************************************
@Copyright Aleksandr Bakhshiev, 2012.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBStatistic_CPP
#define UBStatistic_CPP
#include "UBStatistic.h"
#include <math.h>
//#include "../../UGraphicsXMLSerialize.h"
//#include "../../../System/rdk_system.h"
//#include "../../UGraphicsIO.h"
//#include "../../../Engine/UEnvironment.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

//UBStatisticRect UBGuiSelectionRect;

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBStatistic::UBStatistic(void)
: FileFormat("FileFormat",this),
  FileNameSuffix("FileNameSuffix",this),
  ExcludeModelFileName("ExcludeModelFileName",this),
  UseManualStatistic("UseManualStatistic",this),
  ManualStatisticSwitch("ManualStatisticSwitch",this),
  Input("Input",this)
{
 AddLookupProperty("SavePath",ptPubParameter, new UVProperty<std::string,UBStatistic>(this,&SavePath));
 AddLookupProperty("SubFolderAfterResetFlag",ptPubParameter, new UVProperty<bool,UBStatistic>(this,&SubFolderAfterResetFlag));
 AddLookupProperty("ReflectionXFlag",ptPubParameter, new UVProperty<bool,UBStatistic>(this,&ReflectionXFlag));
 AddLookupProperty("PrefixName",ptPubParameter, new UVProperty<std::string,UBStatistic>(this,&PrefixName));
 AddLookupProperty("InputIndexMode",ptPubParameter, new UVProperty<int,UBStatistic>(this,&InputIndexMode));

 AddLookupProperty("TimeToFileNameFlag",ptPubParameter, new UVProperty<bool,UBStatistic>(this,&TimeToFileNameFlag));
 AddLookupProperty("OrderIndexToFileNameFlag",ptPubParameter, new UVProperty<bool,UBStatistic>(this,&OrderIndexToFileNameFlag));

 AddLookupProperty("NumSkipSteps",ptPubParameter, new UVProperty<int,UBStatistic>(this,&NumSkipSteps));
}

UBStatistic::~UBStatistic(void)
{

}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
bool UBStatistic::SetSavePath(const std::string &value)
{
 SavePath=value;
 return true;
}

bool UBStatistic::SetPrefixName(const std::string &value)
{
 PrefixName=value;
 return true;
}

bool UBStatistic::SetSubFolderAfterResetFlag(bool value)
{
 SubFolderAfterResetFlag=value;
 return true;
}

bool UBStatistic::SetReflectionXFlag(bool value)
{
 ReflectionXFlag=value;
 return true;
}

bool UBStatistic::SetInputIndexMode(int value)
{
 InputIndexMode=value;
 return true;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBStatistic::ADefault(void)
{
 Activity=false;
 SubFolderAfterResetFlag=true;
 SavePath="StatisticLog";
 ReflectionXFlag=true;
 InputIndexMode=0;
 TimeToFileNameFlag=false;
 OrderIndexToFileNameFlag=true;
 NumSkipSteps=0;
 ExcludeModelFileName=true;
 FileNameSuffix=0;
 UseManualStatistic=false;
 FileFormat=1;
 return AFSDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBStatistic::ABuild(void)
{
 return AFSBuild();
}

// Сброс процесса счета без потери настроек
bool UBStatistic::AReset(void)
{
 ResetFlag=true;

 OldTimeStamp=0;
 CurrentFileNameNumber=1;
 CurrentFileIndex=0;
 CurrentStep=0;
 ManualStatisticSwitch=false;

 return AFSReset();
}

// Выполняет расчет этого объекта
bool UBStatistic::ACalculate(void)
{
 if(CurrentStep<NumSkipSteps)
 {
  ++CurrentStep;
  return true;
 }
 ++CurrentStep;

 if(Input->empty())
  return true;

 if(UseManualStatistic)
 {
  if(!ManualStatisticSwitch)
   return true;

  ManualStatisticSwitch=false;
 }

 if(SubFolderAfterResetFlag && ResetFlag)
 {
  if(RDK::CreateNewDirectory((Environment->GetCurrentDataDir()+SavePath).c_str()))
   return false; // Заглушка!! здесь исключение

  time_t time_data;
  time(&time_data);
  if(!PrefixName.empty())
   CurrentPath=Environment->GetCurrentDataDir()+SavePath+std::string("/")+PrefixName+std::string(" ")+get_text_time(time_data,'.','-');
  else
   CurrentPath=Environment->GetCurrentDataDir()+SavePath+std::string("/")+get_text_time(time_data,'.','-');
  if(RDK::CreateNewDirectory(CurrentPath.c_str()))
   return false; // Заглушка!! здесь исключение
 }

 if(InputIndexMode == 1)
 {
  for(int i=0;i<int(Input->size());i++)
   if(RDK::CreateNewDirectory((CurrentPath+std::string("/")+sntoa(i)).c_str()))
	return false; // Заглушка!! здесь исключение
 }

 ResetFlag=false;

 time_t time_data;
 time(&time_data);
 std::string new_file_name;
 if(!PrefixName.empty())
  new_file_name=PrefixName;

 if(!new_file_name.empty())
  new_file_name+=std::string(" ");

 if(OrderIndexToFileNameFlag)
 {
  new_file_name+=sntoa(CurrentFileIndex,8)+std::string(" ");
 }

 if(TimeToFileNameFlag)
 {
  new_file_name+=get_text_time(time_data,'.','-')+std::string(" ");
 }

 if(OldTimeStamp && OldTimeStamp != time_data)
 {
  CurrentFileNameNumber=1;
  CurrentFileName=new_file_name+sntoa(CurrentFileNameNumber,2);
 }
 else
 {
  ++CurrentFileNameNumber;
  CurrentFileName=new_file_name+sntoa(CurrentFileNameNumber,2);
 }
 OldTimeStamp=time_data;

 bool res=AFSCalculate();
 ++CurrentFileIndex;
 return res;
}
// --------------------------

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBStatisticSimple::UBStatisticSimple(void)
{
 AddLookupProperty("TimeInterval",ptPubParameter, new UVProperty<int,UBStatisticSimple>(this,&TimeInterval));
 AddLookupProperty("Mode",ptPubParameter, new UVProperty<int,UBStatisticSimple>(this,&Mode));
 AddLookupProperty("WriteSignal",ptPubState, new UVProperty<bool,UBStatisticSimple>(this,&WriteSignal));
}

UBStatisticSimple::~UBStatisticSimple(void)
{

}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
bool UBStatisticSimple::SetTimeInterval(int value)
{
 TimeInterval=value;
 return true;
}

bool UBStatisticSimple::SetMode(int value)
{
 Mode=value;
 return true;
}

bool UBStatisticSimple::SetWriteSignal(bool value)
{
 WriteSignal=value;
 return true;
}
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBStatisticSimple* UBStatisticSimple::New(void)
{
 return new UBStatisticSimple;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров сплиттинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBStatisticSimple::AFSDefault(void)
{
 TimeInterval=0;
 ReflectionXFlag=true;
 WriteSignal=false;
 Mode=0;
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBStatisticSimple::AFSBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBStatisticSimple::AFSReset(void)
{
 LastSaveTime=GetTime().GetSourceCurrentLocalTimeMs();
 WriteSignal=false;
 return true;

}

// Выполняет расчет этого объекта
bool UBStatisticSimple::AFSCalculate(void)
{
 if(Mode == 0 || Mode == 1)
 {
  if(TimeInterval > 0)
  {
   if(int(GetTime().GetSourceCurrentLocalTimeMs()-LastSaveTime)<TimeInterval)
	return true;
  }

  if(Mode == 1)
  {
   if(WriteSignal)
   {
	WriteSignal=false;
	Save();
    LastSaveTime=GetTime().GetSourceCurrentLocalTimeMs();
   }
  }
  else
  {
   Save();
   LastSaveTime=GetTime().GetSourceCurrentLocalTimeMs();
  }
 }

 return true;
}

// Осуществляет сохранение текущих данных
bool UBStatisticSimple::Save(void)
{
 std::vector<UCItem> c_items;
 if(FileNameSuffix == 1)
  UConnector::GetCItem("Input", c_items);
  for(int i=0;i<Input.GetNumPointers();i++)
  {
   if(!Input[i])
    continue;
   std::string final_path;
   if(InputIndexMode == 0)
   {
	final_path=CurrentPath+std::string("/");
   }
   else
   if(InputIndexMode == 1)
   {
	final_path=CurrentPath+std::string("/")+sntoa(i)+std::string("/");
   }

   std::string file_suffix;
   if(FileNameSuffix == 1)
	c_items[i].Item->GetFullName(file_suffix);
   else
    file_suffix=sntoa(i);
   if(FileNameSuffix == 1 && ExcludeModelFileName)
   {
	std::string::size_type i=file_suffix.find_first_of(".");
	if(i != std::string::npos)
	{
	 file_suffix.erase(0, i+1);
	}
   }




   UBitmap* temp_bmp(0);
   if((ReflectionXFlag && FileFormat == 0) ||
      (!ReflectionXFlag && FileFormat == 1))
   {
	Input[i]->ReflectionX(&TempBitmap);
	temp_bmp=&TempBitmap;
   }
   else
	temp_bmp=&(*(*Input)[i]);

   if(FileFormat == 0)
	SaveBitmapToFile((final_path+CurrentFileName+std::string("_")+file_suffix+std::string(".bmp")).c_str(), TempBitmap);
   else
   {
	if(temp_bmp->GetColorModel() != ubmRGB24)
	{
	 Rgb24TempBitmap.SetColorModel(ubmRGB24,false);
	 temp_bmp->ConvertTo(Rgb24TempBitmap);
	 temp_bmp=&Rgb24TempBitmap;
	}

	if(!ConvertBitmapToJpeg(*temp_bmp, jpeg_buf, temp_buf, false))
	{
	 if(!SaveFileBin(final_path+CurrentFileName+std::string("_")+file_suffix+std::string(".jpg"), jpeg_buf))
	 {
	  LogMessageEx(RDK_EX_WARNING, std::string("Unable to save file ")+final_path+CurrentFileName+std::string("_")+file_suffix+std::string(".jpg"));
	 }
	}
   }
  }
 return true;
}
// --------------------------


}
#endif

