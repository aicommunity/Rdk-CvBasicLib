/* ***********************************************************
@Copyright Alexander V. Bakhshiev.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBMathOperatorH
#define UBMathOperatorH

//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

// �������� �������������� �������� � �������������
enum { ubmAnd=0, ubmOr=1, ubmXor=2, ubmNot=3, ubmSum=4, ubmSub=5, ubmSubAbs=6 };

// ������� ����� ��������������� �����������
class RDK_LIB_TYPE UBMathOperator: public UNet
{
protected: // ���������
// ������������� ���������
int OperatorId;

protected: // ����� � ������
/// �������� 1
UPropertyInputData<UBitmap, UBMathOperator> Input1;

/// �������� 2
UPropertyInputData<UBitmap, UBMathOperator> Input2;

/// �������������� �����������
UPropertyOutputData<UBitmap, UBMathOperator> Output;

protected: // ��������� ����������
UBitmap Buffer;

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBMathOperator(void);
virtual ~UBMathOperator(void);
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ������������� ���������
const int& GetOperatorId(void) const;
bool SetOperatorId(const int &value);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBMathOperator* New(void);
// ---------------------


// --------------------------
// ������, ����������� �������������� ��������
// --------------------------
void And(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Or(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Sub(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Sum(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
// --------------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
protected:
// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
virtual bool ABuild(void);

// ����� �������� ����� ��� ������ ��������
virtual bool AReset(void);

// ��������� ������ ����� �������
virtual bool ACalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif

