#ifndef UBABACKGROUND_CPP
#define UBABACKGROUND_CPP
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBABackground.h"
#include <math.h>

namespace RDK {

// --------------------------------------------------------------------------------------------------------------------
// ПРОСТОЙ РАЗНОСТНЫЙ КАДР
// -------------------------------------------------------


// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABackground::UBABackground(void)
: Input("Input",this),
  Background("Background",this),
  IsBGReady("IsBGReady",this)
{
}

UBABackground::~UBABackground(void)
{
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABackground::ADefault(void)
{
 return AFBgDefault();
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABackground::ABuild(void)
{
 return AFBgBuild();
}

// Сброс процесса счета без потери настроек
bool UBABackground::AReset(void)
{
 return AFBgReset();
}

// Выполняет расчет этого объекта
bool UBABackground::ACalculate(void)
{
 return AFBgCalculate();
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABackground::AFBgDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABackground::AFBgBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBABackground::AFBgReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBABackground::AFBgCalculate(void)
{
 return true;
}
// --------------------------



// ---------------------
// Методы счета
// ---------------------
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABackgroundAvg::UBABackgroundAvg(void)
 : HistorySize("HistorySize",this)
{
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
}

UBABackgroundAvg::~UBABackgroundAvg(void)
{

}
// ---------------------


// Создание новой копии этого объекта
UBABackgroundAvg* UBABackgroundAvg::New(void)
{
 return new UBABackgroundAvg;
}

bool UBABackgroundAvg::BCalculate(UBitmap &input, UBitmap &background)
{
 if(HistorySize<=0)
  return true;

 if(History.GetSize() != HistorySize)
  History.Resize(HistorySize);

 if(CurrentHistorySize>HistorySize)
  CurrentHistorySize=HistorySize;

 if(CurrentHistoryIndex>=HistorySize)
  CurrentHistoryIndex=0;

 History(CurrentHistoryIndex)=input;
 if(CurrentHistorySize<HistorySize)
  ++CurrentHistorySize;
 ++CurrentHistoryIndex;

 for(int i=0;i<CurrentHistorySize;i++)
 {
  if(History(i).GetWidth() != background.GetWidth() ||
	 History(i).GetHeight() != background.GetHeight() ||
	 History(i).GetColorModel() != background.GetColorModel())
  {
   background=input;
   return true;
  }
 }

 UBColor *bg=background.GetData();
 for(int j=0;j<background.GetByteLength();j++)
 {
  unsigned pixel=0;
  for(int i=0;i<CurrentHistorySize;i++)
   pixel+=History(i)[j];
  if(CurrentHistorySize>0)
   *bg++=static_cast<unsigned char>(pixel/CurrentHistorySize);
 }

 return true;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABackgroundAvg::AFBgDefault(void)
{
 HistorySize=10;
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABackgroundAvg::AFBgBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBABackgroundAvg::AFBgReset(void)
{
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
 return true;
}

// Выполняет расчет этого объекта
bool UBABackgroundAvg::AFBgCalculate(void)
{
 Background->SetRes(Input->GetWidth(), Input->GetHeight(), Input->GetColorModel());
 return BCalculate(*Input, *Background);
}
// --------------------------



// ------------------------------------------------------------------------------------------------------------------
// КАДР МЕТОДОМ ЭКСПОНЕНЦИАЛЬНОГО СКОЛЬЗЯЩЕГО СРЕДНЕГО// -------------------------------------------------------

// --------------------
// Методы счета
// ---------------------
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABackgroundExponnential::UBABackgroundExponnential(void)
 : tempoUpdate("tempoUpdate",this)
{
 //HistorySize=0;
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
 tempoUpdate = 0.05;
}

UBABackgroundExponnential::~UBABackgroundExponnential(void)
{

}
// ---------------------


// Создание новой копии этого объекта
UBABackgroundExponnential* UBABackgroundExponnential::New(void)
{
 return new UBABackgroundExponnential;
}

bool UBABackgroundExponnential::BCalculate(UBitmap &input, UBitmap &background)
{
  //Если изображение поменяло формат
  if(input.GetWidth() != background.GetWidth() ||
  input.GetHeight() != background.GetHeight() ||
  input.GetColorModel() != background.GetColorModel())
  {
    background=input;
    CurrentHistorySize=0;
    return true;
  }


//Фон = Предыдущий фон*(а-1)+Текущий кадр*а
//а - темп обновления 0<a<1
 UBColor *bg=background.GetData();
 UBColor *inp=input.GetData();
 for(int j=0;j<background.GetByteLength();j++)
 {
  //int tmp=static_cast<int>(double(*bg)*(1.0-tempoUpdate.v));
  double tmp2=double(*bg)*(1.0-tempoUpdate.v);

  //int tmp3=tempoUpdate.v*double((*inp));
  double tmp4=tempoUpdate.v*double((*inp));

  *bg=static_cast<unsigned char>(tmp2+tmp4);
  CurrentHistorySize++;
  ++bg; ++inp;
 }

 return true;
}

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABackgroundExponnential::AFBgDefault(void)
{
 CurrentHistorySize=10;
 tempoUpdate = 0.05;
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABackgroundExponnential::AFBgBuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBABackgroundExponnential::AFBgReset(void)
{
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
 *Background=*Input;
 return true;
}

// Выполняет расчет этого объекта
bool UBABackgroundExponnential::AFBgCalculate(void)
{
    if (Background->GetWidth()!=Input->GetWidth() ||
        Background->GetHeight()!=Input->GetHeight() ||
        Background->GetColorModel()!=Input->GetColorModel())
    {
     Background->SetRes(Input->GetWidth(), Input->GetHeight(), Input->GetColorModel());
     Background->SetImage(Input->GetData());
    }
 return BCalculate(*Input, *Background);
}
// --------------------------

// ------------------------------------------------------------------------------------------------------------------
// РАЗНИЦА КАДРОВ МЕТОДОМ ЭКСПОНЕНЦИАЛЬНОГО СКОЛЬЗЯЩЕГО СРЕДНЕГО
// В INT И DOUBLE
// -------------------------------------------------------

// ---------------------
// Методы счета
// ---------------------
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBADeltaBackgroundExponnential::UBADeltaBackgroundExponnential(void)
 : tempoUpdate("tempoUpdate",this)
{
 //HistorySize=0;
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
 tempoUpdate = 0.05;
}

UBADeltaBackgroundExponnential::~UBADeltaBackgroundExponnential(void)
{

}
// ---------------------


// Создание новой копии этого объекта
UBADeltaBackgroundExponnential* UBADeltaBackgroundExponnential::New(void)
{
 return new UBADeltaBackgroundExponnential;
}

bool UBADeltaBackgroundExponnential::BCalculate(UBitmap &input, UBitmap &background)
{
 //Если изображение поменяло формат
 if(input.GetWidth() != background.GetWidth() ||
  input.GetHeight() != background.GetHeight() ||
  input.GetColorModel() != background.GetColorModel())
 {
     background=input;
     CurrentHistorySize=0;
     return true;
 }


//Фон = Предыдущий фон*(а-1)+Текущий кадр*а
//а - темп обновления 0<a<1
 UBColor *bg=background.GetData();
 UBColor *inp=input.GetData();
 for(int j=0;j<background.GetByteLength();j++)
 {
  int tmp=static_cast<int>(static_cast<double>(*bg)*(1.0-tempoUpdate.v));
  double tmp2=double(*bg)*(1.0-tempoUpdate.v);

  int tmp3=static_cast<int>(tempoUpdate.v*double((*inp)));
  double tmp4=tempoUpdate.v*double((*inp));

  tmp = tmp+tmp3;
  tmp2 = tmp2+tmp4;
  //*bg = tmp2;
  if (tmp2>tmp)
    *bg=static_cast<unsigned char>(tmp2-tmp);
  else
    *bg=static_cast<unsigned char>(tmp-tmp2);
  CurrentHistorySize++;
  ++bg; ++inp;
 }

 return true;
}
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBADeltaBackgroundExponnential::AFBgDefault(void)
{
 CurrentHistorySize=10;
 tempoUpdate = 0.05;
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBADeltaBackgroundExponnential::AFBgBuild(void)
{
 *Background=*Input;
 return true;
}

// Сброс процесса счета без потери настроек
bool UBADeltaBackgroundExponnential::AFBgReset(void)
{
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
 return true;
}

// Выполняет расчет этого объекта
bool UBADeltaBackgroundExponnential::AFBgCalculate(void)
{
 Background->SetRes(Input->GetWidth(), Input->GetHeight(), Input->GetColorModel());
 return BCalculate(*Input, *Background);
}
// --------------------------


//----------------------------------------------------------------------------
//АДАПТИВНЫЙ САМЫЙ ПРОСТОЙ ФОН
//----------------------------------------------------------------------------

// ---------------------
// Методы счета
// ---------------------
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABackgroundSimpleAdaptive::UBABackgroundSimpleAdaptive(void)
 : tempoUpdate("tempoUpdate",this),
   tempoUpdateFG("tempoUpdateFG",this),
   tempoUpdateBG("tempoUpdateBG",this),
   lastBinarization("lastBinarization", this),
   delay ("delay", this),
   //UpdateFGFlag ("UpdateFGFlag", this),
   modeTypes("modeTypes", this),
   lastInput("lastInput", this),
   deltaFrames("deltaFrames", this),
   updateFGFlag ("updateFGFlag", this),
   zeroingUpdateFlag("zeroingUpdateFlag", this),
   output2("output2", this),
   countFirstCleanBgFrame("countFirstCleanBgFrame", this)
{

    //HistorySize=0;
    CurrentHistoryIndex = 0;
    CurrentHistorySize = 0;
    tempoUpdate = 0.05;
    tempoUpdateFG = 0.0001;
    tempoUpdateBG = 0.01;
    delay = 1;
    //UpdateFGFlag = 0;
    modeTypes = 2;
    deltaFrames=10;
    zeroingUpdateFlag = 200;
    countFirstCleanBgFrame = 50;
    IsBGReady = false;

}
UBABackgroundSimpleAdaptive::~UBABackgroundSimpleAdaptive(void)
{
    countFirstCleanBgFrame=50;
}
// Создание новой копии этого объекта
UBABackgroundSimpleAdaptive* UBABackgroundSimpleAdaptive::New(void)
{
    return new UBABackgroundSimpleAdaptive;
}

bool UBABackgroundSimpleAdaptive::BCalculateExp(UBitmap &input, UBitmap &background)
{
    //Если изображение поменяло формат
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() ||
    input.GetColorModel() != background.GetColorModel())
    {
        background=input;
        CurrentHistorySize=0;
        return true;
    }
    //Фон = Предыдущий фон*(а-1)+Текущий кадр*а
    //а - темп обновления 0<a<1
    UBColor *bg=background.GetData();
    UBColor *inp=input.GetData();
    for(int j=0;j<background.GetByteLength();j++)
    {
        //int tmp=double(*bg)*(1.0-tempoUpdate.v);
        double tmp2=double(*bg)*(1.0-tempoUpdate.v);
        //int tmp3=tempoUpdate.v*double((*inp));
        double tmp4=tempoUpdate.v*double((*inp));
        *bg=static_cast<unsigned char>(tmp2+tmp4);
        CurrentHistorySize++;
        ++bg; ++inp;
    }
    return true;
}

bool UBABackgroundSimpleAdaptive::BCalculateSimplAdaptive
(UBitmap &input, UBitmap &background, UBitmap &lastBinarization)
{
    //Если изображение поменяло формат
    //Говорим, что новый фон = первому кадру нового формата
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() ||
    input.GetColorModel() != background.GetColorModel())
    {
        background=input;
        CurrentHistorySize=0;
        return true;
    }
    UBColor *bg=background.GetData();
    UBColor *inp=input.GetData();
    //Если бинаризованный кадр не определен
    if(input.GetWidth() != lastBinarization.GetWidth() ||
       input.GetHeight() != lastBinarization.GetHeight())
    {
        for(int j=0;j<background.GetByteLength();j++)
        {
            double tmp2=double(*bg)*(1.0-tempoUpdate.v);
            double tmp4=tempoUpdate.v*double((*inp));
            *bg=static_cast<unsigned char>(tmp2+tmp4);

            CurrentHistorySize++;
            ++bg;
            ++inp;
        }
        return true;
    }
    //Если бинаризованный кадр определен
    else
    {
        UBColor *bin=lastBinarization.GetData();
        //Идем попиксельно по кадру
        for(int j=0;j<background.GetByteLength();j++)
        {
            double tmp2, tmp4;
            //Если текущий пиксель относится к переднему плану
            if ((*bin)==255)
            {
                tmp2=double(*bg)*(1.0-tempoUpdateFG.v);
                tmp4=tempoUpdateFG.v*double((*inp));
                *bg=static_cast<unsigned char>(tmp2+tmp4);
            }
            //Если текущий пиксель относится к фону
            else
            {
                tmp2=double(*bg)*(1.0-tempoUpdateBG.v);
                tmp4=tempoUpdateBG.v*double((*inp));
                *bg=static_cast<unsigned char>(tmp2+tmp4);
            }

            CurrentHistorySize++;
            ++bg;
            ++inp;
            ++bin;
        }
     }
     return true;
}

bool UBABackgroundSimpleAdaptive::BCalculateStabilityIndicator(UBitmap &input, UBitmap &background, UBitmap &lastBinarization, UBitmap &lastInput, UBitmap &updateFGFlag)
{
    //Если изображение поменяло формат
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() ||
    input.GetColorModel() != background.GetColorModel())
    {
        background=input;
        return true;
    }
    UBColor *bg=background.GetData();
    UBColor *inp=input.GetData();
    unsigned *updateflag=reinterpret_cast<unsigned*>(updateFGFlag.GetData());
    //Если бинаризованный кадр не определен
    if(input.GetWidth() != lastBinarization.GetWidth() ||
       input.GetHeight() != lastBinarization.GetHeight())
    {
        for(int j=0;j<background.GetByteLength();j++)
        {
            double tmp2=double(*bg)*(1.0-tempoUpdate.v);
            double tmp4=tempoUpdate.v*double((*inp));
            *bg=static_cast<unsigned char>(tmp2+tmp4);

            CurrentHistorySize++;
            ++bg;
            ++inp;
        }
        return true;
    }
    //Если бинаризованный кадр определен
    else
    {
        UBColor *bin=lastBinarization.GetData();
        UBColor *lin=lastInput.GetData();
        for(int j=0;j<background.GetByteLength();j++)
        {
            double tmp2, tmp4;
            //Если текущий пиксель относится к переднему плану
            if ((*bin)==255)
            {
                if ((int(*lin)-int(*inp))<deltaFrames && (int(*lin)-int(*inp))>-deltaFrames)
                {
                    //Если Индикатор стабильности дошел до стабильности
                    if(*updateflag >=zeroingUpdateFlag)
                    {
                        tmp2=double(*bg)*(1.0-tempoUpdateFG.v);
                        tmp4=tempoUpdateFG.v*double((*inp));
                        *bg=static_cast<unsigned char>(tmp2+tmp4);
                        *updateflag=0;
                    }
                    else
                        *updateflag+=delay.v;

                }
            }
            //Если текущий пиксель относится к фону
            else
            {
                tmp2=double(*bg)*(1.0-tempoUpdateBG.v);
                tmp4=tempoUpdateBG.v*double((*inp));
                *bg=static_cast<unsigned char>(tmp2+tmp4);
                *updateflag=0;
            }
            ++bg;
            ++inp;
            ++bin;
            ++lin;
            ++updateflag;
        }
     return true;
    }
}


bool UBABackgroundSimpleAdaptive::BCalculateFirstBackground
(UBitmap &input, UBitmap &background)
{
    //Если изображение поменяло формат
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() ||
    input.GetColorModel() != background.GetColorModel())
    {
        background=input;
        return true;
    }
    //фон
    UBColor *bg=background.GetData();
    //текущий кадр
    UBColor *inp=input.GetData();

    //коэфф для обновления фона
    double a, b;

    b = static_cast<double>(1./(static_cast<double>(nCounterBG)));
    a=static_cast<double>((nCounterBG-1)*b);


    //newb = (unsigned int)(a*bac+b*inp)
    for(int j=0;j<background.GetByteLength();j++)
    {
        *bg=static_cast<unsigned char>(a*(*bg)+b*(*inp));
        ++bg;
        ++inp;
    }
    return true;
}


// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABackgroundSimpleAdaptive::AFBgDefault(void)
{

    tempoUpdate = 0.05;
    tempoUpdateFG = 0.0001;
    tempoUpdateBG = 0.01;
    delay = 1;
    //UpdateFGFlag = 0;
    modeTypes = 2;
    deltaFrames=10;
    zeroingUpdateFlag = 200;
    countFirstCleanBgFrame = 50;

    return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABackgroundSimpleAdaptive::AFBgBuild(void)
{
    return true;
}

// Сброс процесса счета без потери настроек
bool UBABackgroundSimpleAdaptive::AFBgReset(void)
{
    updateFGFlag->Fill(0);
    //UpdateFGFlag = 0;
    *Background=*Input;
    nCounterBG=1;
    IsBGReady = false;
    return true;
}

// Выполняет расчет этого объекта
bool UBABackgroundSimpleAdaptive::AFBgCalculate(void)
{
    //int static n=1;

    if (Background->GetWidth()!=Input->GetWidth() ||
        Background->GetHeight()!=Input->GetHeight() ||
        Background->GetColorModel()!=Input->GetColorModel())
    {
        Background->SetRes(Input->GetWidth(), Input->GetHeight(), Input->GetColorModel());
        Background->SetImage(Input->GetData());
    }
    if (lastInput->GetWidth()!=Input->GetWidth() ||
        lastInput->GetHeight()!=Input->GetHeight() ||
        lastInput->GetColorModel()!=Input->GetColorModel())
    {
        *lastInput=*Input;
    }
    if (updateFGFlag->GetWidth()!=Input->GetWidth() ||
        updateFGFlag->GetHeight()!=Input->GetHeight() ||
        updateFGFlag->GetColorModel()!=ubmY32)
    {
        updateFGFlag->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY32);
        updateFGFlag->Fill(0);
    }
    if (output2->GetWidth()!=Background->GetWidth() ||
        output2->GetHeight()!=Background->GetHeight() ||
        output2->GetColorModel()!=Background->GetColorModel())
    {
        output2->SetRes(Background->GetWidth(), Background->GetHeight(), ubmY32);
    }

    if (nCounterBG < countFirstCleanBgFrame)
    {
        IsBGReady = false;
        BCalculateFirstBackground(*Input, *Background);
        nCounterBG++;
    }
    else
    {
        IsBGReady = true;
        if (modeTypes==0)
            BCalculateExp(*Input, *Background);
        if (modeTypes==1)
            BCalculateSimplAdaptive(*Input, *Background, *lastBinarization);
        if (modeTypes==2)
            BCalculateStabilityIndicator
            (*Input, *Background, *lastBinarization, *lastInput, *updateFGFlag);
        *lastInput=*Input;
    }

    //другой выход для другой модели
    //unsigned* out2 = (unsigned*)output2->GetData();
    unsigned* out2 = reinterpret_cast<unsigned*>(output2->GetData());
    UBColor* out1 =Background->GetData();
    for(int j=0;j<(*output2).GetLength();j++)
    {
        //*(output2+j)=(int)((*(Background+j)->GetData())<<25);
        *out2 = *out1;
        *out2 <<= 24;
        out2++;
        out1++;
    }

    return true;
}
// --------------------------







//------------------------------------------------------------------------
// Фон в зависимоти от текущего дельта между фоном и текущим кадром
//------------------------------------------------------------------------
// ---------------------
// Методы счета
// ---------------------
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABackgroundDependDiff::UBABackgroundDependDiff(void)
 : //StateTempoDif("StateTempoDif",this),
   deltaImg("deltaImg",this),
   countFirstCleanBgFrame("countFirstCleanBgFrame", this)
{
    //StateTempoDif = 242;
    countFirstCleanBgFrame = 50;
    nCounterBG=1;
    IsBGReady = false;
}
UBABackgroundDependDiff::~UBABackgroundDependDiff(void)
{
  ;
}
// Создание новой копии этого объекта
UBABackgroundDependDiff* UBABackgroundDependDiff::New(void)
{
    return new UBABackgroundDependDiff;
}

bool UBABackgroundDependDiff::BCalculateFirstBackground
(UBitmap &input, UBitmap &background)
{
    //Если изображение поменяло формат
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() ||
    input.GetColorModel() != background.GetColorModel())
    {
        background=input;
        return true;
    }
    //фон
    UBColor *bg=background.GetData();
    //текущий кадр
    UBColor *inp=input.GetData();

    //коэфф для обновления фона
    double a, b;

    b = static_cast<double>(1./static_cast<double>(nCounterBG));
    a=static_cast<double>((nCounterBG-1)*b);


    //newb = (unsigned int)(a*bac+b*inp)
    for(int j=0;j<background.GetByteLength();j++)
    {
        *bg=static_cast<unsigned char>(a*(*bg)+b*(*inp));
        ++bg;
        ++inp;
    }
    return true;
}


double UBABackgroundDependDiff::BCalculate1
(UBitmap &input, UBitmap &background, UBitmap &diffImg)
{
    double midAl=0;
    //Если изображение поменяло формат
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() //||
    //input.GetColorModel() != background.GetColorModel()
            )
    {
        background=input;
        return true;
    }
    if(diffImg.GetWidth() != background.GetWidth() ||
    diffImg.GetHeight() != background.GetHeight() ||
    diffImg.GetColorModel() != background.GetColorModel())
    {
        diffImg=input;
        //фон
        UBColor *bg=background.GetData();
        //текущий кадр
        UBColor *inp=input.GetData();
        //разниц фона и текущего предыдущего кадра
        UBColor *delta=diffImg.GetData();
        for(int j=0;j<background.GetByteLength();j++)
        {
            if ((*bg - *inp)>=0)
                *delta =*bg - *inp;
            else
                *delta =*inp - *bg;

            delta++;
            inp++;
            bg++;

        }
        return true;
    }
    //фон
    UBColor *bg=background.GetData();
    //текущий кадр
    UBColor *inp=input.GetData();
    //разниц фона и текущего предыдущего кадра
    UBColor *delta=diffImg.GetData();

    for(int j=0;j<background.GetByteLength();j++)
    {
        //вычисляемый коэффициент обновления фона
        //на самом деле коэф это 1-альфа
        double alfa = *delta;
        //alfa +=(255-StateTempoDif);
        alfa /= 255.0;        
        if (alfa > 1)
            alfa =1;
        if (alfa<0)
            alfa=0;
        midAl+=alfa;
        *bg = static_cast<unsigned char>((*bg)*alfa + (1-alfa)*(*inp));
        //*bg = (*bg);

        bg++;
        delta++;
        inp++;
    }
    midAl/=background.GetByteLength();
    return midAl;
}


// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBABackgroundDependDiff::AFBgDefault(void)
{
    //StateTempoDif = 242;
    nCounterBG=1;
    return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBABackgroundDependDiff::AFBgBuild(void)
{
    return true;
}

// Сброс процесса счета без потери настроек
bool UBABackgroundDependDiff::AFBgReset(void)
{
    *Background=*Input;
    nCounterBG=1;
    IsBGReady = false;
    return true;
}

// Выполняет расчет этого объекта
bool UBABackgroundDependDiff::AFBgCalculate(void)
{
    //int static n=1;

    if (Background->GetWidth()!=Input->GetWidth() ||
        Background->GetHeight()!=Input->GetHeight() ||
        Background->GetColorModel()!=Input->GetColorModel())
    {
        Background->SetRes(Input->GetWidth(), Input->GetHeight(), Input->GetColorModel());
        Background->SetImage(Input->GetData());
    }

    if (deltaImg->GetWidth()!=Input->GetWidth() ||
        deltaImg->GetHeight()!=Input->GetHeight() ||
        deltaImg->GetColorModel()!=Input->GetColorModel())
    {
        deltaImg->SetRes(Input->GetWidth(), Input->GetHeight(), Input->GetColorModel());
        //разница максимальная
        //фон не обновляется
        deltaImg->Fill(255);
    }


    //первоначальная настройка  фона при отсутствии движущихся объектов
    if (nCounterBG < countFirstCleanBgFrame)
    {
        IsBGReady = false;
        BCalculateFirstBackground(*Input, *Background);
        nCounterBG++;
    }
    //рабочая часть, когда появляется движение
    else
    {
        IsBGReady = true;
        BCalculate1 (*Input, *Background, *deltaImg);
    }

    return true;
}






}
//---------------------------------------------------------------------------

#endif
