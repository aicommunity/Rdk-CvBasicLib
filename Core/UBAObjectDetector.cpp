/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAObjectDetector_CPP
#define UBAObjectDetector_CPP

#include <math.h>
#include "UBAObjectDetector.h"

namespace RDK {

// class UBAObjectDetector
// ---------------------
// Операторы
// ---------------------
bool UBAObjectDetector::operator () (const UBitmap& input, Rect* objects)
{
 return Calculate(input, objects);
}
// ---------------------


// class UBANightDetector
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBANightDetector::UBANightDetector(void)
{
 HistorySize=0;

 // Размер блока изображения
 BlockWidth=16;
 BlockHeight=20;

 // Размер карты
 MapWidth=22;
 MapHeight=12;

 // Пороги
 T1=0.45;

 // Коэффициент расстояния между кадрами
 Tr=0.8; // 0.8-0.9

 T=0;

 LocalContrastedImages=0;
 CurrentHistorySize=0;
 CurrentFirstHistoryIndex=-1;
 Input=0;

 // Временные переменные для вычисления локального контраста
 // Размер изображения
 Width=0; Height=0;

 // Число блоков
 NumBlocks=0;

 // Массив локальных контрастов
 CL=0;

 // Массив средних
 ML=0;

 // Массив СКО
 SigmaL=0;

 // Временные переменные для вычисления карты локальной зависимости
 // Число элементов карты
 NumMaps=0;

 // Данные карты
 MCm=0;
 ICm=0;

 // Сетка контрастных объектов
 ContrastGrid=0;

 // Сетка движущихся объектов
 MovedGrid=0;

 TT=128;

 AdaptiveThresholdPercent=10;

 MoveDetectionPercent=10;

}

UBANightDetector::~UBANightDetector(void)
{
 // Временные переменные для вычисления локального контраста
 // Число блоков
 NumBlocks=0;

 // Массив локальных контрастов
 if(CL) delete[] CL;
 CL=0;

 // Массив средних
 if(ML) delete[] ML;
 ML=0;

 // Массив СКО
 if(SigmaL) delete[] SigmaL;
 SigmaL=0;

 // Временные переменные для вычисления карты локальной зависимости
 // Число элементов карты
 NumMaps=0;

 // Данные карты
 if(MCm) delete[] MCm;
 MCm=0;
 if(ICm) delete[] ICm;
 ICm=0;

 if(T) delete[] T;
 T=0;

 // Сетка контрастных объектов
 if(ContrastGrid) delete[] ContrastGrid;
 ContrastGrid=0;

 // Сетка движущихся объектов
 if(MovedGrid) delete[] MovedGrid;
 MovedGrid=0;
}
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
// Число изображений в истории
int UBANightDetector::GetHistorySize(void) const
{
 return HistorySize;
}

bool UBANightDetector::SetHistorySize(int value)
{
 if(HistorySize == value)
  return true;

 if(value<1)
  return false;

 HistorySize=value;
 if(LocalContrastedImages)
  delete LocalContrastedImages;
 LocalContrastedImages=0;
 LocalContrastedImages=new UBitmap[HistorySize];

 CurrentFirstHistoryIndex=-1;
 CurrentHistorySize=0;

 return true;
}
// --------------------------

// --------------------------
// Методы доступа к данным
// --------------------------
// Изображение с обнаружением движущихся объектов
const UBitmap& UBANightDetector::GetMovedImage(void) const
{
 return MovedImage;
}
// --------------------------


// ---------------------
// Методы счета
// ---------------------
bool UBANightDetector::Calculate(const UBitmap& input, Rect* objects)
{
 if(objects)
  return false;

 Width=input.GetWidth();
 Height=input.GetHeight();
 UBMColorModel c=input.GetColorModel();

 if(Width < BlockWidth || Height < BlockHeight || c != ubmY8)// || c != ubmY8 || c != ubmY32)
  return false;

 for(int i=0;i<HistorySize;i++)
  LocalContrastedImages[i].SetRes(Width,Height,c);

 for(int i=0;i<CurrentHistorySize;i++)
 {
  if(LocalContrastedImages[i].GetWidth() != Width ||
     LocalContrastedImages[i].GetHeight() != Height ||
     LocalContrastedImages[i].GetColorModel() != c)
   return false;
 }

 // Проверяем совпадение кадров
/* if(Input && Tr>0)
 {
  Correlation.SetIRes(Width,Height);
  Correlation.SetTRes(Width,Height);
  Correlation.SetWorkIX(0);
  Correlation.SetWorkIY(0);
  Correlation.SetWorkIWidth(Width);
  Correlation.SetWorkIHeight(Height);

  Correlation.SetTemplate(Input->GetData());
  Correlation.SetInput(input.GetData());

  bool res=Correlation.Calculate();
  double corr=Correlation.GetMaxResult();
  if(corr > Tr)
   return true;
 }   */

 Input=&input;

 // Сдвигаем историю если необходимо
 // и делаем текущим изображением истории то, куда будет производится запись
 if(CurrentHistorySize == HistorySize)
 {
  ++CurrentFirstHistoryIndex;
  if(CurrentFirstHistoryIndex>=HistorySize)
   CurrentFirstHistoryIndex=0;

 }
 else
 {
  ++CurrentFirstHistoryIndex;
  if(CurrentFirstHistoryIndex>=HistorySize)
   CurrentFirstHistoryIndex=0;
  else
   ++CurrentHistorySize;
 }

 // Вычисляем локальный контраст
 if(!CalcLocalContrasting())
  return false;

 // Вычисляем карту локальной заметности
 if(!CalcLocalMap())
  return false;

// Обнаружение движущихся объектов
 if(!CalcMovedObjects())
  return false;

 // Вычисляем адаптивный порог
 if(!CalcAdaptiveThreshold())
  return false;

 return true;
}
// ---------------------


// ---------------------
// Скрытые методы счета
// ---------------------
// Вычисление локального контраста
bool UBANightDetector::CalcLocalContrasting(void)
{
 int xblocks=Width/BlockWidth,yblocks=Height/BlockHeight;
 NumBlocks=xblocks*yblocks;

 if(!Input)
  return false;

 if(!CL)
  CL=new double[NumBlocks];
 if(!ML)
  ML=new double[NumBlocks];
 if(!SigmaL)
  SigmaL=new double[NumBlocks];
 memset(CL,0,sizeof(double)*NumBlocks);
 memset(ML,0,sizeof(double)*NumBlocks);
 memset(SigmaL,0,sizeof(double)*NumBlocks);
 double* pML=ML;
 double* pCL=CL;
 double* pSigmaL=SigmaL;
 double sum,sub;

 if(!ContrastGrid)
  ContrastGrid=new UBRect[NumBlocks];

 if(!MovedGrid)
  MovedGrid=new UBRect[NumBlocks];

 for(int q=0;q<yblocks;q++)
 {
  for(int p=0;p<xblocks;p++)
  {
   sum=0;
   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     sum+=double((*Input)(p*BlockWidth+i,q*BlockHeight+j));
    }
   }
   *pML=sum/(BlockWidth*BlockHeight);

   sum=0;
   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     sub=double((*Input)(p*BlockWidth+i,q*BlockHeight+j))-*pML;
     sum+=sub*sub;
    }
   }
   *pSigmaL=sqrt(sum/(BlockWidth*BlockHeight));

   if(*pML)
    *pCL=(*pSigmaL)/(*pML);

   ++pSigmaL;
   ++pML;
   ++pCL;
  }
 }

 return true;
}

