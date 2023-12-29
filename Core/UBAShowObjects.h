/* ***********************************************************
@Copyright Aleksandr Bakhshiev, 2011.
E-mail:        palexab@gmail.com
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAShowObjectsH
#define UBAShowObjectsH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// ������� ����� ����������� ��������
class RDK_LIB_TYPE UBAShowObjects: public UNet
{
protected: // ���������
/// ���� �����
UProperty<RDK::UColorT,UBAShowObjects, ptPubParameter> PenColor;

/// ������� �����
UProperty<int,UBAShowObjects, ptPubParameter> PenWidth;

/// ���� ���������� ���������
UProperty<bool,UBAShowObjects, ptPubParameter> EnableShowFlag;

public: // ������� � �������� ������
/// ������� �����������
UPropertyInputData<UBitmap, UBAShowObjects> Input;

/// �������� �����������
UPropertyOutputData<UBitmap, UBAShowObjects> Output;

/// ������ ������ ��������� ��������
/// ������� ��� ������� ���� �� ���������� ���������� ���� �� ���������
UPropertyInputData<std::vector<UColorT>, UBAShowObjects, ptPubInput | ptParameter> ObjectsColor;

/// ������ ���� ��������
UPropertyInputData<std::vector<std::string>, UBAShowObjects, ptPubInput | ptParameter> ObjectsName;

/// ������ ��������������� ��������
UPropertyInputData<MDMatrix<int>, UBAShowObjects, ptPubInput | ptParameter> ObjectsId;


protected: // ������
UBitmap Canvas;
UGraphics Graphics;

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBAShowObjects(void);
virtual ~UBAShowObjects(void);
// ---------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
bool SetActivity(const bool &activity);
// --------------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool ABuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AReset(void);

/// ��������� ������ ����� �������
virtual bool ACalculate(void);
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� ����������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFSDefault(void)=0;

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFSBuild(void)=0;

/// ����� �������� ����� ��� ������ ��������
virtual bool AFSReset(void)=0;

/// ��������� ������ ����� �������
virtual bool AFSCalculate(void)=0;
// --------------------------
};

// ����� ����������� ��������-�����
class RDK_LIB_TYPE UBAShowObjectsSimple: public RDK::UBAShowObjects
{
protected: // ���������������� ������
/// ��������� �� �������� ������
UPropertyInputData<std::vector<UBPoint>, UBAShowObjectsSimple> Zones;

/// ��������� �� �������� ������
UPropertyInputData<MDMatrix<double>, UBAShowObjectsSimple> MatrixPoints;

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBAShowObjectsSimple(void);
virtual ~UBAShowObjectsSimple(void);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
/// �������� ����� ����� ����� �������
virtual UBAShowObjectsSimple* New(void);
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ����������
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
//---------------------------------------------------------------------------
#endif
