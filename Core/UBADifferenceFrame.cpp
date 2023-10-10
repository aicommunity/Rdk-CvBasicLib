/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBADifferenceFrame.h"
#include <math.h>

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBADifferenceFrame::UBADifferenceFrame(void)
: Input1("Input1",this),
  Input2("Input2",this),
  Output("Output",this)
{
}

UBADifferenceFrame::~UBADifferenceFrame(void)
{
}
// ---------------------

// ---------------------
// ���������
// ---------------------

// ---------------------


// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBADifferenceFrame::ADefault(void)
{
 return AFDiffDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBADifferenceFrame::ABuild(void)
{
 return AFDiffBuild();
}

// ����� �������� ����� ��� ������ ��������
bool UBADifferenceFrame::AReset(void)
{
 return AFDiffReset();
}

// ��������� ������ ����� �������
bool UBADifferenceFrame::ACalculate(void)
{
 return AFDiffCalculate();
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBADifferenceFrame::AFDiffDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBADifferenceFrame::AFDiffBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBADifferenceFrame::AFDiffReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBADifferenceFrame::AFDiffCalculate(void)
{
 return true;
}
// --------------------------



// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBADifferenceFrameSimple* UBADifferenceFrameSimple::New(void)
{
 return new UBADifferenceFrameSimple;
}

bool UBADifferenceFrameSimple::BCalculate(UBitmap &input, UBitmap &deduction, UBitmap &output)
{
 int i, j;
 int rdif, gdif, bdif;
 UBColor *buf, *bufdata, *bufded;
 int Height=input.GetHeight(),Width=input.GetWidth();
 unsigned char *ia;
 unsigned char *ib;
 unsigned char *io;
// unsigned int *iy1, *iy2,*iy3;
 int diff;
 int length=0;
 /*	 unsigned y1=0;
	 unsigned p0 = 0;
	 unsigned p1 = 0;
	 unsigned p2 = 0;
	 unsigned p3 = 0;

	 unsigned y2=0;
	 unsigned d0 = 0;
	 unsigned d1 = 0;
	 unsigned d2 = 0;
	 unsigned d3 = 0;

	 unsigned b0=0;
	 unsigned b1=0;
	 unsigned b2=0;
	 unsigned b3=0;     */


 if(input.GetWidth() != deduction.GetWidth() ||
    input.GetHeight() != deduction.GetHeight() ||
    input.GetColorModel() != deduction.GetColorModel())
  return false;

 bufdata = input.GetData();
 bufded = deduction.GetData();

 output.SetRes(input.GetWidth(),input.GetHeight(),input.GetColorModel());
 buf = output.GetData();

 switch(input.GetColorModel())
 {
  case ubmRGB24:
    for(i=0; i<Height; i++)
     for(j=0; j<Width; j++)
     {
      bdif = (int)(*bufdata++) - (int)(*bufded++);
      gdif = (int)(*bufdata++) - (int)(*bufded++);
      rdif = (int)(*bufdata++) - (int)(*bufded++);
      *buf++ = (rdif<0)?-rdif:rdif;
      *buf++ = (gdif<0)?-gdif:gdif;
	  *buf++ = (bdif<0)?-bdif:bdif;
     }
  break;

  case ubmY8:
  	ia=input.GetData();
	ib=deduction.GetData();
	io=output.GetData();
	length=input.GetByteLength();
	for (i=0;i<length;i++)
	{
	 *io++=((diff=(int)*ia++-(int)*ib++)>=0)?diff:-diff;
	}
  break;

  case ubmY32:
    for(i=0; i<Height; i++)
     for(j=0; j<Width; j++)
     {
	  bdif = *reinterpret_cast<unsigned*>(bufdata)
           - *reinterpret_cast<unsigned*>(bufded);
      *reinterpret_cast<unsigned*>(buf) = (bdif<0)?-bdif:bdif;
      buf+=4; bufdata+=4; bufded+=4;
     }
  break;
 }

 return true;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBADifferenceFrameSimple::AFDiffDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBADifferenceFrameSimple::AFDiffBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBADifferenceFrameSimple::AFDiffReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBADifferenceFrameSimple::AFDiffCalculate(void)
{
 return BCalculate(*Input1, *Input2, *Output);
}
// --------------------------


}
//---------------------------------------------------------------------------

