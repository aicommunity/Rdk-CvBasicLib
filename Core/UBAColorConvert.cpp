/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAColorConvert_CPP
#define UBAColorConvert_CPP

#include "UBAColorConvert.h"
#include <math.h>

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBAColorConvert::UBAColorConvert(void)
{
 AddLookupProperty("NewColorModel",new UVProperty<UBMColorModel,UBAColorConvert>(this,&UBAColorConvert::SetNewColorModel,&UBAColorConvert::GetNewColorModel));
}
UBAColorConvert::~UBAColorConvert(void)
{
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ����� ����� �����������
UBMColorModel UBAColorConvert::GetNewColorModel(void) const
{
 return NewColorModel;
}

bool UBAColorConvert::SetNewColorModel(UBMColorModel value)
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
UBAColorConvert* UBAColorConvert::New(void)
{
 return new UBAColorConvert;
}

//�� �����, ������
bool UBAColorConvert::PLACalculate(UBitmap **input, UBitmap **output, int num_inputs, int num_outputs)
{
 output[0]->SetColorModel(NewColorModel,false);
 return BCalculate(*input[0], *output[0]);
}

bool UBAColorConvert::BCalculate(UBitmap &input, UBitmap &output)
{
 input.ConvertTo(output);
 return true;
}

bool UBAColorConvert::BCalculate(UBitmap &input, UBMColorModel color_model)
{
 // ��� �������� �� ���������� ��������
 if(input.GetColorModel() == color_model)
  return true;

 SetNewColorModel(color_model);
 input.SetColorModel(NewColorModel);
 return true;
}

bool UBAColorConvert::BCalculate(UBitmap &input, UBitmap &output, UBMColorModel color_model)
{
 SetNewColorModel(color_model);
 output.SetColorModel(color_model,false);
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

bool UBAColorConvert::operator () (UBitmap &input, UBMColorModel color_model)
{
 return BCalculate(input,color_model);
}

bool UBAColorConvert::operator () (UBitmap &input, UBitmap &output, UBMColorModel color_model)
{
 return BCalculate(input,output, color_model);
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAColorConvert::AFDefault(void)
{
 NewColorModel=ubmY8;
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------

#endif


