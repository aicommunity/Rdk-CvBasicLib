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
#include "../../../Engine/UNet.h"
#include "../../UBitmap.h"

namespace RDK {

/// ����� �������������� �������� ������� �����������
class UBAColorConvert: public UNet
{
protected: // ���������
/// ����� ����� �����������
UBMColorModel NewColorModel;

protected: // ����� � ������
UPropertyInputData<UBitmap, UBAColorConvert> Input;

UPropertyOutputData<UBitmap, UBAColorConvert> Output;

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
};
}
//---------------------------------------------------------------------------
#endif
