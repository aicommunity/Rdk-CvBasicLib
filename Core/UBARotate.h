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

// ������� ����� �������� �����������
class UBARotate: public UBAbstract
{
protected: // ���������
// ���� �������� (�������)
float Angle;

// ���� ����������
bool Enlarge;

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
// ���� �������� (�������)
float GetAngle(void) const;
bool SetAngle(float angle);

// ���� ����������
bool GetEnlarge(void) const;
bool SetEnlarge(bool enlarge);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
virtual bool PLACalculate(UBitmap **input, UBitmap **output, int num_inputs=1, int num_outputs=1);
virtual bool BCalculate(UBitmap &input, UBitmap &output)=0;
bool BCalculate(UBitmap &input, UBitmap &output, float angle, bool enlarge=false);
bool BCalculate(UBitmap &input, float angle, bool enlarge=false);
// ---------------------

// ---------------------
// ���������
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, UBitmap &output, float angle, bool enlarge=false);
bool operator () (UBitmap &input, float angle, bool enlarge=false);
// ---------------------
};

// ������������ ����������� �� �������� ����
class UBARotateSimple: public UBARotate
{
public: // ������
// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBARotateSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------
};

//extern UBARotateSimple UBRotateSimple;
}
//---------------------------------------------------------------------------
#endif

