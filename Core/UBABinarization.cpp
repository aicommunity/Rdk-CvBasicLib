#ifndef UBABinarization_CPP
#define UBABinarization_CPP
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#include "UBABinarization.h"
#include <math.h>

namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBABinarization::UBABinarization(void)
 : Input("Input",this),
   Output("Output",this)
{
}

UBABinarization::~UBABinarization(void)
{
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABinarization::ADefault(void)
{
 return AFBgDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABinarization::ABuild(void)
{
 return AFBgBuild();
}

// ����� �������� ����� ��� ������ ��������
bool UBABinarization::AReset(void)
{
 return AFBgReset();
}

// ��������� ������ ����� �������
bool UBABinarization::ACalculate(void)
{
 return AFBgCalculate();
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABinarization::AFBgDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABinarization::AFBgBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABinarization::AFBgReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBABinarization::AFBgCalculate(void)
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
UBABinarizationSimple::UBABinarizationSimple(void)
 : Threshold("Threshold",this)
{

}

UBABinarizationSimple::~UBABinarizationSimple(void)
{

}
// ---------------------


// �������� ����� ����� ����� �������
UBABinarizationSimple* UBABinarizationSimple::New(void)
{
 return new UBABinarizationSimple;
}

bool UBABinarizationSimple::BCalculate(UBitmap &input, UBitmap &background)
{
 UBColor *bg=background.GetData();
 UBColor *in=input.GetData();

 switch(input.GetColorModel())
 {
 case ubmRGB24:
 {
  UBColor r=Threshold->rgb.r;
  UBColor g=Threshold->rgb.g;
  UBColor b=Threshold->rgb.b;
  for(int j=0;j<background.GetLength();j++)
  {
   unsigned pixel=(*in++ > r)?255:0;
   pixel+=(*in++ > g)?255:0;
   pixel+=(*in++ > b)?255:0;
   *bg++=static_cast<unsigned char>(pixel/3);
  }
 }
 break;

 case ubmY8:
 {
  UBColor y=Threshold->ycrcb.y;
  //int length=background.GetLength();
  for(int j=0;j<background.GetLength();j++)
  {
   *bg++=(*in++ > y)?255:0;
  }
 }
 break;
 default:
     break;
 }
 return true;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABinarizationSimple::AFBgDefault(void)
{
 Threshold=0x00808080;
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABinarizationSimple::AFBgBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABinarizationSimple::AFBgReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBABinarizationSimple::AFBgCalculate(void)
{
 Output->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY8);
 return BCalculate(*Input, *Output);
}
// --------------------------




//----------------------------------------------------------------------------
//������� ���������� ���� � ���������� ������� ������
//
//----------------------------------------------------------------------------

// ---------------------
// ������ �����
// ---------------------
// ---------------------
// ������������ � �����������
// ---------------------
UBABinarizationSimpleAdaptiveThreshold::UBABinarizationSimpleAdaptiveThreshold(void)
 : Threshold("Threshold",this),
   Background ("Background", this),
   KAlpha ("KAalpha", this),
   KGamma ("KGamma", this),
   startThreshold ("startThreshold", this),
   counterFG ("counterFG", this),
   stableBGflag("stableBGflag", this),
   modeTypes("modeTypes", this),
   counterBG("counterBG", this),
   unstableFlag("unstableFlag", this),
   Threshold2("Threshold2",this),
   output2("output2", this),
   maxDinamThreshold ("maxDinamThreshold", this),
   invThreshold("invThreshold",this),
   countFirstCleanBgFrame("countFirstCleanBgFrame", this),
   firstThTypes ("firstThTypes", this),
   minDinamThreshold ("minDinamThreshold", this)
{
    KAlpha = 0.8;
    KGamma = 10;
    startThreshold = 0;
    stableBGflag = 10;
    modeTypes=3;
    unstableFlag=10;
    maxDinamThreshold = 50;
    countFirstCleanBgFrame=50;
    nCounter=1;
    firstThTypes = 3;
    minDinamThreshold = 5;
}

UBABinarizationSimpleAdaptiveThreshold::~UBABinarizationSimpleAdaptiveThreshold(void)
{

}
// ---------------------
// �������� ����� ����� ����� �������
UBABinarizationSimpleAdaptiveThreshold* UBABinarizationSimpleAdaptiveThreshold::New(void)
{
 return new UBABinarizationSimpleAdaptiveThreshold;
}

bool UBABinarizationSimpleAdaptiveThreshold::BCalculate1
(UBitmap &Background, UBitmap &input, UBitmap &Threshold, UBitmap &output, UBitmap &counterFG)
{
    UBColor *bg=Background.GetData();
    UBColor *in=input.GetData();
    UBColor *th=Threshold.GetData();
    UBColor *out=output.GetData();

    UBColor *cFG=counterFG.GetData();

    switch(input.GetColorModel())
    {
        case ubmRGB24:
        {
            //���-�� ������, ���� ����������� �������
        }
        break;

        //���� ����������� �����-�����
        case ubmY8:
        {
            for(int j=0;j<Background.GetLength();j++)
            {
                if (abs(int(*in)-int(*bg)) >(*th))
                {
                    //�������� ���� �����
                    *out = 255;

                    *cFG+=1;
                    if (*cFG == stableBGflag)
                    {
                        if (*th<250)
                            *th+=10;
                    }
                }
                else
                {
                    double th_res(0.0);
                    //��� ������
                    //���������� �����
                    if((int(*in)-int(*bg))>0)
                        th_res=KAlpha*double(*th)+(1.0-KAlpha.v)*KGamma.v*double(*in-*bg);
                    else
                        th_res=KAlpha*double(*th)+(1.0-KAlpha.v)*KGamma.v*double(*bg-*in);

                    if(th_res<0)
                        th_res=0;
                    if(th_res>255)
                        th_res=255;

                    *cFG=0;
                    *th= static_cast<unsigned char>(th_res);
                    *out=0;

                }
                th++;
                bg++;
                in++;
                out++;

                cFG++;
            }
        }
        break;
        default:
            break;
    }
    return true;
}

bool UBABinarizationSimpleAdaptiveThreshold::BCalculate0
(UBitmap &Background, UBitmap &input, UBitmap &output)
{
    UBColor *bg=Background.GetData();
    UBColor *in=input.GetData();
    UBColor *out=output.GetData();

    switch(input.GetColorModel())
    {
        case ubmRGB24:
        {
            //���-�� ������, ���� ����������� �������
        }
        break;

        //���� ����������� �����-�����
        case ubmY8:
        {
            for(int j=0;j<Background.GetLength();j++)
            {
                if (abs(int(*in)-int(*bg)) >startThreshold)
                {
                    //�������� ���� �����
                    *out = 255;

                }
                else
                {
                    *out=0;

                }
                bg++;
                in++;
                out++;

            }
        }
        break;
    default:
        break;
    }
    return true;
}

bool UBABinarizationSimpleAdaptiveThreshold::BCalculate2
(UBitmap &Background, UBitmap &input, UBitmap &Threshold, UBitmap &output, UBitmap &counterFG,UBitmap &counterBG)
{
    UBColor *bg=Background.GetData();
    UBColor *in=input.GetData();
    UBColor *th=Threshold.GetData();
    UBColor *out=output.GetData();
    UBColor *cFG=counterFG.GetData();
    UBColor *cBG=counterBG.GetData();

    switch(input.GetColorModel())
    {
        case ubmRGB24:
        {
            //���-�� ������, ���� ����������� �������
        }
        break;

        //���� ����������� �����-�����
        case ubmY8:
        {
            for(int j=0;j<Background.GetLength();j++)
            {
                if (abs(int(*in)-int(*bg)) >(*th))
                {
                    //�������� ���� �����
                    *out = 255;
                    *cFG+=1;
                    if (*cFG == stableBGflag)
                    {
                        if (*th<250)
                            *th+=10;
                    }
                    *cBG=0;
                }
                else
                {
                    double th_res(0.0);
                    //��� ������
                    //���������� �����
                    if((int(*in)-int(*bg))>0)
                        th_res=KAlpha*double(*th)+(1.0-KAlpha.v)*KGamma.v*double(*in-*bg);
                    else
                        th_res=KAlpha*double(*th)+(1.0-KAlpha.v)*KGamma.v*double(*bg-*in);

                    if(th_res<0)
                        th_res=0;
                    if(th_res>255)
                        th_res=255;

                    *cBG+=1;
                    if (*cBG == unstableFlag)
                    {
                        if (*th>6)
                            *th-=5;
                    }

                    *cFG=0;
                    *th= static_cast<unsigned char>(th_res);
                    *out=0;
                }
                th++;
                bg++;
                in++;
                out++;
                cFG++;
            }
        }
        break;
    default:
        break;
    }
    return true;
}

bool UBABinarizationSimpleAdaptiveThreshold::BCalculate3
(UBitmap &Background, UBitmap &input, UBitmap &Threshold, UBitmap &output,
 UBitmap &counterFG, UBitmap &counterBG)
{
    UBColor *bg=Background.GetData();
    UBColor *in=input.GetData();
    UBColor *th=Threshold.GetData();
    UBColor *out=output.GetData();
    UBColor *cFG=counterFG.GetData();
    UBColor *cBG=counterBG.GetData();

    //int cmaxcount=0;

    //���������� ���������� �� ��������
    for(unsigned long int j=0;j<15;j++)
        ThresholdStats[j]=0;

    switch(input.GetColorModel())
    {
        case ubmRGB24:
        {
            //���-�� ������, ���� ����������� �������
        }
        break;

        //���� ����������� �����-�����
        case ubmY8:
        {
            for(int j=0;j<Background.GetLength();j++)
            {
                if (abs(int(*in)-int(*bg)) >(*th))
                {
                    //�������� ���� �����
                    *out = 255;
                    *cFG+=1;
                    if (*cFG == stableBGflag)
                    {
                        if (*th<250)
                            *th+=10;
                    }
                    *cBG=0;

                    ThresholdStats[14]++;
                    //cmaxcount++;
                }
                else
                {
                    double th_res(0.0);
                    //��� ������
                    //���������� �����
                    //���� ��� ������� ����� - ����� ��������� �����
                    *cBG+=1;
                    if (*cBG == unstableFlag)
                    {
                        if (*th>6)
                            *th-=4;
                        if (*th >= 2)
                            *th-=1;
                        //*cBG=0;
                    }
                    //else
                    //{

                        if((int(*in)-int(*bg))>0)
                            th_res=KAlpha*double(*th)+(1.0-KAlpha.v)*KGamma.v*double(*in-*bg);
                        else
                            th_res=KAlpha*double(*th)+(1.0-KAlpha.v)*KGamma.v*double(*bg-*in);
                    //}
                    //���� ���������� �� ������� � ��������� �������� ���� � �������� �����
                    //�� 1 �� 15
                    //��������� ��������� ��������
                    if (abs(int(*in)-int(*bg))<14)
                    {
                        ThresholdStats[static_cast<unsigned long int>(abs(int(*in)-int(*bg)))]++;
                        //cmaxcount++;
                    }

                    else
                    {
                        ThresholdStats[14]++;
                        //cmaxcount++;
                    }


                    if(th_res<0)
                        th_res=0;
                    if(th_res>255)
                        th_res=255;



                    *cFG=0;
                    *th = static_cast<unsigned char>(th_res);
                    if (th_res >= maxDinamThreshold)
                        *th = static_cast<unsigned char>(maxDinamThreshold);
                    else
                    {
                        if ( (th_res <= minDinamThreshold))
                            *th = static_cast<unsigned char>(minDinamThreshold);
                    }
                    *out=0;
                }
                th++;
                bg++;
                in++;
                out++;
                cFG++;
                cBG++;
            }
            //��������� ��������� �� ���������
            for(unsigned long long j=0;j<15;j++)
            {
                //ThresholdStats[0]+=ThresholdStats[j];
                ThresholdStats[j]/=Background.GetLength();
                ThresholdStats[j]*=100;
            }
        }
        break;
    default:
        break;
    }
    return true;
}

bool UBABinarizationSimpleAdaptiveThreshold::BCalculateFirstThreshold1
(UBitmap &Background, UBitmap &input, UBitmap &Threshold, UBitmap &output)
{
    UBColor *bg=Background.GetData();
    UBColor *in=input.GetData();
    UBColor *th=Threshold.GetData();
    UBColor *out=output.GetData();

    double d, c, tmpc, tmpd;

    if (nCounter<2)
        d=c=0;
    else
    {
        d=static_cast<double>(1./static_cast<double>(nCounter-1));
        c=static_cast<double>(nCounter-2)*d;
    }
    //newt = (unsigned int)(c*thr+d*pow);
    for(int j=0;j<Background.GetLength();j++)
    {
        if (abs(int(*in)-int(*bg)) >(*th))
        {
            //�������� ���� �����
            *out = 255;
        }
        else
        {
            *out = 0;
        }
        tmpc = c*(*th);
        tmpd = d*(abs(*bg-*in));

        //*th = 10;
        if (tmpc+tmpd > maxDinamThreshold)
        {
            *th = maxDinamThreshold;
        }
        else
        {
            if (tmpc+tmpd < minDinamThreshold)
            {
                *th = minDinamThreshold;
            }
            else
            {
                *th = static_cast<unsigned char>(tmpc+tmpd);
            }
        }
        th++;
        bg++;
        in++;
        out++;
    }
    return true;
}

bool UBABinarizationSimpleAdaptiveThreshold::BCalculateFirstThreshold2
(UBitmap &Background, UBitmap &input, UBitmap &Threshold, UBitmap &output)
{
    UBColor *bg=Background.GetData();
    UBColor *in=input.GetData();
    UBColor *th=Threshold.GetData();
    UBColor *out=output.GetData();

    //newt = (unsigned int)(c*thr+d*pow);
    for(int j=0;j<Background.GetLength();j++)
    {
        if (abs(int(*in)-int(*bg)) >(*th))
        {
            //�������� ���� �����
            *out = 255;
            *th = static_cast<unsigned char>(abs(int(*in)-int(*bg)));
        }
        else
        {
            *out = 0;
        }
        if (*th > maxDinamThreshold)
        {
            *th = maxDinamThreshold;
        }
        th++;
        bg++;
        in++;
        out++;
    }
    return true;
}

// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABinarizationSimpleAdaptiveThreshold::AFBgDefault(void)
{
    KAlpha = 0.8;
    KGamma = 10;
    startThreshold=0;
    modeTypes = 3;
    maxDinamThreshold = 50;
    return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABinarizationSimpleAdaptiveThreshold::AFBgBuild(void)
{
    return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABinarizationSimpleAdaptiveThreshold::AFBgReset(void)
{
    //����������� �������������� ���������� ����
    if (firstThTypes == 1)
    {
      countFirstCleanBgFrame = 0;
      startThreshold.SetData(maxDinamThreshold);
    }
    //����������� ��������� �������� ������
    Threshold->Fill(static_cast<unsigned char>(startThreshold.GetData()));
    //invThreshold->Fill(255-startThreshold.GetData());
    nCounter=1;
    return true;
}

// ��������� ������ ����� �������
bool UBABinarizationSimpleAdaptiveThreshold::AFBgCalculate(void)
{
    //����������� �������������� ���������� ����
    if (firstThTypes == 1)
    {
      countFirstCleanBgFrame = 0;
      startThreshold.SetData(maxDinamThreshold);
    }

    if(nCounter<countFirstCleanBgFrame)
    {
        startThreshold.SetData(0);
    }


    if((Threshold->GetWidth()!=Input->GetWidth()) ||
    (Threshold->GetHeight()!=Input->GetHeight())||
    Threshold->GetColorModel()!=Input->GetColorModel())
    {
        if (firstThTypes == 1)
        {
          countFirstCleanBgFrame = 0;
          startThreshold.SetData(maxDinamThreshold);
        }
        Threshold->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY8);
        Threshold->Fill(static_cast<unsigned char>(startThreshold.GetData()));
        invThreshold->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY8);
        invThreshold->Fill(255-static_cast<unsigned char>(startThreshold.GetData()));
    }
    if((counterFG->GetWidth()!=Input->GetWidth()) ||
    (counterFG->GetHeight()!=Input->GetHeight())||
    counterFG->GetColorModel()!=Input->GetColorModel())
    {
        counterFG->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY8);
        counterFG->Fill(0);
    }
    if((counterBG->GetWidth()!=Input->GetWidth()) ||
    (counterBG->GetHeight()!=Input->GetHeight())||
    counterBG->GetColorModel()!=Input->GetColorModel())
    {
        counterBG->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY8);
        counterBG->Fill(0);
    }
    if((Output->GetWidth()!=Input->GetWidth()) ||
    (Output->GetHeight()!=Input->GetHeight())||
    Output->GetColorModel()!=Input->GetColorModel())
    {
        Output->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY8);
    }
    if((Threshold2->GetWidth()!=Threshold->GetWidth()) ||
    (Threshold2->GetHeight()!=Threshold->GetHeight())||
    Threshold2->GetColorModel()!=Threshold->GetColorModel())
    {
        Threshold2->SetRes(Threshold->GetWidth(), Threshold->GetHeight(), ubmY8);
    }
    if (ThresholdStats.size()!=15)
        ThresholdStats.resize(15);

    if(nCounter<countFirstCleanBgFrame)
    {
        //�������������������� ���������� ������ ������ countFirstCleanBgFrame ������
        if(firstThTypes == 2)
            BCalculateFirstThreshold1(*Background, *Input, *Threshold, *Output);
        //������������ � ����� � ������ countFirstCleanBgFrame ������
        if(firstThTypes == 3)
            BCalculateFirstThreshold2(*Background, *Input, *Threshold, *Output);
        nCounter++;
    }
    else
    {
        if (modeTypes==0)
        {
            BCalculate0(*Background, *Input, *Output);
        }
        if (modeTypes==1)
        {
            BCalculate1(*Background, *Input, *Threshold, *Output, *counterFG);
        }
        if (modeTypes==2)
        {
            BCalculate2(*Background, *Input, *Threshold, *Output, *counterFG, *counterBG);
        }
        if (modeTypes==3)
        {
            BCalculate3(*Background, *Input, *Threshold,
                        *Output, *counterFG, *counterBG);
        }
    }
    unsigned* th2 = reinterpret_cast<unsigned*>(Threshold2->GetData());
    UBColor* th1 = Threshold->GetData();
    for(int j=0;j<(*output2).GetLength();j++)
    {
        //*(output2+j)=(int)((*(Background+j)->GetData())<<25);
        *th2 = *th1;
        *th2*=*th2;
        *th2<<=16;
        th2++;
        th1++;
    }

    Threshold->Inverse(&*invThreshold);

    if(nCounter>=countFirstCleanBgFrame)
    {
        //����� ����� � ���������� ���������������� ������
        invThreshold->SetColorModel(ubmRGB24,true);
        UGraphics graph(invThreshold);

        graph.SetFont(GetDefaultFont());
        graph.SetFont(GetFont("Tahoma",16));
        graph.SetPenColor(0x000000FF);
        std::string text;
        int y=0;
        text=string("<1: ")+sntoa(ThresholdStats[0]);
        graph.Text(text,0,y);

        y+=20;
        for(unsigned long long i=1;i<14;i++)
        {
             text=sntoa(i)+string(": ")+sntoa(ThresholdStats[i]);
             graph.Text(text,0,y);
             y+=20;
        }
        text=string(">14: ")+sntoa(ThresholdStats[14]);
        graph.Text(text,0,y);
    }





    return true;
}
// --------------------------








//���






// ---------------------
// ������ �����
// ---------------------
// ---------------------
// ������������ � �����������
// ---------------------
UBABinarizationOtsu::UBABinarizationOtsu(void)
    : minThreshold ("minThreshold", this),
      Mask ("Mask", this)
{
    minThreshold = 30;
}

UBABinarizationOtsu::~UBABinarizationOtsu(void)
{

}
// ---------------------


// �������� ����� ����� ����� �������
UBABinarizationOtsu* UBABinarizationOtsu::New(void)
{
 return new UBABinarizationOtsu;
}

bool UBABinarizationOtsu::BCalculate(UBitmap &input, UBitmap &output, UBitmap &mask)
{
    UBColor *out=output.GetData();
    UBColor *in=input.GetData();
    UBColor *ms=mask.GetData();
    int size = input.GetLength();

    if (input.GetColorModel() == ubmY8)
    {
        /**out = 255-*in;
        out++;
        in++;*/


        // ��������� ����������� � ������������ ������� ���� ��������
        //�������� ���� ��-�������� ������
        int min = *in;
        int max = *in;

        for (int i = 1; i < size; i++)
        {
            in++;
            int value = *in;

            if (value < min)
                min = value;

            if (value > max)
                max = value;

            if  (*ms == 0)
            {
                *in = 0;
                //*out = 0;
            }
            ms++;
        }

        in=input.GetData();
        out=output.GetData();
        ms=mask.GetData();

        // ����������� ����� ���������� ����� � ������ ���������� min � max,
        // ������� ��� ������ ��������� ����������� �������� 256 �����
        int histSize = max - min + 1;
        int* hist = new int[static_cast<unsigned long int>(histSize)];

        // �������� ����������� ������
        for (int t = 0; t < histSize; t++)
        hist[t] = 0;

        // � �������� ������ �����
        for (int i = 0; i < size; i++)
        {
            hist[*in - min]++;
            in++;
        }
        in=input.GetData();

        // ������ ��� ��������������� �����:
        int m = 0; // m - ����� ����� ���� �����, ����������� �� ��������� �� ��������
        int n = 0; // n - ����� ����� ���� �����
        for (int t = 0; t <= max - min; t++)
        {
            m += t * hist[t];
            n += hist[t];
        }

        float maxSigma = -1; // ������������ �������� ������������ ���������
        int threshold = 0; // �����, ��������������� maxSigma

        int alpha1 = 0; // ����� ����� ���� ����� ��� ������ 1
        int beta1 = 0; // ����� ����� ���� ����� ��� ������ 1, ����������� �� ��������� �� ��������

        // ���������� alpha2 �� �����, �.�. ��� ����� m - alpha1
        // ���������� beta2 �� �����, �.�. ��� ����� n - alpha1

        // t ����������� �� ���� ��������� ��������� ������
        for (int t = 0; t < max - min; t++)
        {
            alpha1 += t * hist[t];
            beta1 += hist[t];

            // ������� ����������� ������ 1.
            float w1 = static_cast<float>(beta1) / n;
            // �������� ����������, ��� w2 ���� �� �����, �.�. ��� ����� 1 - w1

            // a = a1 - a2, ��� a1, a2 - ������� �������������� ��� ������� 1 � 2
            float a = static_cast<float>(alpha1) / beta1 - static_cast<float>(m - alpha1) / (n - beta1);

            // �������, ������� sigma
            float sigma = w1 * (1 - w1) * a * a;

            // ���� sigma ������ ������� ������������, �� ��������� maxSigma � �����
            if (sigma > maxSigma)
            {
                maxSigma = sigma;
                threshold = t;
            }
        }

        // �� �������, ��� ����� ������������ �� min, � �� �� ����
        threshold += min;
        if (threshold < minThreshold)
            threshold = minThreshold;

        for(int j=0;j<input.GetLength();j++)
            {
            if (*in < threshold)
                *out = 0;
            else
                *out = 255;
            in++;
            out++;
        }

    }
    else
    {
     ;
    }
    return true;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABinarizationOtsu::AFBgDefault(void)
{
    minThreshold = 30;
    return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABinarizationOtsu::AFBgBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABinarizationOtsu::AFBgReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBABinarizationOtsu::AFBgCalculate(void)
{
 Output->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY8);
 if((Mask->GetWidth()!=Input->GetWidth()) ||
 (Mask->GetHeight()!=Input->GetHeight())||
 Mask->GetColorModel()!=Input->GetColorModel())
 {
     Mask->SetRes(Input->GetWidth(), Input->GetHeight(), ubmY8);
     Mask->Fill(255);
 }

 return BCalculate(*Input, *Output, *Mask);
}
// --------------------------

}
//---------------------------------------------------------------------------

#endif
