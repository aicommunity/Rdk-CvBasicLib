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
// ������� ���������� ����
// -------------------------------------------------------


// ---------------------
// ������������ � �����������
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
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABackground::ADefault(void)
{
 return AFBgDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABackground::ABuild(void)
{
 return AFBgBuild();
}

// ����� �������� ����� ��� ������ ��������
bool UBABackground::AReset(void)
{
 return AFBgReset();
}

// ��������� ������ ����� �������
bool UBABackground::ACalculate(void)
{
 return AFBgCalculate();
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABackground::AFBgDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABackground::AFBgBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABackground::AFBgReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBABackground::AFBgCalculate(void)
{
 return true;
}
// --------------------------



// ---------------------
// ������ �����
// ---------------------
// ---------------------
// ������������ � �����������
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


// �������� ����� ����� ����� �������
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
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABackgroundAvg::AFBgDefault(void)
{
 HistorySize=10;
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABackgroundAvg::AFBgBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABackgroundAvg::AFBgReset(void)
{
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
 return true;
}

// ��������� ������ ����� �������
bool UBABackgroundAvg::AFBgCalculate(void)
{
 Background->SetRes(Input->GetWidth(), Input->GetHeight(), Input->GetColorModel());
 return BCalculate(*Input, *Background);
}
// --------------------------



// ------------------------------------------------------------------------------------------------------------------
// ���� ������� ����������������� ����������� ��������// -------------------------------------------------------

// --------------------
// ������ �����
// ---------------------
// ---------------------
// ������������ � �����������
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


// �������� ����� ����� ����� �������
UBABackgroundExponnential* UBABackgroundExponnential::New(void)
{
 return new UBABackgroundExponnential;
}

bool UBABackgroundExponnential::BCalculate(UBitmap &input, UBitmap &background)
{
  //���� ����������� �������� ������
  if(input.GetWidth() != background.GetWidth() ||
  input.GetHeight() != background.GetHeight() ||
  input.GetColorModel() != background.GetColorModel())
  {
    background=input;
    CurrentHistorySize=0;
    return true;
  }


//��� = ���������� ���*(�-1)+������� ����*�
//� - ���� ���������� 0<a<1
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
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABackgroundExponnential::AFBgDefault(void)
{
 CurrentHistorySize=10;
 tempoUpdate = 0.05;
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABackgroundExponnential::AFBgBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABackgroundExponnential::AFBgReset(void)
{
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
 *Background=*Input;
 return true;
}

// ��������� ������ ����� �������
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
// ������� ������ ������� ����������������� ����������� ��������
// � INT � DOUBLE
// -------------------------------------------------------

// ---------------------
// ������ �����
// ---------------------
// ---------------------
// ������������ � �����������
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


// �������� ����� ����� ����� �������
UBADeltaBackgroundExponnential* UBADeltaBackgroundExponnential::New(void)
{
 return new UBADeltaBackgroundExponnential;
}

bool UBADeltaBackgroundExponnential::BCalculate(UBitmap &input, UBitmap &background)
{
 //���� ����������� �������� ������
 if(input.GetWidth() != background.GetWidth() ||
  input.GetHeight() != background.GetHeight() ||
  input.GetColorModel() != background.GetColorModel())
 {
     background=input;
     CurrentHistorySize=0;
     return true;
 }


//��� = ���������� ���*(�-1)+������� ����*�
//� - ���� ���������� 0<a<1
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
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBADeltaBackgroundExponnential::AFBgDefault(void)
{
 CurrentHistorySize=10;
 tempoUpdate = 0.05;
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBADeltaBackgroundExponnential::AFBgBuild(void)
{
 *Background=*Input;
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBADeltaBackgroundExponnential::AFBgReset(void)
{
 CurrentHistoryIndex=0;
 CurrentHistorySize=0;
 return true;
}

// ��������� ������ ����� �������
bool UBADeltaBackgroundExponnential::AFBgCalculate(void)
{
 Background->SetRes(Input->GetWidth(), Input->GetHeight(), Input->GetColorModel());
 return BCalculate(*Input, *Background);
}
// --------------------------


//----------------------------------------------------------------------------
//���������� ����� ������� ���
//----------------------------------------------------------------------------

// ---------------------
// ������ �����
// ---------------------
// ---------------------
// ������������ � �����������
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
// �������� ����� ����� ����� �������
UBABackgroundSimpleAdaptive* UBABackgroundSimpleAdaptive::New(void)
{
    return new UBABackgroundSimpleAdaptive;
}

bool UBABackgroundSimpleAdaptive::BCalculateExp(UBitmap &input, UBitmap &background)
{
    //���� ����������� �������� ������
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() ||
    input.GetColorModel() != background.GetColorModel())
    {
        background=input;
        CurrentHistorySize=0;
        return true;
    }
    //��� = ���������� ���*(�-1)+������� ����*�
    //� - ���� ���������� 0<a<1
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
    //���� ����������� �������� ������
    //�������, ��� ����� ��� = ������� ����� ������ �������
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
    //���� �������������� ���� �� ���������
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
    //���� �������������� ���� ���������
    else
    {
        UBColor *bin=lastBinarization.GetData();
        //���� ����������� �� �����
        for(int j=0;j<background.GetByteLength();j++)
        {
            double tmp2, tmp4;
            //���� ������� ������� ��������� � ��������� �����
            if ((*bin)==255)
            {
                tmp2=double(*bg)*(1.0-tempoUpdateFG.v);
                tmp4=tempoUpdateFG.v*double((*inp));
                *bg=static_cast<unsigned char>(tmp2+tmp4);
            }
            //���� ������� ������� ��������� � ����
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
    //���� ����������� �������� ������
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
    //���� �������������� ���� �� ���������
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
    //���� �������������� ���� ���������
    else
    {
        UBColor *bin=lastBinarization.GetData();
        UBColor *lin=lastInput.GetData();
        for(int j=0;j<background.GetByteLength();j++)
        {
            double tmp2, tmp4;
            //���� ������� ������� ��������� � ��������� �����
            if ((*bin)==255)
            {
                if ((int(*lin)-int(*inp))<deltaFrames && (int(*lin)-int(*inp))>-deltaFrames)
                {
                    //���� ��������� ������������ ����� �� ������������
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
            //���� ������� ������� ��������� � ����
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
    //���� ����������� �������� ������
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() ||
    input.GetColorModel() != background.GetColorModel())
    {
        background=input;
        return true;
    }
    //���
    UBColor *bg=background.GetData();
    //������� ����
    UBColor *inp=input.GetData();

    //����� ��� ���������� ����
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
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
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

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABackgroundSimpleAdaptive::AFBgBuild(void)
{
    return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABackgroundSimpleAdaptive::AFBgReset(void)
{
    updateFGFlag->Fill(0);
    //UpdateFGFlag = 0;
    *Background=*Input;
    nCounterBG=1;
    IsBGReady = false;
    return true;
}

// ��������� ������ ����� �������
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

    //������ ����� ��� ������ ������
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
// ��� � ���������� �� �������� ������ ����� ����� � ������� ������
//------------------------------------------------------------------------
// ---------------------
// ������ �����
// ---------------------
// ---------------------
// ������������ � �����������
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
// �������� ����� ����� ����� �������
UBABackgroundDependDiff* UBABackgroundDependDiff::New(void)
{
    return new UBABackgroundDependDiff;
}

bool UBABackgroundDependDiff::BCalculateFirstBackground
(UBitmap &input, UBitmap &background)
{
    //���� ����������� �������� ������
    if(input.GetWidth() != background.GetWidth() ||
    input.GetHeight() != background.GetHeight() ||
    input.GetColorModel() != background.GetColorModel())
    {
        background=input;
        return true;
    }
    //���
    UBColor *bg=background.GetData();
    //������� ����
    UBColor *inp=input.GetData();

    //����� ��� ���������� ����
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
    //���� ����������� �������� ������
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
        //���
        UBColor *bg=background.GetData();
        //������� ����
        UBColor *inp=input.GetData();
        //������ ���� � �������� ����������� �����
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
    //���
    UBColor *bg=background.GetData();
    //������� ����
    UBColor *inp=input.GetData();
    //������ ���� � �������� ����������� �����
    UBColor *delta=diffImg.GetData();

    for(int j=0;j<background.GetByteLength();j++)
    {
        //����������� ����������� ���������� ����
        //�� ����� ���� ���� ��� 1-�����
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
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABackgroundDependDiff::AFBgDefault(void)
{
    //StateTempoDif = 242;
    nCounterBG=1;
    return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABackgroundDependDiff::AFBgBuild(void)
{
    return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABackgroundDependDiff::AFBgReset(void)
{
    *Background=*Input;
    nCounterBG=1;
    IsBGReady = false;
    return true;
}

// ��������� ������ ����� �������
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
        //������� ������������
        //��� �� �����������
        deltaImg->Fill(255);
    }


    //�������������� ���������  ���� ��� ���������� ���������� ��������
    if (nCounterBG < countFirstCleanBgFrame)
    {
        IsBGReady = false;
        BCalculateFirstBackground(*Input, *Background);
        nCounterBG++;
    }
    //������� �����, ����� ���������� ��������
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
