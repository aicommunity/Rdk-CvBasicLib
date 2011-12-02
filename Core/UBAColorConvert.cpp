/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBARESIZE_CPP
#define UBARESIZE_CPP

#include "UBAColorConvert.h"
#include <math.h>

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBAColorConvert::UBAColorConvert(void)
{
 NewColorModel=ubmY8;
}
UBAColorConvert::~UBAColorConvert(void)
{
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ����� ����� �����������
int UBAColorConvert::GetNewColorModel(void) const
{
 return NewColorModel;
}

bool UBAColorConvert::SetNewColorModel(int value)
{
 if(NewColorModel == value)
  return true;

 NewColorModel=value;
 return true;
}
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBAColorConvert* UBAColorConvert::New(void)  //?
{
 return new UBAColorConvert;
}

//�� �����, ������
bool UBAColorConvert::PLACalculate(UBitmap **input, UBitmap **output, int num_inputs, int num_outputs)
{
  return BCalculate(*input[InputTable[0]], *output[OutputTable[0]]);
}

bool UBAColorConvert::BCalculate(UBitmap &input, UBitmap &output)
{
 input.ConvertTo(output);
 return true;
}

bool UBAColorConvert::BCalculate(UBitmap &input, int color_model)
{
 // ��� �������� �� ���������� ��������
 if(input.GetColorModel() == color_model)
  return true;

 SetNewColorModel(color_model);
 return input.SetColorModel(NewColorModel);
}

bool UBAColorConvert::BCalculate(UBitmap &input, UBitmap &output, int color_model)
{
 SetNewColorModel(color_model);
 return BCalculate(input,output);
}
// ---------------------

// ---------------------
// ���������
// ---------------------
bool UBAColorConvert::operator () (UBitmap &input, UBitmap &output)
{
 return BCalculate(input,output);
}

bool UBAColorConvert::operator () (UBitmap &input, int color_model)
{
 return BCalculate(input,color_model);
}

bool UBAColorConvert::operator () (UBitmap &input, UBitmap &output, int color_model)
{
 return BCalculate(input,output, color_model);
}
// ---------------------


//
// ---------------------
// ������ �����
// ---------------------
}
//---------------------------------------------------------------------------

#endif


