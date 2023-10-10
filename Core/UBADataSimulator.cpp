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
// ������������ � �����������
// ---------------------
UBADataSimulator::UBADataSimulator(void)
{
}

UBADataSimulator::~UBADataSimulator(void)
{
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBADataSimulator::ADefault(void)
{
 return AFSDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBADataSimulator::ABuild(void)
{
 return AFSBuild();
}

// ����� �������� ����� ��� ������ ��������
bool UBADataSimulator::AReset(void)
{
 return AFSReset();
}

// ��������� ������ ����� �������
bool UBADataSimulator::ACalculate(void)
{
 return AFSCalculate();
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBADataSimulator::AFSDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBADataSimulator::AFSBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBADataSimulator::AFSReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBADataSimulator::AFSCalculate(void)
{
 return true;
}
// --------------------------


/* UBADataSimulatorSimple */
// ---------------------
// ������������ � �����������
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
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBADataSimulatorSimple* UBADataSimulatorSimple::New(void)
{
 return new UBADataSimulatorSimple;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
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

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBADataSimulatorSimple::AFSBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBADataSimulatorSimple::AFSReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBADataSimulatorSimple::AFSCalculate(void)
{
 return true;
}
// --------------------------


}

#endif

