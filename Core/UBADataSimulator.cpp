/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBADATA_SIMULATOR_CPP
#define UBADATA_SIMULATOR_CPP

#include "UBADataSimulator.h"
//#include "../../UGraphics.h"
//#include "../../UGraphicsXMLSerialize.h"
//#include "../../UGraphicsBinarySerialize.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBADataSimulator::UBADataSimulator(void)
{
}

UBADataSimulator::~UBADataSimulator(void)
{
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBADataSimulator::ADefault(void)
{
 return AFSDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBADataSimulator::ABuild(void)
{
 return AFSBuild();
}

// Сброс процесса счета без потери настроек
bool UBADataSimulator::AReset(void)
{
 return AFSReset();
}

// Выполняет расчет этого объекта
bool UBADataSimulator::ACalculate(void)
{
 return AFSCalculate();
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBADataSimulator::AFSDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBADataSimulator::AFSBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBADataSimulator::AFSReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBADataSimulator::AFSCalculate(void)
{
 return true;
}
// --------------------------


/* UBADataSimulatorSimple */
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBADataSimulatorSimple::UBADataSimulatorSimple(void)
{
 AddLookupProperty("ScreenPoints",ptPubOutput | ptPubParameter, new UVPropertyOutputData<std::vector<MVector<double,2> >,UBADataSimulator>(this,&ScreenPoints));
 AddLookupProperty("PlanePoints",ptPubOutput | ptPubParameter, new UVPropertyOutputData<std::vector<MVector<double,3> >,UBADataSimulator>(this,&PlanePoints));
 AddLookupProperty("SpacePoints",ptPubOutput | ptPubParameter, new UVPropertyOutputData<std::vector<MVector<double,4> >,UBADataSimulator>(this,&SpacePoints));
}

UBADataSimulatorSimple::~UBADataSimulatorSimple(void)
{
}
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBADataSimulatorSimple* UBADataSimulatorSimple::New(void)
{
 return new UBADataSimulatorSimple;
}
// ---------------------


// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBADataSimulatorSimple::AFSDefault(void)
{
// SetNumOutputs(3);
// SetNumInputs(0);

// ScreenPoints.push_back(UBPoint(0,0));
 ScreenPoints.push_back(MVector<double,2>(0));
 PlanePoints.push_back(MVector<double,3>(0,0,1));
 SpacePoints.push_back(MVector<double,4>(0,0,0,1));

 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBADataSimulatorSimple::AFSBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBADataSimulatorSimple::AFSReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBADataSimulatorSimple::AFSCalculate(void)
{
 return true;
}
// --------------------------


}

#endif

