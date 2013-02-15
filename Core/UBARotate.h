/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBARotateH
#define UBARotateH
#include "../../UBAbstract.h"

namespace RDK {

/// ������� ����� �������� �����������
class UBARotate: public UBAbstract
{
protected: // ���������
/// ���� �������� (�������)
float Angle;

/// ���� ����������
bool Enlarge;

protected: // ������� � �������� ������
/// ������� �����������
UEPtr<UBitmap> Input;

/// �������� �����������
UEPtr<UBitmap> Output;

protected: // ��������� ����������
UBitmap Buffer;

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBARotate(void);
virtual ~UBARotate(void);
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
/// ���� �������� (�������)
float GetAngle(void) const;
bool SetAngle(float angle);

/// ���� ����������
bool GetEnlarge(void) const;
bool SetEnlarge(bool enlarge);
// ---------------------

// ---------------------
// ���������
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, UBitmap &output, float angle, bool enlarge=false);
// ---------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFDefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFBuild(void);

/// ����� �������� �����.
virtual bool AFReset(void);

/// ��������� ������ ����� �������
virtual bool AFCalculate(void);
// --------------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFCDefault(void)=0;

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFCBuild(void)=0;

/// ����� �������� �����.
virtual bool AFCReset(void)=0;

/// ��������� ������ ����� �������
virtual bool AFCCalculate(void)=0;
// --------------------------
};

/// ������������ ����������� �� �������� ����
class UBARotateSimple: public UBARotate
{
public: // ������
// ---------------------
// ������ �����
// ---------------------
/// �������� ����� ����� ����� �������
virtual UBARotateSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFCDefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFCBuild(void);

/// ����� �������� �����.
virtual bool AFCReset(void);

/// ��������� ������ ����� �������
virtual bool AFCCalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif

