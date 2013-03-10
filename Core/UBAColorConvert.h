/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAColorConvertH
#define UBAColorConvertH
#include "../../UBAbstract.h"

namespace RDK {

/// ����� �������������� �������� ������� �����������
class UBAColorConvert: public UBAbstract
{
protected: // ���������
/// ����� ����� �����������
UBMColorModel NewColorModel;

protected: // ��������� ����������
UBitmap Buffer;   //?

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBAColorConvert(void);
virtual ~UBAColorConvert(void);
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
/// ����� ����� �����������
const UBMColorModel& GetNewColorModel(void) const;
bool SetNewColorModel(const UBMColorModel &value);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
UBAColorConvert* New(void);
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFDefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFBuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AFReset(void);

/// ��������� ������ ����� �������
virtual bool AFCalculate(void);
// --------------------------
};
}
//---------------------------------------------------------------------------
#endif
