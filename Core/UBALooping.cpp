/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBALooping.h"
//#include <math.h>
#include <string.h>
#include <stdlib.h>

namespace RDK {

// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBALooping::UBALooping(void)
: Input("Input",this),
  Output("Output",this)
{

}

UBALooping::~UBALooping(void)
{

}
// --------------------------


// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBALooping::ADefault(void)
{
 return AFCDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBALooping::ABuild(void)
{
 return AFCBuild();
}

// Сброс процесса счета.
bool UBALooping::AReset(void)
{
 return AFCReset();
}

// Выполняет расчет этого объекта
bool UBALooping::ACalculate(void)
{
 return AFCCalculate();
}
// --------------------------


// Выделяет контура простым фильтром
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBALoopingSimple* UBALoopingSimple::New(void)
{
 return new UBALoopingSimple;
}

bool UBALoopingSimple::BCalculate(UBitmap &input, UBitmap &output)
{
 int i; // Счётчик
 UBColor *pData, *ptData;
 unsigned r,g,b;
 unsigned tr,tg,tb;
 UBMColorModel cmodel=input.GetColorModel();
 int Width=input.GetWidth(),Height=input.GetHeight();
 int Length=input.GetLength();
 int linebytelength=input.GetLineByteLength();

 output.SetRes(Width,Height,cmodel);

 UColorT cmin,cmax;
 cmin.c=0;
 memset(&cmax,0xFF,sizeof(cmax));

 pData=input.GetData();
 ptData=output.GetData();
 switch(cmodel)
 {
  case ubmRGB24:
   for(i=0;i<Length;i++,pData+=3,ptData+=3)
   {
    tr=tg=tb=0;

    r=*(pData+0);
    g=*(pData+1);
    b=*(pData+2);
    if(i>Width-1)
    {
     if(i%Width!=0)
     {
      tr+=labs(r-*(pData-linebytelength-3));
      tg+=labs(g-*(pData-linebytelength-3+1));
      tb+=labs(b-*(pData-linebytelength-3+2));
     }
     tr+=labs(r-*(pData-linebytelength));
     tg+=labs(g-*(pData-linebytelength+1));
     tb+=labs(b-*(pData-linebytelength+2));
     if((i+1)%Width!=0)
     {
      tr+=labs(r-*(pData-linebytelength+3));
      tg+=labs(g-*(pData-linebytelength+3+1));
      tb+=labs(b-*(pData-linebytelength+3+2));
     }
    }
    if(i%Width!=0)
    {
     tr+=labs(r-*(pData-3));
     tg+=labs(g-*(pData-3+1));
     tb+=labs(b-*(pData-3+2));
    }
    if((i+1)%Width!=0)
    {
     tr+=labs(r-*(pData+3));
     tg+=labs(g-*(pData+3+1));
     tb+=labs(b-*(pData+3+2));
    }
    if(i<Length-Width)
    {
     if(i%Width!=0)
     {
      tr+=labs(r-*(pData+linebytelength-3));
      tg+=labs(g-*(pData+linebytelength-3+1));
      tb+=labs(b-*(pData+linebytelength-3+2));
     }
     tr+=labs(r-(int)*(pData+linebytelength));
     tg+=labs(g-(int)*(pData+linebytelength+1));
     tb+=labs(b-(int)*(pData+linebytelength+2));
     if((i+1)%Width!=0)
     {
      tr+=labs(r-*(pData+linebytelength+3));
      tg+=labs(g-*(pData+linebytelength+3+1));
      tb+=labs(b-*(pData+linebytelength+3+2));
     }
    }
    *ptData=tr>>3;
    *(ptData+1)=tg>>3;
    *(ptData+2)=tb>>3;
   }
//   output.Contrasting(cmin,cmax);
  break;

  case ubmY8:
   for(i=0;i<Length;i++,pData++,ptData++)
   {
    tr=tg=tb=0;

    b=*pData;

    if(i>Width-1)
    {
     if(i%Width!=0)
      tb+= labs(b-*(pData-Width-1));
      tb+= labs(b-*(pData-Width));
     if((i+1)%Width!=0)
      tb+= labs(b-*(pData-Width+1));
    }
    if(i%Width!=0)
     tb+= labs(b-*(pData-1));
    if((i+1)%Width!=0)
     tb+= labs(b-*(pData+1));
    if(i<Length-Width)
    {
     if(i%Width!=0)
      tb+= labs(b-*(pData+Width-1));
     tb+= labs(b-*(pData+Width));
     if((i+1)%Width!=0)
      tb+= labs(b-*(pData+Width+1));
    }

    *ptData=tb>>3;
   }

//   output.Contrasting();
  break;

  case ubmY32:
   for(i=0;i<Length;i++,pData+=4,ptData+=4)
   {
    unsigned int &tc=*reinterpret_cast<unsigned*>(ptData);
    b=*reinterpret_cast<unsigned*>(pData);

    tc=0;
    if(i>Width-1)
    {
     if(i%Width!=0)
      tc+=labs(b-*reinterpret_cast<unsigned*>(pData-linebytelength-4));
     tc+=labs(b-*reinterpret_cast<unsigned*>(pData-linebytelength-4));
     if((i+1)%Width!=0)
      tc+=labs(b-*reinterpret_cast<unsigned*>(pData-linebytelength+4));
    }
    if(i%Width!=0)
     tc+=labs(b-*reinterpret_cast<unsigned*>(pData-4));
    if((i+1)%Width!=0)
     tc+=labs(b-*reinterpret_cast<unsigned*>(pData+4));
    if(i<Length-Width)
    {
     if(i%Width!=0)
      tc+=labs(b-*reinterpret_cast<unsigned*>(pData+linebytelength-4));
     tc+=labs(b-*reinterpret_cast<unsigned*>(pData+linebytelength));
     if((i+1)%Width!=0)
      tc+=labs(b-*reinterpret_cast<unsigned*>(pData+linebytelength+4));
    }
   }
//   output.Contrasting();
  break;
 }

 return true;
}
// ---------------------


// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBALoopingSimple::AFCDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBALoopingSimple::AFCBuild(void)
{
 return true;
}

// Сброс процесса счета.
bool UBALoopingSimple::AFCReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBALoopingSimple::AFCCalculate(void)
{
 return BCalculate(*Input, *Output);
}
// --------------------------

// Выделяет контура фильтром собеля
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBALoopingSobel* UBALoopingSobel::New(void)
{
 return new UBALoopingSobel;
}

bool UBALoopingSobel::BCalculate(UBitmap &input, UBitmap &output)
{
// int i=0; // Счётчик
 UBColor *pData, *ptData;
 //int r,g,b;
// int tr,tg,tb;
 UBColor *pNBLine;
 unsigned int Gx,Gy;
 UBMColorModel cmodel=input.GetColorModel();
 int Width=input.GetWidth();
 int Height=input.GetHeight();
// int Length=input.GetLength();
 int linebytelength=input.GetLineByteLength();

        int x = 0, y = 0;
        int G00, G01, G02, G10, G12, G20, G21, G22;


 output.SetRes(Width,Height,cmodel);

 UColorT cmin,cmax;
 cmin.c=0;
 memset(&cmax,0xFF,sizeof(cmax));

 pData=input.GetData();
 ptData=output.GetData();
 switch(cmodel)
 {
  case ubmRGB24:
        pData+=linebytelength;

        memset(ptData, 0, linebytelength);    // 1 строка
        ptData += linebytelength;
        for(y = 1; y < Height-1; y++)
        {
            *ptData=*(ptData+1)=*(ptData+2)=0; ptData+=3;
            pData+=3;// 1 pixel
            for(x = 1; x < Width-1; x++, pData+=3)
            {
                pNBLine = pData-linebytelength;

                G00 = *(pNBLine-3);
                G01 = *pNBLine;
                G02 = *(pNBLine+3);
                pNBLine += linebytelength<<1;
                G10 = *(pData-3);
                G12 = *(pData+3);
                G20 = *(pNBLine-3);
                G21 = *pNBLine;
                G22 = *(pNBLine+3);

                Gx= (labs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
                Gy= (labs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

                *ptData = (Gx + Gy);

                ++pData; ++ptData; ++pNBLine;

                pNBLine -= linebytelength<<1;

                G00 = *(pNBLine-3);
                G01 = *pNBLine;
                G02 = *(pNBLine+3);
                pNBLine += linebytelength<<1;
                G10 = *(pData-3);
                G12 = *(pData+3);
                G20 = *(pNBLine-3);
                G21 = *pNBLine;
                G22 = *(pNBLine+3);

                Gx= (labs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
                Gy= (labs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

                *ptData= (Gx + Gy);

                ++pData; ++ptData; ++pNBLine;
                pNBLine -= linebytelength<<1;

                G00 = *(pNBLine-3);
                G01 = *pNBLine;
                G02 = *(pNBLine+3);
                pNBLine += linebytelength<<1;
                G10 = *(pData-3);
                G12 = *(pData+3);
                G20 = *(pNBLine-3);
                G21 = *pNBLine;
                G22 = *(pNBLine+3);

                Gx= (labs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
                Gy= (labs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

                *ptData= (Gx + Gy);

                ptData-=2; pData-=2;
                ptData+=3;
            }
            *ptData=0; ptData+=3;
            pData+=3;// 1 pixel
        }
        memset(ptData, 0, linebytelength);    // 1 строка
//   target->Contrasting(cmin,cmax);
  break;

  case ubmY8:
        pData+=linebytelength;

        memset(ptData, 0, linebytelength);    // 1 строка
        ptData += linebytelength;
        for(y = 1; y < Height-1; y++)
        {
            *ptData++=0;
            pData++;// 1 pixel
            for(x = 1; x < Width-1; x++, pData++)
            {
                pNBLine = pData-linebytelength;

                G00 = *(pNBLine-1);
                G01 = *pNBLine;
                G02 = *(pNBLine+1);
                pNBLine += linebytelength<<1;
                G10 = *(pData-1);
                G12 = *(pData+1);
                G20 = *(pNBLine-1);
                G21 = *pNBLine;
                G22 = *(pNBLine+1);

                Gx= (labs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
                Gy= (labs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

                *ptData = (Gx + Gy);
                ++ptData;
            }
            *ptData++=0;
            pData++;// 1 pixel
        }
        memset(ptData, 0, linebytelength);    // 1 строка

//   target->Contrasting();
  break;

  case ubmY32:
        pData+=linebytelength;

        memset(ptData, 0, linebytelength);    // 1 строка
        ptData += linebytelength;
        for(y = 1; y < Height-1; y++)
        {
            *reinterpret_cast<unsigned*>(ptData)=0;
            ptData+=4;
            pData+=4;// 1 pixel
            for(x = 1; x < Width-1; x++, pData+=4)
            {
                pNBLine = pData-linebytelength;

                G00 = *reinterpret_cast<unsigned*>(pNBLine-4);
                G01 = *reinterpret_cast<unsigned*>(pNBLine);
                G02 = *reinterpret_cast<unsigned*>(pNBLine+4);
                pNBLine += linebytelength<<1;
                G10 = *reinterpret_cast<unsigned*>(pData-4);
                G12 = *reinterpret_cast<unsigned*>(pData+4);
                G20 = *reinterpret_cast<unsigned*>(pNBLine-4);
                G21 = *reinterpret_cast<unsigned*>(pNBLine);
                G22 = *reinterpret_cast<unsigned*>(pNBLine+4);

                Gx= (labs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
                Gy= (labs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

                *reinterpret_cast<unsigned*>(ptData)=(Gx + Gy);
                ptData+=4;
            }
            *ptData=0;
            ptData+=4;
            pData+=4;// 1 pixel
        }
        memset(ptData, 0, linebytelength);    // 1 строка

//   target->Contrasting();
  break;
 }

 return true;
}
// ---------------------


// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBALoopingSobel::AFCDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBALoopingSobel::AFCBuild(void)
{
 return true;
}

// Сброс процесса счета.
bool UBALoopingSobel::AFCReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBALoopingSobel::AFCCalculate(void)
{
 return BCalculate(*Input, *Output);
}
// --------------------------
}
//---------------------------------------------------------------------------

