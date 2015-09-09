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
// Конструкторы и деструкторы
// ---------------------
UBARotate::UBARotate(void)
: Angle("Angle",this, &UBARotate::SetAngle),
//  Enlarge("Enlarge",this, &UBARotate::SetEnlarge),
  Input("Input",this),
  Output("Output",this)
{
 Enlarge=true;
}

UBARotate::~UBARotate(void)
{
}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// Угол поворота (градусы)
float UBARotate::GetAngle(void) const
{
 return Angle;
}

bool UBARotate::SetAngle(const float &angle)
{
// Angle=angle;
 return true;
}

// Флаг расширения
bool UBARotate::GetEnlarge(void) const
{
 return Enlarge;
}

bool UBARotate::SetEnlarge(const bool &enlarge)
{
// Enlarge=enlarge;
 return true;
}
// ---------------------

// ---------------------
// Операторы
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
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBARotate::ADefault(void)
{
 Angle=0;
// Enlarge=false;
 return AFCDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBARotate::ABuild(void)
{
 return AFCBuild();
}

// Сброс процесса счета.
bool UBARotate::AReset(void)
{
 return AFCReset();
}

// Выполняет расчет этого объекта
bool UBARotate::ACalculate(void)
{
 return AFCCalculate();
}
// --------------------------



// Поворачивает изображение на заданный угол
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
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

 if(angle == 0)
 {
  output=input;
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
   output.SetRes(input.GetHeight(),input.GetWidth(),input.GetColorModel());
   int pixel_byte_length=input.GetPixelByteLength();
   int output_line_byte_length=output.GetLineByteLength();

   UBColor *indata=input.GetData()+input.GetByteLength();
   UBColor *outdata=output.GetData();
   switch(input.GetColorModel())
   {
   case ubmY8:
	// Выбираем размер результирующего изображения
	for(int j=input.GetHeight()-1;j>=0;j--)
	{
	 UBColor* poutdata=outdata+j;
	 for(int i=0;i<input.GetWidth();i++)
	 {
	  *poutdata=*indata;
	  poutdata+=output_line_byte_length;
	  --indata;
	 }
    }
   break;

   case ubmRGB24:
	// Выбираем размер результирующего изображения
	for(int j=input.GetHeight()-1;j>=0;j--)
	{
	 UBColor* poutdata=outdata+j*pixel_byte_length;
	 for(int i=0;i<input.GetWidth();i++)
	 {
	  *poutdata=*indata;
	  *(poutdata+1)=*(indata+1);
	  *(poutdata+2)=*(indata+2);
	  poutdata+=output_line_byte_length;
	  indata-=pixel_byte_length;
	 }
	}
   break;

   default:
	// Выбираем размер результирующего изображения
	for(int j=input.GetHeight()-1;j>=0;j--)
	{
	 UBColor* poutdata=outdata+j*pixel_byte_length;
	 for(int i=0;i<input.GetWidth();i++)
	 {
	  memcpy(poutdata,indata,pixel_byte_length);
	  poutdata+=output_line_byte_length;
	  indata-=pixel_byte_length;
	 }
    }
   }
  }
  else
  {
   output.SetRes(input.GetWidth(),input.GetHeight(),input.GetColorModel());
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

  input.ReflectionX(&output);
  output.ReflectionY();
 }
 else
 if(angle == 90)
 {
  if(input.GetWidth() == 0 || input.GetHeight() == 0)
  {
   output.SetRes(input.GetHeight(),input.GetWidth(),input.GetColorModel());
   return true;
  }

  if(Enlarge)
  {
   output.SetRes(input.GetHeight(),input.GetWidth(),input.GetColorModel());
   UBColor *indata=input.GetData()+input.GetByteLength();;
   UBColor *outdata=output.GetData();
   int pixel_byte_length=input.GetPixelByteLength();
   int output_line_byte_length=output.GetLineByteLength();

   switch(input.GetColorModel())
   {
   case ubmY8:
	for(int j=input.GetHeight()-1;j>=0;j--)
	{
	 UBColor *poutdata=outdata+j;
	 for(int i=0;i<input.GetWidth();i++)
	 {
//	  memcpy(poutdata,indata,pixel_byte_length);
	  *poutdata=*indata;
	  poutdata+=output_line_byte_length;
	  --indata;
	 }
	}
   break;

   case ubmRGB24:
	for(int j=input.GetHeight()-1;j>=0;j--)
	{
	 UBColor *poutdata=outdata+j*pixel_byte_length;
	 for(int i=0;i<input.GetWidth();i++)
	 {
//	  memcpy(poutdata,indata,pixel_byte_length);
	  *poutdata=*indata;
	  *(poutdata+1)=*(indata+1);
	  *(poutdata+2)=*(indata+2);
	  poutdata+=output_line_byte_length;
	  indata-=pixel_byte_length;
	 }
	}
   break;

   default:
	for(int j=input.GetHeight()-1;j>=0;j--)
	{
	 UBColor *poutdata=outdata+j*pixel_byte_length;
	 for(int i=0;i<input.GetWidth();i++)
	 {
	  memcpy(poutdata,indata,pixel_byte_length);
	  poutdata+=output_line_byte_length;
	  indata-=pixel_byte_length;
	 }
	}
   }
  }
  else
  {
   output.SetRes(input.GetWidth(),input.GetHeight(),input.GetColorModel());
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
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBARotateSimple::AFCDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBARotateSimple::AFCBuild(void)
{
 return true;
}

// Сброс процесса счета.
bool UBARotateSimple::AFCReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBARotateSimple::AFCCalculate(void)
{
 return BCalculate(*Input, *Output);
}
// --------------------------
}
//---------------------------------------------------------------------------

