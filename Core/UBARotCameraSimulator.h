/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAROT_CAMERA_SIMULATOR_H
#define UBAROT_CAMERA_SIMULATOR_H

#include "../../../Rdk/Deploy/Include/rdk.h"
#include "UBAVideoSimulator.h"

namespace RDK {


/// ������������ ��������� ������� ��������� ����
class RDK_LIB_TYPE UBARotCameraSimulator: public UBAVideoSimulatorSimple
{
protected: // ���������

/// �������� �����������
UPropertyOutputData<UBitmap, UBARotCameraSimulator, ptOutput | ptPubState> ViewOutput;
/// ������ ���� ������, ������������ ���� �����
/// �������� ViewOutputX = Input / ViewResizeCoef
/// �������� ����������� � ������
UPropertyOutputData<UBitmap, UBARotCameraSimulator, ptOutput | ptPubState> BorderOutput;

ULProperty<double, UBARotCameraSimulator, ptPubParameter> ViewResizeCoef;
/// �������� �������� ���� ������ �� ���� �����
/// � ��������� ������ �������������� ��������� �� ��������� ������,
/// ���������� �� ��������� ������������ �������
/// (�������, ����� �����)
ULProperty<double, UBARotCameraSimulator, ptPubParameter> XSpeedCoef;
ULProperty<double, UBARotCameraSimulator, ptPubParameter> YSpeedCoef;

/// ������� ������, ����������� ��������� ���� ������ �� ���� �����
UPropertyInputData<MDMatrix<double>,UBARotCameraSimulator, ptInput | ptPubState> MoveLeftSignal;
UPropertyInputData<MDMatrix<double>,UBARotCameraSimulator, ptInput | ptPubState> MoveRightSignal;
UPropertyInputData<MDMatrix<double>,UBARotCameraSimulator, ptInput | ptPubState> MoveTopSignal;
UPropertyInputData<MDMatrix<double>,UBARotCameraSimulator, ptInput | ptPubState> MoveBottomSignal;


protected: // ������
/// ������ ���� ������ � ��������
int ViewX, ViewY;
/// ����� ���� ������ ������������ ���� ����� � ��������
int ViewShiftX, ViewShiftY;
/// ������� ������
int frame_counter;


public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBARotCameraSimulator(void);
virtual ~UBARotCameraSimulator(void);
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
/// ������ ���� ������, ������������ ���� �����
/// �������� ViewOutputX = Input / ViewResizeCoef
inline double GetViewResizeCoef(void) { return ViewResizeCoef; };
bool SetViewResizeCoef(double const &new_vol);
/// ������ ���� ������ � ��������
inline int GetViewWinX(void) { return ViewX; };
inline int GetViewWinY(void) { return ViewY; };
/// �������� �������� ���� ������ �� ���� �����
/// � ��������� ������ �������������� ��������� �� ��������� ������,
/// ���������� �� ��������� ������������ �������
/// (�������, ����� �����)
inline double GetXSpeedCoef(void) { return XSpeedCoef; };
inline double GetYSpeedCoef(void) { return YSpeedCoef; };
bool SetXSpeedCoef(double const &new_vol);
bool SetYSpeedCoef(double const &new_vol);
/// ����� ���� ������ ������������ ���� ����� � ��������
inline int GetViewShiftX(void) { return ViewShiftX; };
inline int GetViewShiftY(void) { return ViewShiftY; };
// ---------------------

// ---------------------
// ������ �����
// ---------------------
/// �������� ����� ����� ����� �������
virtual UBARotCameraSimulator* New(void);
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
protected:

/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFSDefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFSBuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AFSReset(void);

/// ��������� ������ ����� �������
virtual bool AFSCalculate(void);
// --------------------------
};

}

#endif