// Построение карты локальной заметности
bool UBANightDetector::CalcLocalMap(void)
{
 UBitmap &out=LocalContrastedImages[CurrentFirstHistoryIndex];

 int xblocks=Width/BlockWidth,yblocks=Height/BlockHeight;

 double* pCL=CL;
 UBRect *pContrastGrid=ContrastGrid;
 for(int q=0;q<yblocks;q++)
 {
  for(int p=0;p<xblocks;p++)
  {
   if(*pCL>=T1)
   {
    pContrastGrid->X=p*BlockWidth;
    pContrastGrid->Y=q*BlockHeight;
    pContrastGrid->Width=BlockWidth;
    pContrastGrid->Height=BlockHeight;
   }
   else
   {
    pContrastGrid->X=0;
    pContrastGrid->Y=0;
    pContrastGrid->Width=0;
    pContrastGrid->Height=0;
   }
   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     if(*pCL >= T1)
      out(p*BlockWidth+i,q*BlockHeight+j)=((*Input)(p*BlockWidth+i,q*BlockHeight+j));
     else
      out(p*BlockWidth+i,q*BlockHeight+j)=0;
    }
   }
   ++pCL;
   ++pContrastGrid;
  }
 }

 return true;
}


// Обнаружение движущихся объектов
bool UBANightDetector::CalcMovedObjects(void)
{
 MovedImage.SetRes(LocalContrastedImages[CurrentFirstHistoryIndex].GetWidth(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetHeight(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetColorModel());
 DiffImage.SetRes(LocalContrastedImages[CurrentFirstHistoryIndex].GetWidth(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetHeight(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetColorModel());

 int xblocks=Width/BlockWidth,yblocks=Height/BlockHeight;
 UBRect *pMovedGrid=MovedGrid;

 if(!T)
 {
  T=new double[NumBlocks];
  memset(T,0,NumBlocks*sizeof(double));
 }

 int i1,i2;

 if(CurrentFirstHistoryIndex == 0)
 {
  i1=CurrentFirstHistoryIndex;
  i2=1;
 }
 else
 {
  i1=CurrentFirstHistoryIndex;
  i2=0;
 }

 for(int i=0;i<DiffImage.GetLength();i++)
  DiffImage[i]=abs(int(LocalContrastedImages[i1][i])-int(LocalContrastedImages[i2][i]));

 for(int q=0;q<yblocks;q++)
 {
  for(int p=0;p<xblocks;p++)
  {
   int vis=0;
   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     if(DiffImage(p*BlockWidth+i,q*BlockHeight+j)>TT)
     {
      ++vis;
     }
    }
   }

   if(vis>(BlockWidth*BlockHeight*MoveDetectionPercent)/100.0)
   {
    pMovedGrid->X=p*BlockWidth;
    pMovedGrid->Y=q*BlockHeight;
    pMovedGrid->Width=BlockWidth;
    pMovedGrid->Height=BlockHeight;
   }
   else
   {
    pMovedGrid->X=0;
    pMovedGrid->Y=0;
    pMovedGrid->Width=0;
    pMovedGrid->Height=0;
   }


   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     if(vis>(BlockWidth*BlockHeight*MoveDetectionPercent)/100.0)
      MovedImage(p*BlockWidth+i,q*BlockHeight+j)=((*Input)(p*BlockWidth+i,q*BlockHeight+j));
     else
      MovedImage(p*BlockWidth+i,q*BlockHeight+j)=0;
    }
   }
   ++pMovedGrid;
  }
 }
/*
 for(int i=0;i<MovedImage.GetLength();i++)
 {
  if(abs(int(LocalContrastedImages[i1][i])-int(LocalContrastedImages[i2][i]))>T)
   MovedImage[i]=1;
  else
   MovedImage[i]=0;
 }

 for(int i=0;i<MovedImage.GetLength();i++)
 {
  MovedImage[i]=MovedImage[i]*(*Input)[i];
 }
    */
 return true;
}


// Расчет адаптивного порога
bool UBANightDetector::CalcAdaptiveThreshold(void)
{
 unsigned minval,maxval;
 int min_i=-1;

 Histogram.Prepare(ubmY8);

// int xblocks=Width/BlockWidth,yblocks=Height/BlockHeight;

 Histogram.Calc(DiffImage);
//   DiffImage.CalcHistogram(Histogram, 256);
//   memmove(Histogram,Histogram+1,255*sizeof(UBHistogramElement));

   // Ищем маскимум гистограммы
   maxval=0;
   for(int i=0;i<256;i++)
   {
	if(Histogram[i].Int>maxval)
    {
	 maxval=Histogram[i].Int;
    }
   }

   // Ищем яркость AdaptiveThresholdPercent% от максимума
   minval=0;
   for(int i=0;i<256;i++)
   {
	if(Histogram[i].Int<=(maxval*AdaptiveThresholdPercent)/100.0 && Histogram[i].Int>=minval)
    {
     minval=Histogram[i].Int;
     min_i=i;
    }
   }

   if(min_i>0)
    TT=Histogram[min_i].Color.rgb.b;
   else
    TT=0;


 return true;
}
// ---------------------

}


#endif


