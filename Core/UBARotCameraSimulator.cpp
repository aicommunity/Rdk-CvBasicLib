/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAROT_CAMERA_SIMULATOR_CPP
#define UBAROT_CAMERA_SIMULATOR_CPP

#include "UBARotCameraSimulator.h"
//#include "../../UGraphics.h"
//#include "../../UGraphicsXMLSerialize.h"
//#include "../../UGraphicsBinarySerialize.h"
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBARotCameraSimulator::UBARotCameraSimulator(void)
: ViewOutput("ViewOutput",this),
  BorderOutput("BorderOutput",this),
  ViewResizeCoef("ViewResizeCoef",this),
  XSpeedCoef("XSpeedCoef",this),
  YSpeedCoef("YSpeedCoef",this),
  MoveLeftSignal("MoveLeftSignal",this),
  MoveRightSignal("MoveRightSignal",this),
  MoveTopSignal("MoveTopSignal",this),
  MoveBottomSignal("MoveBottomSignal",this)
{
 Graphics=new UGraphics;
 /// ������� ������
 frame_counter = 0;
}

UBARotCameraSimulator::~UBARotCameraSimulator(void)
{
 if(Graphics)
 {
  delete Graphics;
  Graphics=0;
 }
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
/// ������ ���� ������, ������������ ���� �����
/// �������� ViewOutputX = Input / ViewResizeCoef
bool UBARotCameraSimulator::SetViewResizeCoef(const double &new_vol)
{
	if(new_vol < 1)
        return false;

	//ViewResizeCoef = new_vol;
	Ready = false;

	return true;
}
/// �������� �������� ���� ������ �� ���� �����
/// � ��������� ������ �������������� ��������� �� ��������� ������,
/// ���������� �� ��������� ������������ �������
/// (�������, ����� �����)
bool UBARotCameraSimulator::SetXSpeedCoef(double const &new_vol)
{
	//XSpeedCoef = new_vol;

	return true;
}
bool UBARotCameraSimulator::SetYSpeedCoef(double const &new_vol)
{
	//YSpeedCoef = new_vol;

	return true;
}
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBARotCameraSimulator *UBARotCameraSimulator::New(void)
{
 return new UBARotCameraSimulator;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBARotCameraSimulator::AFSDefault(void)
{
 if(!UBAVideoSimulatorSimple::AFSDefault())
	return false;

 // ������ ���� ������, ������������ ���� �����
 // �������� ViewOutputX = Input / ViewResizeCoef
 ViewResizeCoef = 2.0;
 // �������� �������� ���� ������ �� ���� �����
 // � ��������� ������ �������������� ��������� �� ��������� ������,
 // ���������� �� ��������� ������������ �������
 // (�������, ����� �����)
 XSpeedCoef = 1.2;
 YSpeedCoef = 1.2;

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBARotCameraSimulator::AFSBuild(void)
{
 if(!UBAVideoSimulatorSimple::AFSBuild())
	return false;

 // ������ ���� ������, ������������ ���� �����
 // �������� ViewOutputX = Input / ViewResizeCoef
 // --->
 ViewY = 100;//int(double(Input->GetHeight()) / ViewResizeCoef);
 //ViewX = int(double(Input->GetWidth()) / ViewResizeCoef);
 ViewX = 100;//ViewY;
 ViewOutput->SetRes(ViewX,ViewY,Input->GetColorModel());
 // <---

 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBARotCameraSimulator::AFSReset(void)
{
 if(!UBAVideoSimulatorSimple::AFSReset())
	return false;

 /// ����� ���� ������ ������������ ���� ����� � ��������
 ViewShiftX = 0;
 ViewShiftY = 0;

 return true;
}

#ifdef __BORLANDC__
#pragma warn -8058
#endif
// ��������� ������ ����� �������
bool UBARotCameraSimulator::AFSCalculate(void)
{
 if(!UBAVideoSimulatorSimple::AFSCalculate())
	return false;

 // ��������� ����� ������ ������ ������ �� ������ �����
 ViewShiftX += int(((*MoveRightSignal)(0,0) - (*MoveLeftSignal)(0,0))*XSpeedCoef);
 ViewShiftY += int(((*MoveBottomSignal)(0,0) - (*MoveTopSignal)(0,0))*YSpeedCoef);

 int shift;
 bool is_saccades = true;
 if(is_saccades)
 {
	switch(frame_counter%4)
	{
		case 0: shift = 0; break;
		case 1: case 3: shift = 1; break;
		case 2: shift = 2; break;
 	}
 }

 // ��������� ����� �������� ������ ������ � ������ �����
 int start_x, start_y;
 start_x = (Input->GetWidth() - ViewX) / 2;
 start_x += ViewShiftX;
 if(is_saccades) start_x += shift;
 if(start_x < 0) start_x = 0;
 if(start_x > Input->GetWidth() - ViewX - 1) start_x = Input->GetWidth() - ViewX - 1;
 start_y = (Input->GetHeight() - ViewY) / 2;
 start_y += ViewShiftY;
 if(is_saccades) start_y += shift;
 if(start_y < 0) start_y = 0;
 if(start_y > Input->GetHeight() - ViewY - 1) start_x = Input->GetHeight() - ViewY - 1;

 // �������� ���� ������
 Output->GetRect(start_x,start_y,*ViewOutput);

 // ������� ������
 frame_counter++;

 // ����� � ������
 *BorderOutput = *Output;
 const UBRect rect1(start_x,start_y,ViewX,2);
 const UBRect rect2(start_x,start_y+ViewY,ViewX,2);
 const UBRect rect3(start_x,start_y,2,ViewY);
 const UBRect rect4(start_x+ViewX,start_y,2,ViewY);
 BorderOutput->Fill(0x00000000,rect1);
 BorderOutput->Fill(0x00000000,rect2);
 BorderOutput->Fill(0x00000000,rect3);
 BorderOutput->Fill(0x00000000,rect4);

 return true;

}
#ifdef __BORLANDC__
#pragma warn .8058
#endif

}

#endif

