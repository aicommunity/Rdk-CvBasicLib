#ifndef RDK_UDETECTORBASE_CPP
#define RDK_UDETECTORBASE_CPP

#include "UDetectorBase.h"


#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {



// Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UDetectorBase::UDetectorBase(void):
    ConfidenceThreshold("ConfidenceThreshold", this),
    NMSthreshold("NMSthreshold",this),
    UseDebugImage("UseDebugImage",this),
    InputImage("InputImage",this),
    //UseRelativeCoords("UseRelativeCoords",this),
    DebugImage("DebugImage",this),
    OutputObjects("OutputObjects",this),
    OutputRects("OutputRects",this),
    OutputClasses("OutputClasses",this),
    OutputReliability("OutputReliability",this)
{

}

UDetectorBase::~UDetectorBase(void)
{

}
// --------------------------


// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------

// ---------------------
// Методы управления переменными состояния
// ---------------------
// ---------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса

// --------------------------


// --------------------------
// Скрытые методы управления счетом
// --------------------------
bool UDetectorBase::ACalculate(void)
{
    if(!InputImage.IsConnected())
        return true;

    ProcessedBmp = *InputImage;

    if(ProcessedBmp.GetData()==NULL)
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("InputImage is NULL"));
        return true;
    }

    if(!Detect(ProcessedBmp, *OutputRects, *OutputClasses, *OutputReliability))
        return true;

    OutputObjects->Resize(OutputRects->GetRows(), 6);
    for(int i=0;i<OutputRects->GetRows();i++)
    {
        bool rc = ((*OutputRects)(i,0)<=1)&&((*OutputRects)(i,1)<=1)&&((*OutputRects)(i,2)<=1)&&((*OutputRects)(i,3)<=1);
        double wm = (rc)?(InputImage->GetWidth()):(1);
        double hm = (rc)?(InputImage->GetHeight()):(1);

        (*OutputObjects)(i,0) = (int)((*OutputRects)(i,0)*wm);
        (*OutputObjects)(i,1) = (int)((*OutputRects)(i,1)*hm);
        (*OutputObjects)(i,2) = (int)((*OutputRects)(i,2)*wm);
        (*OutputObjects)(i,3) = (int)((*OutputRects)(i,3)*hm);
        (*OutputObjects)(i,4) = (*OutputReliability)(i,0);
        (*OutputObjects)(i,5) = (*OutputClasses)(i,0);
    }

    if(UseDebugImage)
    {
        DebugImage->SetColorModel(ubmRGB24,false);
        InputImage->ConvertTo(*DebugImage);

        Graph.SetCanvas(&DebugImage.v);

        UAFont *class_font=GetFont("Tahoma",20);

        for(int i=0; i<OutputRects->GetRows(); i++)
        {
            int xmin, ymin, xmax, ymax;

            xmin = (int)((*OutputObjects)(i,0));
            ymin = (int)((*OutputObjects)(i,1));
            xmax = (int)((*OutputObjects)(i,2));
            ymax = (int)((*OutputObjects)(i,3));

            double conf = (*OutputReliability)(i,0);
            int cls = (*OutputClasses)(i,0);

            Graph.SetPenColor(0x00FF00);
            Graph.SetPenWidth(3);
            Graph.Rect(xmin, ymin, xmax, ymax);

            std::stringstream ss;
            ss<<cls<<"["<<conf<<"]";

            if(class_font)
            {
                Graph.SetFont(class_font);
                Graph.Text(ss.str(),xmin, ymax+3);
            }
        }
    }

    return true;

}

}


#endif



