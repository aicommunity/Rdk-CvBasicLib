/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBARESIZE_CPP
#define UBARESIZE_CPP

#include "UBAResize.h"
#include <math.h>

namespace RDK {

UBAResizeEdges UBResizeEdges;

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAResize::UBAResize(void)
{
 NewWidth=1;
 NewHeight=1;
}
UBAResize::~UBAResize(void)
{
}
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// Новый размер
int UBAResize::GetNewWidth(void) const
{
 return NewWidth;
}

int UBAResize::GetNewHeight(void) const
{
 return NewHeight;
}

bool UBAResize::SetNewWidth(int value)
{
 if(NewWidth == value)
  return true;

 NewWidth=value;
 return true;
}

bool UBAResize::SetNewHeight(int value)
{
 if(NewHeight == value)
  return true;

 NewHeight=value;
 return true;
}
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBAResizeEdges* UBAResizeEdges::New(void)
{
 return new UBAResizeEdges;
}

bool UBAResize::PLACalculate(UBitmap **input, UBitmap **output, int num_inputs, int num_outputs)
{
  return BCalculate(*input[0], *output[0]);
}

bool UBAResize::BCalculate(UBitmap &input, int width, int height)
{
 // Тут проверка на совпадение размеров
 if(input.GetWidth() == width && input.GetHeight() == height)
  return true;

 SetNewWidth(width);
 SetNewHeight(height);
 if(BCalculate(input,Buffer))
 {
  input.Clear();
  input.AttachBuffer(width,height,Buffer.DetachBuffer(),Buffer.GetColorModel());
  return true;
 }
 return false;
}

bool UBAResize::BCalculate(UBitmap &input, UBitmap &output, int width, int height)
{
 SetNewWidth(width);
 SetNewHeight(height);
 return BCalculate(input,output);
}
// ---------------------

// ---------------------
// Операторы
// ---------------------
bool UBAResize::operator () (UBitmap &input, UBitmap &output)
{
 return BCalculate(input,output);
}

bool UBAResize::operator () (UBitmap &input, int width, int height)
{
 return BCalculate(input,width,height);
}

bool UBAResize::operator () (UBitmap &input, UBitmap &output, int width, int height)
{
 return BCalculate(input,output, width,height);
}
// ---------------------


// Изменяет размер изображения по четырем угловым точкам
// ---------------------
// Методы счета
// ---------------------
bool UBAResizeEdges::BCalculate(UBitmap &input, UBitmap &output)
{
 // Временные переменные расчётных методов
 int x1coord, y1coord;
 UBColor *Dest, *Src0, *Src1;
 //unsigned int p1, p2, p3, p4;
 unsigned int Res;
 float corrX, corrY;
 float di=0;
 float dj=0;
 int dj3;

 int oWidth=input.GetWidth();
 int oHeight=input.GetHeight();
 int nWidth=NewWidth;
 int nHeight=NewHeight;
 output.SetRes(nWidth,nHeight,input.GetColorModel());
 int oLineByteLength=input.GetLineByteLength();

 if(!oWidth || !oHeight)
 {
  output.Fill(UColorT(0,0,0));
  return true;
 }

 if(!nWidth || !nHeight)
  return true;

 if(nWidth == oWidth && nHeight == oHeight)
 {
  output=input;
  return true;
 }

 if((nWidth % oWidth == 0) && (nHeight % oHeight == 0))
 {
  // Здесь должна быть оптимизированная версия для масштабирования в кратные размеры
 }

 float StepX= (float)oWidth / (float)nWidth;
 float StepY= (float)oHeight / (float)nHeight;
 corrX= static_cast<float>((StepX>1)? StepX-1. : 0);
 corrY= static_cast<UBColor>((StepY>1)? StepY-1. : 0);

 Dest= output.GetData();
 switch(input.GetColorModel())
 {
 case ubmRGB24:
  // Прореживание по каждой строке
  di=0;
  for(int i=0; i<nHeight; i++, di+=StepY)
  {
    y1coord= int(di + corrY);
    Src0= input.GetData() + int(di) * oLineByteLength;
    Src1= input.GetData() + y1coord * oLineByteLength;
    dj=0;
    for(int j=0; j<nWidth; j++, dj+=StepX)
    {
     dj3=static_cast<int>(dj*3);
     x1coord= (int)(dj + corrX)*3;
     Res= *(Src0 + dj3);
     Res+= *(Src0 + x1coord);
     Res+= *(Src1 + dj3);
     Res+= *(Src1 + x1coord);
     *Dest++ = Res>>2;

     Res= *(Src0 + dj3+1);
     Res+= *(Src0 + x1coord+1);
     Res+= *(Src1 + dj3+1);
     Res+= *(Src1 + x1coord+1);
     *Dest++ = Res>>2;

     Res= *(Src0 + dj3+2);
     Res+= *(Src0 + x1coord+2);
     Res+= *(Src1 + dj3+2);
     Res+= *(Src1 + x1coord+2);
     *Dest++ = Res>>2;
    }
   }
 break;

 case ubmY8:
  // Прореживание по каждой строке
  di=0;
  for(int i=0; i<nHeight; i++, di+=StepY)
  {
    y1coord= (int)(di + corrY);
    Src0= input.GetData() + int(di) * oLineByteLength;
    Src1= input.GetData() + y1coord * oLineByteLength;
    dj=0;
    for(int j=0; j<nWidth; ++j, dj+=StepX)
    {
     x1coord= (int)(dj + corrX);
     Res= *(Src0 + int(dj));
     Res+= *(Src0 + x1coord);
     Res+= *(Src1 + int(dj));
     Res+= *(Src1 + x1coord);
     *Dest++=Res>>2;
    }
   }
 break;

 case ubmY32:
  // Прореживание по каждой строке
  di=0;
  for(int i=0; i<nHeight; i++, di+=StepY)
  {
   y1coord= (int)(di + corrY);
   Src0= input.GetData() + int(di) * oLineByteLength;
   Src1= input.GetData() + y1coord * oLineByteLength;
   dj=0;
   for(int j=0; j<nWidth; j++, dj+=StepX, Dest+=4)
   {
    x1coord= (int)(dj + corrX);
    Res=  *(reinterpret_cast<unsigned*>(Src0)+int(dj));
    Res+= *(reinterpret_cast<unsigned*>(Src0) + x1coord);
    Res+= *(reinterpret_cast<unsigned*>(Src1) + int(dj));
    Res+= *(reinterpret_cast<unsigned*>(Src1) + x1coord);
    *reinterpret_cast<unsigned*>(Dest)=Res>>2;
   }
  }
 break;
 }

 return true;
}
// ---------------------

}
//---------------------------------------------------------------------------

#endif


