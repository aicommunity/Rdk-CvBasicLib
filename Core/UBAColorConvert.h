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

// ������� ����� ��������������� �����������
class UBAColorConvert: public UBAbstract
{
protected: // ���������
// ����� ����� �����������
int NewColorModel;

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
// ����� ����� �����������
int GetNewColorModel(void) const;
bool SetNewColorModel(int value);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
virtual bool PLACalculate(UBitmap **input, UBitmap **output, int num_inputs=1, int num_outputs=1);
virtual bool BCalculate(UBitmap &input, UBitmap &output);
bool BCalculate(UBitmap &input, int color_model);
bool BCalculate(UBitmap &input, UBitmap &output, int color_model);
// ---------------------

// ---------------------
// ���������
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, int color_model);
bool operator () (UBitmap &input, UBitmap &output, int color_model);  //?
};
// ---------------------
};
//---------------------------------------------------------------------------
#endif
