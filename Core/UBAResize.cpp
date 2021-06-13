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

//UBAResizeEdges UBResizeEdges;

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAResize::UBAResize(void)
: NewWidth("NewWidth",this),
  NewHeight("NewHeight",this),
  Input("Input",this),
  Output("Output",this)
{
 NewWidth=100;
 NewHeight=100;
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


// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAResize::ADefault(void)
{
 return AFCDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAResize::ABuild(void)
{
 return AFCBuild();
}

// Сброс процесса счета.
bool UBAResize::AReset(void)
{
 return AFCReset();
}

// Выполняет расчет этого объекта
bool UBAResize::ACalculate(void)
{
 return AFCCalculate();
}
// --------------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBAResizeEdges* UBAResizeEdges::New(void)
{
 return new UBAResizeEdges;
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
 UBColor *Dest(0), *Src0(0), *Src1(0);
 //unsigned int p1, p2, p3, p4;
 unsigned int Res;
 float corrX, corrY;
 float di=0;
 float dj=0;

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
 corrY= static_cast<float>((StepY>1)? StepY-1. : 0);

 Dest= output.GetData();

 switch(input.GetColorModel())
 {

 case ubmRGB24:
 {
	int x0coord, y0coord;
//	unsigned char *Dest, *Src0, *Src1;

	unsigned char p1, p2, p3, p4;
//	unsigned int Res;
//	double corrX, corrY;

//	corrX= (StepX>1)? StepX-1. : 0;
//	corrY= (StepY>1)? StepY-1. : 0;

	// Прореживание по каждой строке компоненты R
	double di=0;
	Dest= output.GetData();
	for(int i=0; i<nHeight; i++, di+=StepY)
	{
		y0coord= (int)di;
		y1coord= (int)(di + corrY);
		Src0= input.GetData() + 3 * y0coord * oWidth;
		Src1= input.GetData() + 3 * y1coord * oWidth;
		double dj=0;
		for(int j=0; j<nWidth; j++, dj+=StepX)
		{
			x0coord= 3 * (int)dj;
			x1coord= 3 * (int)(dj + corrX);
			p1= *(Src0 + x0coord);
			p2= *(Src0 + x1coord);
			p3= *(Src1 + x0coord);
			p4= *(Src1 + x1coord);
			Res= (unsigned int)p1 + (unsigned int)p2 + (unsigned int)p3 + (unsigned int)p4;
			*Dest= (Res>>2);

			Dest += 3;
		}
	}
	// Прореживание по каждой строке компоненты G
	Dest = output.GetData() + 1;
	di=0;
	for(int i=0; i<nHeight; i++, di+=StepY)
	{
		y0coord= (int)di;
		y1coord= (int)(di + corrY);
		Src0= input.GetData() + 3 * y0coord * oWidth;
		Src1= input.GetData() + 3 * y1coord * oWidth;
		double dj=0;
		for(int j=0; j<nWidth; j++, dj+=StepX)
		{
			x0coord= 3 * (int)dj + 1;
			x1coord= 3 * (int)(dj + corrX) + 1;
			p1= *(Src0 + x0coord);
			p2= *(Src0 + x1coord);
			p3= *(Src1 + x0coord);
			p4= *(Src1 + x1coord);
			Res= (unsigned int)p1 + (unsigned int)p2 + (unsigned int)p3 + (unsigned int)p4;
			*Dest= (Res>>2);

			Dest += 3;
		}
	}
	// Прореживание по каждой строке компоненты B
	Dest = output.GetData() + 2;
	di=0;
	for(int i=0; i<nHeight; i++, di+=StepY)
	{
		y0coord= (int)di;
		y1coord= (int)(di + corrY);
		Src0= input.GetData() + 3 * y0coord * oWidth;
		Src1= input.GetData() + 3 * y1coord * oWidth;
		double dj=0;
		for(int j=0; j<nWidth; j++, dj+=StepX)
		{
			x0coord= 3 * (int)dj + 2;
			x1coord= 3 * (int)(dj + corrX) + 2;
			p1= *(Src0 + x0coord);
			p2= *(Src0 + x1coord);
			p3= *(Src1 + x0coord);
			p4= *(Src1 + x1coord);
			Res= (unsigned int)p1 + (unsigned int)p2 + (unsigned int)p3 + (unsigned int)p4;
			*Dest= (Res>>2);

			Dest += 3;
		}
	}

 }
		 /*
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
   }      */
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


// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAResizeEdges::AFCDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAResizeEdges::AFCBuild(void)
{
 return true;
}

// Сброс процесса счета.
bool UBAResizeEdges::AFCReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBAResizeEdges::AFCCalculate(void)
{
 return BCalculate(*Input, *Output);
}
// --------------------------


}
//---------------------------------------------------------------------------

#endif


