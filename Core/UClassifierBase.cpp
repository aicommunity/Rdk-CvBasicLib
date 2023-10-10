#ifndef RDK_UCLASSIFIERBASE_CPP
#define RDK_UCLASSIFIERBASE_CPP

#include "UClassifierBase.h"


namespace RDK {



// Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UClassifierBase::UClassifierBase(void):
    ConfidenceThreshold("ConfidenceThreshold", this),
    InputImage("InputImage",this),
    InputImages("InputImages",this),
    OutputClasses("OutputClasses",this),
    OutputConfidences("OutputConfidences", this),
    ClassificationTime("ClassificationTime",this),
    NumClasses("NumClasses",this,&UClassifierBase::SetNumClasses)
{

}

UClassifierBase::~UClassifierBase(void)
{

}
// --------------------------


// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------
bool UClassifierBase::SetNumClasses(const int &value)
{
    Ready=false;
    return true;
}
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
bool UClassifierBase::ACalculate(void)
{
    OutputClasses->Resize(0,1);
    OutputConfidences->Resize(0, NumClasses);
    if(InputImages.IsConnected() && InputImages->size()>0)
    {
        OutputClasses->Assign(int(InputImages->size()),1, CLASS_UNDEFINED);
        OutputConfidences->Assign(int(InputImages->size()), NumClasses,0.0);
        for(int i=0; i<InputImages->size(); i++)
        {
            ProcessedBmp = (*InputImages)[i];

            if(ProcessedBmp.GetData()==NULL)
            {
                LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("InputImages["+sntoa(i)+"] is NULL"));
                continue;
            }

            MDVector<double> output_confidences;
            int class_id;
            bool is_classified;
            bool classify_res=ClassifyBitmap(ProcessedBmp, output_confidences, ConfidenceThreshold, class_id, is_classified);

            if(classify_res)
            {
                for(int k=0; k<output_confidences.GetSize(); k++)
                {
                    (*OutputConfidences)(i, k) = output_confidences(k);
                }
                (*OutputClasses)[i] = (is_classified)?class_id:CLASS_LOWQUAL;
            }
        }
    }
    else
    {
        if(InputImage.IsConnected())
        {
            OutputClasses->Assign(1,1, CLASS_UNDEFINED);
            OutputConfidences->Assign(1, NumClasses,0.0);
            ProcessedBmp = *InputImage;

            if(ProcessedBmp.GetData()==NULL)
            {
                LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("InputImage is NULL"));
                return true;
            }

            MDVector<double> output_confidences;
            int class_id;
            bool is_classified;
            bool classify_res=ClassifyBitmap(ProcessedBmp, output_confidences, ConfidenceThreshold, class_id, is_classified);
            if(classify_res)
            {
                for(int k=0; k<output_confidences.GetSize(); k++)
                {
                    (*OutputConfidences)(0, k) = output_confidences(k);
                }
                (*OutputClasses)[0] = (is_classified)?class_id:CLASS_LOWQUAL;
            }
        }
    }

    return true;
}

}
#endif



