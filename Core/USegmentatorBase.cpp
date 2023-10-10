#ifndef RDK_USEGMENTATORBASE_CPP
#define RDK_USEGMENTATORBASE_CPP

#include "USegmentatorBase.h"


#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {



// Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
USegmentatorBase::USegmentatorBase(void):
    InputImage("InputImage",this),
    OutputImage("OutputImage",this),
    ClassColors("ClassColors",this)
{

}

USegmentatorBase::~USegmentatorBase(void)
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
bool USegmentatorBase::ACalculate(void)
{
    if(!InputImage.IsConnected())
        return true;

    ProcessedBmp=*InputImage;

    if(ProcessedBmp.GetData()==NULL)
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("InputImage is NULL"));
        return true;
    }

    UBitmap &mask = (*OutputImage);


    if(!Inference(ProcessedBmp, mask))
    {

    }


    return true;
}

}
#endif



