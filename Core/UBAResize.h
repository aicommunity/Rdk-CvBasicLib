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

// ������� ����� ��������������� �����������
class UBAResize: public UBAbstract
{
protected: // ���������
// ����� ������
int NewWidth,NewHeight;

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
// ����� ������
int GetNewWidth(void) const;
int GetNewHeight(void) const;
bool SetNewWidth(int value);
bool SetNewHeight(int value);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
virtual bool PLACalculate(UBitmap **input, UBitmap **output, int num_inputs=1, int num_outputs=1);
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
};

// �������� ������ ����������� �� ������� ������� ������
class UBAResizeEdges: public UBAResize
{
public: // ������
// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBAResizeEdges* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------
};

//extern UBAResizeEdges UBResizeEdges;
}
//---------------------------------------------------------------------------
#endif
