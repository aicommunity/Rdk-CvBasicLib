/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAMovingDetector_CPP
#define UBAMovingDetector_CPP

#include <string.h>
#include <math.h>
#include "UBAMovingDetector.h"

namespace RDK {

//UBANightMovingDetector UBNightMovingDetector;
//UBACollateMovingDetector UBCollateMovingDetector;

// class UBAMovingDetector
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBAMovingDetector::UBAMovingDetector(void)
: Input("Input",this)
{
 MovedObjects=0;

 LocalContrastedImages=0;
 CurrentHistorySize=0;
 CurrentFirstHistoryIndex=-1;


 HistorySize=0;
}

UBAMovingDetector::~UBAMovingDetector(void)
{
 if(LocalContrastedImages)
  delete[] LocalContrastedImages;
 LocalContrastedImages=0;
}
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
// Число изображений в истории
int UBAMovingDetector::GetHistorySize(void) const
{
 return HistorySize;
}

bool UBAMovingDetector::SetHistorySize(int value)
{
 if(HistorySize == value)
  return true;

 if(value<1)
  return false;

 HistorySize=value;
 Ready=false;
 return true;
}
// --------------------------

// --------------------------
// Методы доступа к данным
// --------------------------
// Текущее входное изображение
const UBitmap* UBAMovingDetector::GetInputData(void) const
{
 return Input;
}

// Выходные данные
const UBRect* UBAMovingDetector::GetMovedObjects(void) const
{
 return MovedObjects;
}

// Обработанные изображения
const UBitmap* UBAMovingDetector::GetLocalContrastedImages(void) const
{
 return LocalContrastedImages;
}

// Текущий размер истории
int UBAMovingDetector::GetCurrentHistorySize(void) const
{
 return CurrentHistorySize;
}

// Текущий первый кадр истории
int UBAMovingDetector::GetCurrentFirstHistoryIndex(void) const
{
 return CurrentFirstHistoryIndex;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
/// Сдвигает историю
void UBAMovingDetector::HistoryShift(void)
{
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
}

// Восстановление настроек по умолчанию и сброс процесса счета
bool UBAMovingDetector::ADefault(void)
{
 return AFCDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBAMovingDetector::ABuild(void)
{

 if(LocalContrastedImages)
  delete[] LocalContrastedImages;
 LocalContrastedImages=0;
 LocalContrastedImages=new UBitmap[HistorySize];

 CurrentFirstHistoryIndex=-1;
 CurrentHistorySize=0;
 return AFCBuild();
}

// Сброс процесса счета.
bool UBAMovingDetector::AReset(void)
{
 return AFCReset();
}

// Выполняет расчет этого объекта
bool UBAMovingDetector::ACalculate(void)
{
 if(!Input)
  return true;

 return AFCCalculate();
}
// --------------------------

// class UBANightMovingDetector
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBANightMovingDetector::UBANightMovingDetector(void)
{
 // Размер блока изображения
 BlockWidth=16;
 BlockHeight=20;

 // Пороги
 T1=0.45;

 // Коэффициент расстояния между кадрами
 Tr=0.8; // 0.8-0.9

 T=0;

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

 MovingDetectionMode=0;

 HistLeftRange=3;
 HistRightRange=25;

 MovingFrameMode=1;
}

UBANightMovingDetector::~UBANightMovingDetector(void)
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
// Размер блока изображения
int UBANightMovingDetector::GetBlockWidth(void) const
{
 return BlockWidth;
}

bool UBANightMovingDetector::SetBlockWidth(int value)
{
 if(BlockWidth == value)
  return true;

 Ready=false;
 BlockWidth=value;
 return true;
}

int UBANightMovingDetector::GetBlockHeight(void) const
{
 return BlockHeight;
}

bool UBANightMovingDetector::SetBlockHeight(int value)
{
 if(BlockHeight == value)
  return true;

 Ready=false;
 BlockHeight=value;
 return true;
}

// Режим определения движения
int UBANightMovingDetector::GetMovingDetectionMode(void) const
{
 return MovingDetectionMode;
}

bool UBANightMovingDetector::SetMovingDetectionMode(int value)
{
 if(MovingDetectionMode == value)
  return true;

 MovingDetectionMode=value;
 return true;
}

// Диапазон анализа гистограммы
int UBANightMovingDetector::GetHistLeftRange(void) const
{
 return HistLeftRange;
}

bool UBANightMovingDetector::SetHistLeftRange(int value)
{
 if(HistLeftRange == value)
  return true;

 HistLeftRange=value;
 return true;
}

int UBANightMovingDetector::GetHistRightRange(void) const
{
 return HistRightRange;
}

bool UBANightMovingDetector::SetHistRightRange(int value)
{
 if(HistRightRange == value)
  return true;

 HistRightRange=value;
 return true;
}

// Режим формирования движущегося кадра
int UBANightMovingDetector::GetMovingFrameMode(void) const
{
 return MovingFrameMode;
}

bool UBANightMovingDetector::SetMovingFrameMode(int value)
{
 if(MovingFrameMode == value)
  return true;

 MovingFrameMode=value;
 return true;
}
// --------------------------

// --------------------------
// Методы доступа к данным
// --------------------------
// Изображение с обнаружением движущихся объектов
const UBitmap& UBANightMovingDetector::GetMovedImage(void) const
{
 return MovedImage;
}

// Число блоков
int UBANightMovingDetector::GetNumBlocks(void) const
{
 return NumBlocks;
}

// Массив локальных контрастов
const double* UBANightMovingDetector::GetCL(void) const
{
 return CL;
}

// Массив средних
const double* UBANightMovingDetector::GetML(void) const
{
 return ML;
}

// Массив СКО
const double* UBANightMovingDetector::GetSigmaL(void) const
{
 return SigmaL;
}

// Изображение разностного кадра
const UBitmap& UBANightMovingDetector::GetDiffImage(void) const
{
 return DiffImage;
}

// Гистограмма
const UBHistogram& UBANightMovingDetector::GetHistogram(void) const
{
 return Histogram;
}

// Сетка контрастных объектов
const UBRect* UBANightMovingDetector::GetContrastGrid(void) const
{
 return ContrastGrid;
}

const UBRect& UBANightMovingDetector::GetContrastGrid(int i) const
{
 return ContrastGrid[i];
}


// Сетка движущихся объектов
const UBRect* UBANightMovingDetector::GetMovedGrid(void) const
{
 return MovedGrid;
}

const UBRect& UBANightMovingDetector::GetMovedGrid(int i) const
{
 return MovedGrid[i];
}
// --------------------------


// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBANightMovingDetector* UBANightMovingDetector::New(void)
{
 return new UBANightMovingDetector;
}
// ---------------------


// ---------------------
// Скрытые методы счета
// ---------------------
// Установка разрешения входных изображений
bool UBANightMovingDetector::SetRes(int width, int height)
{
 if(Width == width && Height == height)
  return true;

 Width=width;
 Height=height;
 Ready=false;
 return true;
}

// Вычисление локального контраста
bool UBANightMovingDetector::CalcLocalContrasting(void)
{
 if(!Input)
  return false;

 memset(CL,0,sizeof(double)*NumBlocks);
 memset(ML,0,sizeof(double)*NumBlocks);
 memset(SigmaL,0,sizeof(double)*NumBlocks);
 double* pML=ML;
 double* pCL=CL;
 double* pSigmaL=SigmaL;
 double sum,sub;

// int index=0;
 for(int q=0;q<YBlocks;q++)
 {
  for(int p=0;p<XBlocks;p++)
  {
   sum=0;
   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     sum+=double((*Input)(p*BlockWidth+i,q*BlockHeight+j))/255.0;
    }
   }
   *pML=sum/(BlockWidth*BlockHeight);

   sum=0;
   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     sub=double((*Input)(p*BlockWidth+i,q*BlockHeight+j))/255.0-*pML;
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
bool UBANightMovingDetector::CalcLocalMap(void)
{
 UBitmap &out=LocalContrastedImages[CurrentFirstHistoryIndex];

 double* pCL=CL;
 UBRect *pContrastGrid=ContrastGrid;
 for(int q=0;q<YBlocks;q++)
 {
  for(int p=0;p<XBlocks;p++)
  {
   if(*pCL>=T1)
   {
    pContrastGrid->X=p*BlockWidth;
    pContrastGrid->Y=q*BlockHeight;
    pContrastGrid->X2(pContrastGrid->X+BlockWidth-1);
    pContrastGrid->Y2(pContrastGrid->Y+BlockHeight-1);
   }
   else
   {
    pContrastGrid->X=0;
    pContrastGrid->Y=0;
    pContrastGrid->X2(0);
    pContrastGrid->Y2(0);
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
bool UBANightMovingDetector::CalcMovedObjects(void)
{
 MovedImage.SetRes(LocalContrastedImages[CurrentFirstHistoryIndex].GetWidth(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetHeight(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetColorModel());
 DiffImage.SetRes(LocalContrastedImages[CurrentFirstHistoryIndex].GetWidth(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetHeight(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetColorModel());

 UBRect *pMovedGrid=MovedGrid;

// double* pT=T;

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

 for(int q=0;q<YBlocks;q++)
 {
  for(int p=0;p<XBlocks;p++)
  {
   int vis=0;
   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     if(double(DiffImage(p*BlockWidth+i,q*BlockHeight+j))/255.0>TT)
     {
      ++vis;
      if(MovingFrameMode == 0)
       MovedImage(p*BlockWidth+i,q*BlockHeight+j)=((*Input)(p*BlockWidth+i,q*BlockHeight+j));
     }
     else
     {
      if(MovingFrameMode == 0)
       MovedImage(p*BlockWidth+i,q*BlockHeight+j)=0;
     }

    }
   }

   if(vis>(BlockWidth*BlockHeight*MoveDetectionPercent)/100.0)
   {
    pMovedGrid->X=p*BlockWidth;
    pMovedGrid->Y=q*BlockHeight;
    pMovedGrid->X2(pMovedGrid->X+BlockWidth-1);
    pMovedGrid->Y2(pMovedGrid->Y+BlockHeight-1);
   }
   else
   {
    pMovedGrid->X=0;
    pMovedGrid->Y=0;
    pMovedGrid->X2(0);
    pMovedGrid->Y2(0);
   }

   if(MovingFrameMode == 1)
   {
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
   }

   ++pMovedGrid;
  }
 }

 return true;
}

// Обнаружение движущихся объектов на основе нормировки разности
bool UBANightMovingDetector::CalcNormalMovedObjects(void)
{
 MovedImage.SetRes(LocalContrastedImages[CurrentFirstHistoryIndex].GetWidth(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetHeight(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetColorModel());
 DiffImage.SetRes(LocalContrastedImages[CurrentFirstHistoryIndex].GetWidth(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetHeight(),
                LocalContrastedImages[CurrentFirstHistoryIndex].GetColorModel());

 UBRect *pMovedGrid=MovedGrid;
// double* pCL=CL;

// double* pT=T;

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

// for(int i=0;i<DiffImage.GetLength();i++)
//  DiffImage[i]=abs(int(LocalContrastedImages[i1][i])-int(LocalContrastedImages[i2][i]));

 for(int q=0;q<YBlocks;q++)
 {
  for(int p=0;p<XBlocks;p++)
  {
   int vis=0;
   for(int j=0;j<BlockHeight;j++)
   {
    for(int i=0;i<BlockWidth;i++)
    {
     double maxpic=LocalContrastedImages[i1](p*BlockWidth+i,q*BlockHeight+j);
     if(maxpic<LocalContrastedImages[i2](p*BlockWidth+i,q*BlockHeight+j))
      maxpic=LocalContrastedImages[i2](p*BlockWidth+i,q*BlockHeight+j);
     double diff=abs(int(LocalContrastedImages[i1](p*BlockWidth+i,q*BlockHeight+j))-int(LocalContrastedImages[i2](p*BlockWidth+i,q*BlockHeight+j)));
     if(maxpic && diff/maxpic>AdaptiveThresholdPercent/100.0)
     {
      ++vis;
      if(MovingFrameMode == 0)
       MovedImage(p*BlockWidth+i,q*BlockHeight+j)=((*Input)(p*BlockWidth+i,q*BlockHeight+j));
     }
     else
     {
      if(MovingFrameMode == 0)
       MovedImage(p*BlockWidth+i,q*BlockHeight+j)=0;
     }

    }
   }

  // ++pCL;
   if(vis>(BlockWidth*BlockHeight*MoveDetectionPercent)/100.0)
   {
    pMovedGrid->X=p*BlockWidth;
    pMovedGrid->Y=q*BlockHeight;
    pMovedGrid->X2(pMovedGrid->X+BlockWidth-1);
    pMovedGrid->Y2(pMovedGrid->Y+BlockHeight-1);
   }
   else
   {
    pMovedGrid->X=0;
    pMovedGrid->Y=0;
    pMovedGrid->X2(0);
    pMovedGrid->Y2(0);
   }


   if(MovingFrameMode == 1)
   {
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
   }
   ++pMovedGrid;
  }
 }

 return true;
}



// Расчет адаптивного порога
bool UBANightMovingDetector::CalcAdaptiveThreshold(void)
{
 unsigned minval,maxval;
 int min_i=-1/*,max_i=-1*/;

// double *pT=T;

 Histogram.Calc(DiffImage);
//   memmove(Histogram,Histogram+1,255*sizeof(UBHistogramElement));

   // Ищем маскимум гистограммы
   maxval=0;
   for(int i=HistLeftRange;i<256;i++)
   {
	if(Histogram[i].Int>maxval)
    {
//     max_i=i;
     maxval=Histogram[i].Int;
    }
   }

   // Ищем яркость AdaptiveThresholdPercent% от максимума
   minval=0;
   for(int i=HistLeftRange;i<HistRightRange;i++)
   {
    if(Histogram[i].Int<=(maxval*AdaptiveThresholdPercent)/100.0 && Histogram[i].Int>=minval)
    {
	 minval=Histogram[i].Int;
     min_i=i;
    }
   }

   if(min_i>0)
    TT=double(Histogram[min_i].Color.rgb.b)/255.0;
   else
    TT=0;


 return true;
}
// ---------------------


// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBANightMovingDetector::AFCDefault(void)
{
 // Временные переменные для вычисления локального контраста
 // Число блоков
 NumBlocks=0;

 MovingDetectionMode=0;

 HistLeftRange=3;
 HistRightRange=25;

 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBANightMovingDetector::AFCBuild(void)
{
 XBlocks=Width/BlockWidth,YBlocks=Height/BlockHeight;
 NumBlocks=XBlocks*YBlocks;

 // Массив локальных контрастов
 if(CL) delete[] CL;
  CL=new double[NumBlocks];

 // Массив средних
 if(ML) delete[] ML;
  ML=new double[NumBlocks];

 // Массив СКО
 if(SigmaL) delete[] SigmaL;
  SigmaL=new double[NumBlocks];

 if(T) delete[] T;
  T=new double[NumBlocks];
  memset(T,0,NumBlocks*sizeof(double));

 // Данные карты
 if(MCm) delete[] MCm;
 MCm=0;
 if(ICm) delete[] ICm;
 ICm=0;

 Histogram.Resize(256);

 // Сетка контрастных объектов
 if(ContrastGrid) delete[] ContrastGrid;
  ContrastGrid=new UBRect[NumBlocks];

 // Сетка движущихся объектов
 if(MovedGrid) delete[] MovedGrid;
  MovedGrid=new UBRect[NumBlocks];

 return true;
}

// Сброс процесса счета.
bool UBANightMovingDetector::AFCReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBANightMovingDetector::AFCCalculate(void)
{
 SetRes(Input->GetWidth(),Input->GetHeight());
 UBMColorModel c=Input->GetColorModel();

 if(Width < BlockWidth || Height < BlockHeight || c != ubmY8)// || c != ubmY8 || c != ubmY32)
  return false;

 if(!IsReady())
  if(!Reset())
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

 HistoryShift();

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

 // Вычисляем локальный контраст
 if(!CalcLocalContrasting())
  return false;

 // Вычисляем карту локальной заметности
 if(!CalcLocalMap())
  return false;

 // Обнаружение движущихся объектов
 switch(MovingDetectionMode)
 {
 case 0:
  if(!CalcMovedObjects())
   return false;
 break;
 case 1:
  if(!CalcNormalMovedObjects())
   return false;
 break;
 }

 // Вычисляем адаптивный порог
 if(!CalcAdaptiveThreshold())
  return false;

 return true;
}
// --------------------------



// Класс UBACollateMovingDetector
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBACollateMovingDetector::UBACollateMovingDetector(void)
{
}

UBACollateMovingDetector::~UBACollateMovingDetector(void)
{
}
// --------------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBACollateMovingDetector* UBACollateMovingDetector::New(void)
{
 return new UBACollateMovingDetector;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBACollateMovingDetector::AFCDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBACollateMovingDetector::AFCBuild(void)
{
 return true;
}

// Сброс процесса счета.
bool UBACollateMovingDetector::AFCReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
#ifdef __BORLANDC__
#pragma warn -8058
#endif
bool UBACollateMovingDetector::AFCCalculate(void)
{
// UBMColorModel c=Input->GetColorModel();

 if(!IsReady())
  if(!Reset())
   return false;

 for(int i=0;i<HistorySize;i++)
  LocalContrastedImages[i].SetRes(Input->GetWidth(),Input->GetHeight(),Input->GetColorModel());

/* for(int i=0;i<CurrentHistorySize;i++)
 {
  if(LocalContrastedImages[i].GetWidth() != Width ||
     LocalContrastedImages[i].GetHeight() != Height ||
     LocalContrastedImages[i].GetColorModel() != c)
   return false;
 }*/

 HistoryShift();

 LocalContrastedImages[CurrentFirstHistoryIndex]=*Input;

 if(CurrentHistorySize<2)
  return true;

 // Вычисляем разностный кадр
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


 DiffImage.SetRes(Input->GetWidth(),Input->GetHeight(),Input->GetColorModel());
 for(int i=0;i<Input->GetLength();i++)
 {
  UColorT c1=LocalContrastedImages[i1](i);
  UColorT c2=LocalContrastedImages[i2](i);
  int m=(c1.ycrcb.y>c2.ycrcb.y)?c1.ycrcb.y:c2.ycrcb.y;
  if(m>0)
   DiffImage(i).ycrcb.y=(abs(c1.ycrcb.y-c2.ycrcb.y)*255)/m;
  else
   DiffImage(i).ycrcb.y=0;
 }

 return true;
}
#ifdef __BORLANDC__
#pragma warn .8058
#endif
// --------------------------

}


#endif


