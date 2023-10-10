#ifndef RDK_UCRPrincipalComponentAnalysis_CPP
#define RDK_UCRPrincipalComponentAnalysis_CPP

#include "UCRPrincipalComponentAnalysis.h"
#include <boost/filesystem.hpp>

#include "PCA/PCA.h"

namespace RDK {



// Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRPrincipalComponentAnalysis::UCRPrincipalComponentAnalysis(void):
    RetrainFlag("RetrainFlag", this),
    OutComponents("OutComponents",this),
    TrainingData("TrainingData",this),
    EncodingData("EncodingData",this),
    PCAResult("PCAResult", this),
    PCA_X("PCA_X",this)
{
    RetrainFlag = true;
    OutComponents=1;
    /*OverwriteSaveDirectory = false;
    CalculateFlag = false;
    (*ObjectsName).insert(pair<int, std::string>(-5,"mock"));*/
}

UCRPrincipalComponentAnalysis::~UCRPrincipalComponentAnalysis(void)
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
UCRPrincipalComponentAnalysis* UCRPrincipalComponentAnalysis::New(void)
{
 return new UCRPrincipalComponentAnalysis;
}
// --------------------------


// --------------------------
// Скрытые методы управления счетом
// --------------------------


bool UCRPrincipalComponentAnalysis::AReset(void)
{
    RetrainFlag = true;
    return true;
}


bool UCRPrincipalComponentAnalysis::ACalculate(void)
{

    if(RetrainFlag.v == true)
    {
        if(!TrainingData.IsConnected())
        {
            LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("PCA: [TrainingData] is not connected"));
            return true;
        }

        if(TrainingData->IsEmpty())
        {
            LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("PCA: [TrainingData] is empty"));
            return true;
        }

        //TODO: Check this is right
        if(!TrainPCA())
            return true;
    }

    if(!EncodingData.IsConnected())
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("PCA: [EncodingData] is not connected"));
        return true;
    }

    if(EncodingData->IsEmpty())
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("PCA: [EncodingData] is empty"));
        return true;
    }

    return ApplyPCA();
}

bool UCRPrincipalComponentAnalysis::TrainPCA(void)
{
    //Обучить PCA
    //Подготовить параметры
    int N = TrainingData->GetRows();
    int M = TrainingData->GetCols();

    double **data = new double*[N];
    for(int i=0; i<N; i++)
    {
        data[i] = new double[M];
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            data[i][j] = (*TrainingData)(i, j);
        }
    }

    //Применить
    double **eigenvector = PCA(data, M, N, true);

    //Записать результат
    PCA_X->Resize(M, M+1);
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<(M+1); j++)
        {
            (*PCA_X)(i, j) = eigenvector[i][j];
        }
    }

    RetrainFlag.v = false;

    //Очистка
    for(int i=0; i<N; i++)
    {
        delete[] data[i];
    }
    delete[] data;

    for(int i=0;i<M;++i)
        delete [] eigenvector[i];
    delete [] eigenvector;

    return true;
}
bool UCRPrincipalComponentAnalysis::ApplyPCA(void)
{
    //Подготовить данные
    int M = PCA_X->GetRows();

    double **eigenvector = new double*[M];
    for(int i=0; i<M; i++)
        eigenvector[i] = new double[M+1];

    for(int i=0; i<M; i++)
    {
        for(int j=0; j<(M+1); j++)
        {
            eigenvector[i][j] = (*PCA_X)(i, j);
        }
    }

    double *data = new double[M];
    for(int i=0; i<M; i++)
    {
        data[i] = (*EncodingData)(0, i);
    }

    //Расчет
    int nc = OutComponents.v;
    if(nc<=0 || nc>M)
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("PCA: OutComponents is <=0 or >M"));
        return false;
    }

    PCAResult->Resize(1, nc);
    for(int i=0; i<nc; i++)
    {
        (*PCAResult)(0, i) = PCA_TransformOne(data, eigenvector, i, M);
    }

    //Очистка
    for(int i=0; i<M; i++)
    {
        delete[] eigenvector[i];
    }
    delete[] eigenvector;
    delete[] data;

    return true;
}

}
#endif



