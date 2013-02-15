/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAResizeH
#define UBAResizeH
#include "../../UBAbstract.h"

namespace RDK {

/// ������� ����� ��������������� �����������
class UBAResize: public UBAbstract
{
protected: // ���������
/// ����� ������
int NewWidth,NewHeight;

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
UBAResize(void);
virtual ~UBAResize(void);
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
/// ����� ������
int GetNewWidth(void) const;
int GetNewHeight(void) const;
bool SetNewWidth(int value);
bool SetNewHeight(int value);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
virtual bool BCalculate(UBitmap &input, UBitmap &output)=0;
bool BCalculate(UBitmap &input, int width, int height);
bool BCalculate(UBitmap &input, UBitmap &output, int width, int height);
// ---------------------

// ---------------------
// ���������
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, int width, int height);
bool operator () (UBitmap &input, UBitmap &output, int width, int height);
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

/// �������� ������ ����������� �� ������� ������� ������
class UBAResizeEdges: public UBAResize
{
public: // ������
// ---------------------
// ������ �����
// ---------------------
/// �������� ����� ����� ����� �������
virtual UBAResizeEdges* New(void);

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
