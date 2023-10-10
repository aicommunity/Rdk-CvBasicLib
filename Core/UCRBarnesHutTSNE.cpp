#ifndef RDK_UCRBarnesHutTSNE_CPP
#define RDK_UCRBarnesHutTSNE_CPP

#include "UCRBarnesHutTSNE.h"
#include <boost/filesystem.hpp>

#include "TSNE/tsne.h"

#include <iostream>
#include <fstream>

//Зададим дефолтные параметры тут тоже
const int DEFAULT_NO_DIMS = 2;
const int INITIAL_DIMENSIONS = 50;
const int DEFAULT_PERPLEXITY = 50;
const double DEFAULT_THETA = 0.5;
const int EMPTY_SEED = -1;
//const bool DEFAULT_USE_PCA = true;
const int DEFAULT_MAX_ITERATIONS = 1000;


namespace RDK {

// Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRBarnesHutTSNE::UCRBarnesHutTSNE(void):
    RetrainFlag("RetrainFlag", this),
    NumOutCoords("NumOutCoords",this),
    Perplexity("Perplexity",this),
    Theta("Theta",this),
    MaxIterations("MaxIterations", this),
    RandomSeed("RandomSeed", this),
    CalcActive("CalcActive", this),
    InputComponents("InputComponents",this),
    OutputComponents("OutputComponents",this)
{
    RetrainFlag = true;
    NumOutCoords = DEFAULT_NO_DIMS;
    Perplexity = DEFAULT_PERPLEXITY;
    Theta = DEFAULT_THETA;
    MaxIterations = DEFAULT_MAX_ITERATIONS;
    RandomSeed = EMPTY_SEED;

    TSNECalcInProcess = false;
    CalcProgress = 0.0f;

    rand_seed = -1;

    m_thread = NULL;
}

UCRBarnesHutTSNE::~UCRBarnesHutTSNE(void)
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
UCRBarnesHutTSNE* UCRBarnesHutTSNE::New(void)
{
 return new UCRBarnesHutTSNE;
}
// --------------------------


// --------------------------
// Скрытые методы управления счетом
// --------------------------


bool UCRBarnesHutTSNE::AReset(void)
{
    RetrainFlag = true;
    return true;
}


bool UCRBarnesHutTSNE::ACalculate(void)
{

    if(RetrainFlag.v == true)
    {
        if(!InputComponents.IsConnected())
        {
            LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("TSNE: [InputComponents] is not connected"));
            return true;
        }

        if(InputComponents->IsEmpty())
        {
            LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("TSNE: [InputComponents] is empty"));
            return true;
        }
    }

    //Расчет не активен
    if(!TSNECalcInProcess)
    {
        //Ничего нет или есть желание пересчитать
        if(OutputComponents->GetRows()==0 || RetrainFlag.v==true)
        {
            RunTSNECalculation();
        }
    }

    UpdateCalculationState();

    return true;
}

bool UCRBarnesHutTSNE::RunTSNECalculation()
{
    if(TSNECalcInProcess)
        return true;

    //Заполнить данные
    N = (*InputComponents).GetRows();
    D = (*InputComponents).GetCols();
    no_dims = NumOutCoords;
    max_iter = MaxIterations;

    perplexity = Perplexity;
    theta = Theta;
    rand_seed = RandomSeed;

    //Важно - МАССИВЫ СОЗДАЮТСЯ ЗДЕСЬ!

    landmarks = (int*) malloc(N * sizeof(int));
    if(landmarks == NULL) { LogMessageEx(RDK_EX_ERROR, __FUNCTION__, std::string("TSNE: Memory allocation failed!")); return false; }
    for(int n = 0; n < N; n++) landmarks[n] = n;

    Y = (double*) malloc(N * no_dims * sizeof(double));
    costs = (double*) calloc(N, sizeof(double));

    data = (double*) malloc(N * D * sizeof(double));

    std::ofstream ofs;
    ofs.open("nums.txt");
    ofs<<"N = "<<N<<" D = "<<D<<" no_dims = "<<no_dims<<" max_iter = "<<max_iter<<"\n";
    ofs.close();

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<D; j++)
        {
            data[i*D+j] = (*InputComponents)(i, j);
        }
    }

    if(Y == NULL || costs == NULL) { LogMessageEx(RDK_EX_ERROR, __FUNCTION__, std::string("TSNE: Memory allocation failed!")); return false; }

    //Обнулить счетчик и переменную
    TSNECalcInProcess = true;
    CalcProgress = 0.0;

    //Запустить поток
    m_thread = new std::thread(&UCRBarnesHutTSNE::TSNECalculationThread, this);
    //Вернуть норму
    return true;
}

void UCRBarnesHutTSNE::TSNECalculationThread()
{
    //Запустить расчет, передать счетчик состояния

    TSNE::run(data, N, D, Y, no_dims, perplexity, theta, rand_seed, false, max_iter, 250, 250);

    //Выставить флаг

    TSNECalcInProcess = false;
    RetrainFlag.v = false;
    CalcActive.v = false;

    (*OutputComponents).Resize(N, no_dims);

    std::ofstream ofs;
    ofs.open("test.txt");
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<no_dims; j++)
        {
            (*OutputComponents)(i, j) = Y[i*no_dims+j];
            ofs<<(*OutputComponents)(i, j)<<" ";
        }
        ofs<<"\n";
    }
    ofs.close();


    //Очистить данные
    //ВАЖНО - МАССИВЫ ОЧИЩАЮТСЯ ЗДЕСЬ!!
    free(data); data = NULL;
    free(Y); Y = NULL;
    free(costs); costs = NULL;
    free(landmarks); landmarks = NULL;
}

void UCRBarnesHutTSNE::UpdateCalculationState()
{
    CalcActive.v = TSNECalcInProcess;
}
}
#endif



