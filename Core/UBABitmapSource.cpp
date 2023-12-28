/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBABitmapSource_CPP
#define UBABitmapSource_CPP

#include "UBABitmapSource.h"
//#include "../../UGraphics.h"
//#include "../../UGraphicsXMLSerialize.h"
//#include "../../UGraphicsBinarySerialize.h"
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABitmapSource::UBABitmapSource(void)
: Output("Output",this),
  SourceParamaters("SourceParamaters",this)
{
}

UBABitmapSource::~UBABitmapSource(void)
{
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABitmapSource::ADefault(void)
{
 return AFSDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABitmapSource::ABuild(void)
{
// SourceParamaters.resize(NumOutputs);
 return AFSBuild();
}

// Сброс процесса счета без потери настроек
bool UBABitmapSource::AReset(void)
{
 return AFSReset();
}

// Выполняет расчет этого объекта
bool UBABitmapSource::ACalculate(void)
{
 for(int i=0;i<1;i++) // Заглушка!!
  Output->SetRes(SourceParamaters[i].Width,SourceParamaters[i].Height,SourceParamaters[i].ColorModel);
 return AFSCalculate();
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABitmapSource::AFSDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABitmapSource::AFSBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBABitmapSource::AFSReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBABitmapSource::AFSCalculate(void)
{
 return true;
}
// --------------------------


/* UBABitmapSourceSimple */
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABitmapSourceSimple::UBABitmapSourceSimple(void)
{
}

UBABitmapSourceSimple::~UBABitmapSourceSimple(void)
{
}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBABitmapSourceSimple* UBABitmapSourceSimple::New(void)
{
 return new UBABitmapSourceSimple;
}

bool UBABitmapSourceSimple::BCalculate(void)
{

 return true;
}
// ---------------------


// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABitmapSourceSimple::AFSDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABitmapSourceSimple::AFSBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBABitmapSourceSimple::AFSReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBABitmapSourceSimple::AFSCalculate(void)
{
 return true;
}
// --------------------------

/* UBABitmapSourceSimple */
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABitmapSourceFile::UBABitmapSourceFile(void)
{
}

UBABitmapSourceFile::~UBABitmapSourceFile(void)
{
}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBABitmapSourceFile* UBABitmapSourceFile::New(void)
{
 return new UBABitmapSourceFile;
}
// ---------------------


// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABitmapSourceFile::AFSDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABitmapSourceFile::AFSBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBABitmapSourceFile::AFSReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBABitmapSourceFile::AFSCalculate(void)
{
 return true;
}
// --------------------------


// Методы UBASourceFreezeFrame
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBASourceFreezeFrame::UBASourceFreezeFrame(void)
: FreezeFlag("FreezeFlag",this)
{
}

UBASourceFreezeFrame::~UBASourceFreezeFrame(void)
{
}
// --------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UBASourceFreezeFrame* UBASourceFreezeFrame::New(void)
{
 return new UBASourceFreezeFrame;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBASourceFreezeFrame::ADefault(void)
{
 *FreezeFlag=false;
 return true;
}

// Сброс процесса счета.
bool UBASourceFreezeFrame::AReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBASourceFreezeFrame::ACalculate(void)
{
 if(*FreezeFlag)
 {
  *FreezeFlag=false;
  *Output=*Input;
 }

 return true;
}
// --------------------------

}

#endif

