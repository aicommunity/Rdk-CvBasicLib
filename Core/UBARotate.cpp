/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBARotate.h"
#include <math.h>
#include <string.h>

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBARotate::UBARotate(void)
: Input("Input",this),
  Output("Output",this)
{
}

UBARotate::~UBARotate(void)
{
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ���� �������� (�������)
float UBARotate::GetAngle(void) const
{
 return Angle;
}

bool UBARotate::SetAngle(float angle)
{
 if(Angle == angle)
  return true;

 Angle=angle;
 return true;
}

// ���� ����������
bool UBARotate::GetEnlarge(void) const
{
 return Enlarge;
}

bool UBARotate::SetEnlarge(bool enlarge)
{
 if(Enlarge == enlarge)
  return true;

 Enlarge=enlarge;
 return true;
}
// ---------------------

// ---------------------
// ���������
// ---------------------
bool UBARotate::operator () (UBitmap &input, UBitmap &output)
{
 //*Input=input;
 //bool res=AFCCalculate();
 //output=*Output;
 BCalculate(input, output);
 return true;
}

bool UBARotate::operator () (UBitmap &input, UBitmap &output, float angle, bool enlarge)
{
 Angle=angle;
 Enlarge=enlarge;
 BCalculate(input, output);
 return true;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBARotate::ADefault(void)
{
 Angle=0;
 Enlarge=false;
 return AFCDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBARotate::ABuild(void)
{
 return AFCBuild();
}

// ����� �������� �����.
bool UBARotate::AReset(void)
{
 return AFCReset();
}

// ��������� ������ ����� �������
bool UBARotate::ACalculate(void)
{
 return AFCCalculate();
}
// --------------------------



// ������������ ����������� �� �������� ����
// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBARotateSimple* UBARotateSimple::New(void)
{
 return new UBARotateSimple;
}

bool UBARotateSimple::BCalculate(UBitmap &input, UBitmap &output)
{
 float angle=Angle;
 if(angle>=360)
  angle-=(int(angle)/360)*360;

 if(angle<0)
  angle+=(labs(int(angle))/360)*360;

 // �������� ������ ��������������� �����������
 if(Enlarge)
 {
  output.SetRes(input.GetWidth(),input.GetHeight(),input.GetColorModel());
 }
 else
 {
  output.SetRes(input.GetWidth(),input.GetHeight(),input.GetColorModel());
 }

 if(angle == 0)
 {
  output=input;
 }
 else
 if(angle == 90)
 {
  if(input.GetWidth() == 0 || input.GetHeight() == 0)
  {
   output.SetRes(input.GetHeight(),input.GetWidth(),input.GetColorModel());
   return true;
  }
/*  if(enlarge)
  {
   UBColor *indata=input.GetData();
   UBColor *outdata=output.GetData();
   for(int j=0;j<input.GetHeight();j++)
   {
	for(int i=0;i<input.GetWidth();i++)
	{
	 memcpy(outdata+i*output.GetLineByteLength()+j*output.GetPixelByteLength(),
			indata,input.GetPixelByteLength());
	 indata+=input.GetPixelByteLength();
	}
   }
  }
  else
  {
   int in_xstart,in_xstop,in_ystart,in_ystop;
   int out_xstart,out_xstop,out_ystart,out_ystop;
   if(input.GetWidth()>input.GetHeight())
   {
    in_xstart=(input.GetWidth()-input.GetHeight())/2;
    in_xstop=in_xstart+input.GetHeight()-1;
    in_ystart=0;
    in_ystop=input.GetHeight()-1;
    out_xstart=in_xstart;
    out_xstop=in_xstop;
    out_ystart=in_ystart;
    out_ystop=in_ystop;
   }
   else
   {
    in_xstart=0;
    in_xstop=input.GetWidth();
    in_ystart=(input.GetHeight()-input.GetWidth())/2;
    in_ystop=in_ystart+input.GetWidth();
    out_xstart=in_ystart;
    out_xstop=in_ystop;
    out_ystart=in_xstart;
    out_ystop=in_xstop;
   }

   UBColor *indata=input.GetData();
   UBColor *outdata=output.GetData();
   for(int j=in_ystart;j<=in_ystop;j++)
   {
    for(int i=in_xstart;i<=in_xstop;i++)
    {
     memcpy(outdata+(i-in_xstart)*output.GetLineByteLength()+(j+in_xstart)*output.GetPixelByteLength(),
            indata+j*input.GetLineByteLength()+i*input.GetPixelByteLength(),input.GetPixelByteLength());
    }
   }
  }    */
  if(Enlarge)
  {
   UBColor *indata=input.GetData();
   UBColor *outdata=output.GetData();
   for(int j=0;j<input.GetHeight();j++)
   {
    for(int i=0;i<input.GetWidth();i++)
    {
     memcpy(outdata+i*output.GetLineByteLength()+j*output.GetPixelByteLength(),
            indata,input.GetPixelByteLength());
     indata+=input.GetPixelByteLength();
    }
   }
  }
  else
  {
   int in_xstart,in_xstop,in_ystart,in_ystop;
  // int out_xstart,out_xstop/*,out_ystart,out_ystop*/;
   if(input.GetWidth()>input.GetHeight())
   {
    in_xstart=(input.GetWidth()-input.GetHeight())/2;
    in_xstop=in_xstart+input.GetHeight()-1;
    in_ystart=0;
    in_ystop=input.GetHeight()-1;
//    out_xstart=in_xstart;
//    out_xstop=in_xstop;
//    out_ystart=in_ystart;
//    out_ystop=in_ystop;
   }
   else
   {
    in_xstart=0;
    in_xstop=input.GetWidth()-1;
    in_ystart=(input.GetHeight()-input.GetWidth())/2;
	in_ystop=in_ystart+input.GetWidth()-1;
//    out_xstart=in_ystart;
//    out_xstop=in_ystop;
//    out_ystart=in_xstart;
//    out_ystop=in_xstop;
   }

   UBColor *indata=input.GetData();
   UBColor *outdata=output.GetData();
   for(int j=in_ystart;j<=in_ystop;j++)
   {
    for(int i=in_xstart;i<=in_xstop;i++)
    {
     memcpy(outdata+(in_ystop-(i-in_xstart))*output.GetLineByteLength()+(j+in_xstart)*output.GetPixelByteLength(),
            indata+j*input.GetLineByteLength()+i*input.GetPixelByteLength(),input.GetPixelByteLength());
    }
   }
  }

 }
 else
 if(angle == 180)
 {
  if(input.GetWidth() == 0 || input.GetHeight() == 0)
  {
   output.SetRes(input.GetWidth(),input.GetHeight(),input.GetColorModel());
   return true;
  }

  output=input;
  output.ReflectionX();
  output.ReflectionY();
 }
 else
 if(angle == 270)
 {
  if(input.GetWidth() == 0 || input.GetHeight() == 0)
  {
   output.SetRes(input.GetHeight(),input.GetWidth(),input.GetColorModel());
   return true;
  }

  if(Enlarge)
  {
   UBColor *indata=input.GetData();
   UBColor *outdata=output.GetData();
   for(int j=0;j<input.GetHeight();j++)
   {
    for(int i=0;i<input.GetWidth();i++)
    {
     memcpy(outdata+i*output.GetLineByteLength()+j*output.GetPixelByteLength(),
            indata,input.GetPixelByteLength());
     indata+=input.GetPixelByteLength();
    }
   }
  }
  else
  {
   int in_xstart,in_xstop,in_ystart,in_ystop;
//   int out_xstart/*,out_xstop,out_ystart,out_ystop*/;
   if(input.GetWidth()>input.GetHeight())
   {
    in_xstart=(input.GetWidth()-input.GetHeight())/2;
    in_xstop=in_xstart+input.GetHeight()-1;
    in_ystart=0;
    in_ystop=input.GetHeight()-1;
//    out_xstart=in_xstart;
//    out_xstop=in_xstop;
//    out_ystart=in_ystart;
//    out_ystop=in_ystop;
   }
   else
   {
    in_xstart=0;
	in_xstop=input.GetWidth()-1;
	in_ystart=(input.GetHeight()-input.GetWidth())/2;
	in_ystop=in_ystart+input.GetWidth()-1;
//    out_xstart=in_ystart;
//    out_xstop=in_ystop;
//    out_ystart=in_xstart;
//    out_ystop=in_xstop;
   }

   UBColor *indata=input.GetData();
   UBColor *outdata=output.GetData();
   for(int j=in_ystart;j<=in_ystop;j++)
   {
    for(int i=in_xstart;i<=in_xstop;i++)
    {
     memcpy(outdata+(in_ystop-(i-in_xstart))*output.GetLineByteLength()+(j+in_xstart)*output.GetPixelByteLength(),
            indata+j*input.GetLineByteLength()+i*input.GetPixelByteLength(),input.GetPixelByteLength());
    }
   }
  }
  output.ReflectionX();
  output.ReflectionY();
 }
 else
 {
 }

 return true;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBARotateSimple::AFCDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBARotateSimple::AFCBuild(void)
{
 return true;
}

// ����� �������� �����.
bool UBARotateSimple::AFCReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBARotateSimple::AFCCalculate(void)
{
 return BCalculate(*Input, *Output);
}
// --------------------------
}
//---------------------------------------------------------------------------

