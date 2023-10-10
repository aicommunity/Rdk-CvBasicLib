// ===========================================================
// Version:        3.0.4
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2002.
E-mail:        alexab@ailab.ru
url:        http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UCRFUSION_CPP
#define UCRFUSION_CPP

#include "UCRFusion.h"
#include <algorithm>
#include <fstream>
//#include "CRFeatureSelectorCorrelation.h"


namespace RDK {

using namespace std;

// Функция расчета факториала
unsigned int fact(unsigned int n)
{
 unsigned int res=1;

 for(unsigned int i=2;i<=n;i++)
  res*=i;

 return res;
}

// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRFusion::UCRFusion(void)
//: UCRClassifier(name),
 : FusionMode("FusionMode",this,&UCRFusion::SetFusionMode),
  NumAttempts("NumAttempts",this),
  AccumulateMode("AccumulateMode",this),
  PreResultsWeigths("PreResultsWeigths",this)
{
 CurrentAttempt=-1;
}

UCRFusion::~UCRFusion(void)
{
}
// --------------------------

// -----------------------------
// Методы управления общедоступными свойствами
// -----------------------------
bool UCRFusion::SetFusionMode(const int &value)
{
// if(value == 0 || value == 1)
//  return true;
 return true;
}
// -----------------------------

// -----------------------------
// Методы управления параметрами
// -----------------------------
// -----------------------------

// -----------------------------
// Методы доступа к данным модели
// -----------------------------
// Текущее значение накоплений
int UCRFusion::GetCurrentAttempt(void) const
{
 return CurrentAttempt;
}
// -----------------------------

// ------------------------
// Методы счета
// ------------------------
// Загружает настройки из файла
bool UCRFusion::AFileLoad(fstream &file)
{
 return true;
}

// Сохраняет настройки в файл
bool UCRFusion::AFileSave(fstream &file)
{
 return true;
}
// ------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UCRFusion* UCRFusion::New(void)
{
 return new UCRFusion;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UCRFusion::ACRDefault(void)
{
 SetOutputDataSize(0,MMatrixSize(1,2));
 SetNumInputs(100);

 vector<double> minrate,maxrate;
 minrate.assign(GetOutputDataSize(0)[1],0);
 maxrate.assign(GetOutputDataSize(0)[1],100);

 MinQualityRate=minrate;
 MaxQualityRate=maxrate;

 AutoQualityRate=true;

 MaxInputValue=100;
 MinInputValue=0;
 MinOutputValue=0;
 MaxOutputValue=100;

 FusionMode=2;
 NumAttempts=10;
 AccumulateMode=3;

 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UCRFusion::ACRBuild(void)
{
 return true;
}


// Сброс процесса счета.
bool UCRFusion::ACRReset(void)
{
 AccumOutput.resize(0);
 CurrentAttempt=-1;

 return true;
}

bool UCRFusion::ACRCalculate(void)
{
 switch(FusionMode)
 {
 case 0:
  if(!AverageQualityCalculate())
   return false;
 break;

 case 1:
  if(!PairCalculate())
   return false;
 break;

 case 2:
  if(!AverageInputCalculate())
   return false;
 break;

 case 3:
  if(!RecognitionCounterCalculate())
   return false;
 break;

 case 4:
  if(!SumInputCalculate())
   return false;
 break;

 case 5:
  if(!InputRecognitionCounterCalculate())
   return false;
 break;

 case 6:
  if(!SumInputRecognitionCounterCalculate())
   return false;
 break;

 default:
  return false;
 }

 if(NumAttempts == 1)
  return true;

 int size=GetOutputDataSize(0)[1];

 bool key=false;
 for(int j=0;j<size;j++)
  if(POutputData[0].Double[j])
   key=true;

 if(key)
 {
  AccumOutput.push_back(POutputData[0]);
  ++CurrentAttempt;
  if(AccumOutput.size()>static_cast<size_t>(NumAttempts) && NumAttempts != 0)
  {
   AccumOutput.erase(AccumOutput.begin());
   --CurrentAttempt;
  }
 }

 int maxindex;
 double maxresult;
 vector<int> maxcounter;

 for(int j=0;j<size;j++)
  POutputData[0].Double[j]=0;

 int accumsize=int(AccumOutput.size());
 switch(AccumulateMode)
 {
 case 1:
   for(size_t i=0;i<AccumOutput.size();i++)
   {
    for(int j=0;j<size;j++)
     POutputData[0].Double[j]+=AccumOutput[i].Double[j];
   }

   if(accumsize)
    for(int j=0;j<size;j++)
     POutputData[0].Double[j]/=accumsize;
 break;

 case 2:
  for(size_t i=0;i<AccumOutput.size();i++)
  {
   maxindex=-1;
   maxresult=0;
   maxcounter.assign(size,0);
   for(int j=0;j<size;j++)
    if(AccumOutput[i].Double[j]>maxresult)
    {
     maxindex=j;
     maxresult=AccumOutput[i].Double[j];
    }

   if(maxindex>=0 && maxresult>0)
   {
    POutputData[0].Double[maxindex]+=maxresult;
    ++maxcounter[maxindex];
   }
  }

  for(int j=0;j<size;j++)
   if(maxcounter[j])
    POutputData[0].Double[j]/=maxcounter[j];
 break;

 case 3:
  for(size_t i=0;i<AccumOutput.size();i++)
  {
   maxindex=-1;
   maxresult=0;
   maxcounter.assign(size,0);
   for(int j=0;j<size;j++)
    if(AccumOutput[i].Double[j]>maxresult)
    {
     maxindex=j;
     maxresult=AccumOutput[i].Double[j];
    }

   if(maxindex>=0 && maxresult>0)
   {
    POutputData[0].Double[maxindex]+=1;
    ++maxcounter[maxindex];
   }
  }

/*  for(size_t j=0;j<size;j++)
   if(maxcounter[j])
    POutputData[0].Double[j]/=maxcounter[j];
    */
 break;
 }


 return true;
}
// --------------------------


// --------------------------
// Скрытые методы обучения сети
// --------------------------
// Сброс настроек обучение в исходное состояние
void UCRFusion::AResetTraining(void)
{
}

// Однократное обучение на заданном примере
double UCRFusion::ATrain(size_t exp_class)
{
 double E=0;

 return E;
}
// --------------------------


// ------------------------
// Скрытые методы счета
// ------------------------
// Вычисление результата как среднего по показателю качества
bool UCRFusion::AverageQualityCalculate(void)
{
 vector<UCRClassifier*> classifiers;

 for(int i=0;i<NumInputs;i++)
 {
  if(dynamic_cast<UCRClassifier*>(GetCItem(i).Item))
   classifiers.push_back(static_cast<UCRClassifier*>(GetCItem(i).Item));
 }

 if(classifiers.size()==0)
  return true;

 int minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];

 for(size_t i=1;i<classifiers.size();i++)
 {
  if(minoutputsize<classifiers[0]->GetOutputDataSize(0)[1])
   minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];
 }

 // Вектор числа попаданий на определенный класс
 vector<double> classcounter;

 // Вектор суммарного показателя качества
 vector<double> classquality;

 classcounter.assign(minoutputsize,0);
 classquality.assign(minoutputsize,0);

 for(size_t i=0;i<classifiers.size();i++)
 {
  if(classifiers[i]->QualityRate->second >= int(minoutputsize) ||
     !classifiers[i]->GetActivity())
   continue;
  classcounter[classifiers[i]->QualityRate->second]+=1;

  classquality[classifiers[i]->QualityRate->second]+=classifiers[i]->QualityRate->first;
 }

 for(size_t i=0;i<classquality.size();i++)
  if(classcounter[i])
   classquality[i]/=classcounter[i];

double maxcounter=0;

 for(size_t i=0;i<classcounter.size();i++)
  if(maxcounter<classcounter[i])
  {
   maxcounter=classcounter[i];
  }

 SetOutputDataSize(0,MMatrixSize(1,minoutputsize));
 for(size_t i=0;i<classcounter.size();i++)
  POutputData[0].Double[i]=classquality[i];

 return true;
}

// Вычисление результата как среднего по входам
bool UCRFusion::AverageInputCalculate(void)
{
 vector<UCRClassifier*> classifiers;

 for(int i=0;i<NumInputs;i++)
 {
  if(dynamic_cast<UCRClassifier*>(GetCItem(i).Item))
   classifiers.push_back(static_cast<UCRClassifier*>(GetCItem(i).Item));
 }

 if(classifiers.size()==0)
  return true;

 size_t minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];

 for(size_t i=1;i<classifiers.size();i++)
 {
  if(int(minoutputsize)<classifiers[0]->GetOutputDataSize(0)[1])
   minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];
 }

 // Вектор числа попаданий на определенный класс
 vector<double> classcounter;

 // Вектор суммарного показателя качества
 vector<double> classquality;

 classcounter.assign(minoutputsize,0);
 classquality.assign(minoutputsize,0);

 for(size_t i=0;i<classifiers.size();i++)
 {
  for(size_t j=0;j<minoutputsize;j++)
  {
   if(!classifiers[i]->GetActivity())
    continue;

   ++classcounter[j];
   classquality[j]+=classifiers[i]->GetOutputData(0).Double[j];
  }
 }

 for(size_t i=0;i<classquality.size();i++)
  if(classcounter[i])
   classquality[i]/=classcounter[i];

 double maxcounter=0;

 for(size_t i=0;i<classquality.size();i++)
  if(maxcounter<classquality[i])
  {
   maxcounter=classquality[i];
  }

 SetOutputDataSize(0,MMatrixSize(1,minoutputsize));

 for(size_t i=0;i<classcounter.size();i++)
  POutputData[0].Double[i]=classquality[i];

 return true;
}

// Вычисление результата как суммы по входам
bool UCRFusion::SumInputCalculate(void)
{
 vector<UCRClassifier*> classifiers;

 for(int i=0;i<NumInputs;i++)
 {
  if(dynamic_cast<UCRClassifier*>(GetCItem(i).Item))
   classifiers.push_back(static_cast<UCRClassifier*>(GetCItem(i).Item));
 }

 if(classifiers.size()==0)
  return true;

 size_t minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];

 for(size_t i=1;i<classifiers.size();i++)
 {
  if(int(minoutputsize)<classifiers[0]->GetOutputDataSize(0)[1])
   minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];
 }

 // Вектор суммарного показателя качества
 vector<double> classquality;

 classquality.assign(minoutputsize,0);

 for(size_t i=0;i<classifiers.size();i++)
 {
  if(!classifiers[i]->GetActivity())
   continue;

  for(size_t j=0;j<minoutputsize;j++)
   classquality[j]+=classifiers[i]->GetOutputData(0).Double[j];
 }

 SetOutputDataSize(0,MMatrixSize(1,minoutputsize));

 for(size_t i=0;i<classquality.size();i++)
  POutputData[0].Double[i]=classquality[i];

 return true;
}


// Вычисление результата через попарное сравнение
bool UCRFusion::PairCalculate(void)
{
/* int classindex;
 int classindex2;
 double maxresult=-1,maxresult2=-1;

 double mininput,maxinput;

 vector<UCRClassifier*> classifiers;
 vector<CRFeatureSelectorCorr*> attributemodules;

 for(size_t i=0;i<NumInputs;i++)
 {
  if(dynamic_cast<UCRClassifier*>(GetCItem(i).Item))
   classifiers.push_back(static_cast<UCRClassifier*>(GetCItem(i).Item));
 }

 if(classifiers.size()==0)
  return true;

 attributemodules.resize(classifiers.size());
 for(size_t i=1;i<classifiers.size();i++)
 {
  attributemodules[i]=dynamic_cast<CRFeatureSelectorCorr*>(classifiers[i]->GetCItem(0).Item);
 }


 int minoutputsize=classifiers[0]->GetOutputDataSize(0);

 for(size_t i=1;i<classifiers.size();i++)
 {
  if(minoutputsize<classifiers[0]->GetOutputDataSize(0))
   minoutputsize=classifiers[0]->GetOutputDataSize(0);
 }

 // Вектор числа попаданий на определенный класс
 vector<double> classcounter;

 // Вектор суммарного показателя качества
 vector<double> classquality;

 // Вектор результатов предварительной попарной классификации
 vector<UCRFPreResult> preresults;

 // Число вариантов предварительной классификации (число сочетаний)
 int numpreresults=fact(minoutputsize)/(fact(2)*fact(minoutputsize-2));

 preresults.resize(numpreresults);

 PreResultsWeigths->resize(classifiers.size());

 for(size_t k=0;k<PreResultsWeigths->size();k++)
 {
//  PreResultsWeigths[i].assign(numpreresults,1);
  PreResultsWeigths[k].resize(numpreresults);
  if(attributemodules[k])
  {
   int n=0;
   for(size_t j=0;j<minoutputsize;j++)
    for(size_t i=j+1;i<minoutputsize;i++)
    {
     PreResultsWeigths[k][n]=(1.0-attributemodules[k]->GetTrainCorrTable()[j][0][i][0]);
     ++n;
    }
  }
 }



 classcounter.assign(minoutputsize,0);
 classquality.assign(minoutputsize,0);

 int n=0;
 for(size_t j=0;j<minoutputsize;j++)
  for(size_t i=j+1;i<minoutputsize;i++)
  {
   preresults[n].Ix1=j;
   preresults[n].Ix2=i;
   for(size_t k=0;k<classifiers.size();k++)
   {
    if(classifiers[i]->QualityRate->second >= minoutputsize ||
     !classifiers[i]->Activity)
     continue;

    preresults[n].Res1+=classifiers[k]->GetOutputData(0).Double[j]*PreResultsWeigths[k][n];
    preresults[n].Res2+=classifiers[k]->GetOutputData(0).Double[i]*PreResultsWeigths[k][n];
   }
   ++n;
  }

 for(size_t n=0;n<numpreresults;n++)
 {
 // if(classquality[preresults[n].Ix1]<preresults[n].Res1)
   classquality[preresults[n].Ix1]+=preresults[n].Res1;
 // if(classquality[preresults[n].Ix2]<preresults[n].Res2)
   classquality[preresults[n].Ix2]+=preresults[n].Res2;
 }

 SetOutputDataSize(0,minoutputsize);

 for(size_t i=0;i<classcounter.size();i++)
  POutputData[0].Double[i]=classquality[i];
              */
 return true;
}

// Вычисление результата по числу обнаружений класса
bool UCRFusion::RecognitionCounterCalculate(void)
{
 vector<UCRClassifier*> classifiers;

 for(int i=0;i<NumInputs;i++)
 {
  if(dynamic_cast<UCRClassifier*>(GetCItem(i).Item))
   classifiers.push_back(static_cast<UCRClassifier*>(GetCItem(i).Item));
 }

 if(classifiers.size()==0)
  return true;

 size_t minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];

 for(size_t i=1;i<classifiers.size();i++)
 {
  if(int(minoutputsize)<classifiers[0]->GetOutputDataSize(0)[1])
   minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];
 }

 // Вектор числа попаданий на определенный класс
 vector<double> classcounter;

 // Вектор суммарного показателя качества
 vector<double> classquality;

 classcounter.assign(minoutputsize,0);
 classquality.assign(minoutputsize,0);

 for(size_t i=0;i<classifiers.size();i++)
 {
  if(classifiers[i]->QualityRate->second >= int(minoutputsize) ||
     !classifiers[i]->GetActivity())
   continue;
  classcounter[classifiers[i]->QualityRate->second]+=1;

  classquality[classifiers[i]->QualityRate->second]+=1;//classifiers[i]->QualityRate->first;
 }

/* for(size_t i=0;i<classquality.size();i++)
  if(classcounter[i])
   classquality[i]/=classcounter[i];
  */
double maxcounter=0;

 for(size_t i=0;i<classcounter.size();i++)
  if(maxcounter<classcounter[i])
  {
   maxcounter=classcounter[i];
  }

 SetOutputDataSize(0,MMatrixSize(1,minoutputsize));
 for(size_t i=0;i<classcounter.size();i++)
  POutputData[0].Double[i]=classcounter[i];

 return true;
}

// Вычисление результата по числу обнаружений класса по входам
bool UCRFusion::InputRecognitionCounterCalculate(void)
{
 vector<UCRClassifier*> classifiers;

 for(int i=0;i<NumInputs;i++)
 {
  if(dynamic_cast<UCRClassifier*>(GetCItem(i).Item))
   classifiers.push_back(static_cast<UCRClassifier*>(GetCItem(i).Item));
 }

 if(classifiers.size()==0)
  return true;

 size_t minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];

 for(size_t i=1;i<classifiers.size();i++)
 {
  if(int(minoutputsize)<classifiers[0]->GetOutputDataSize(0)[1])
   minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];
 }

 // Вектор числа попаданий на определенный класс
 vector<double> classcounter;

 // Вектор суммарного показателя качества
 vector<double> classquality;

 classcounter.assign(minoutputsize,0);
 classquality.assign(minoutputsize,0);

 double maxout;
 int maxindex;

 for(size_t i=0;i<classifiers.size();i++)
 {
  if(!classifiers[i]->GetActivity())
   continue;

  maxout=0;
  maxindex=0;
  for(size_t j=0;j<minoutputsize;j++)
  {
   if(maxout<classifiers[i]->GetOutputData(0).Double[j])
   {
    maxout=classifiers[i]->GetOutputData(0).Double[j];
    maxindex=int(j);
   }
  }

  if(maxout>0)
  {
   classcounter[maxindex]+=1;

   classquality[maxindex]+=1;//classifiers[i]->QualityRate->first;
  }
 }

 SetOutputDataSize(0,MMatrixSize(1,minoutputsize));
 for(size_t i=0;i<classcounter.size();i++)
  POutputData[0].Double[i]=classcounter[i];

 return true;
}

// Вычисление результата по сумме входов-победителей
bool UCRFusion::SumInputRecognitionCounterCalculate(void)
{
 vector<UCRClassifier*> classifiers;

 for(int i=0;i<NumInputs;i++)
 {
  if(dynamic_cast<UCRClassifier*>(GetCItem(i).Item))
   classifiers.push_back(static_cast<UCRClassifier*>(GetCItem(i).Item));
 }

 if(classifiers.size()==0)
  return true;

 int minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];

 for(size_t i=1;i<classifiers.size();i++)
 {
  if(int(minoutputsize)<classifiers[0]->GetOutputDataSize(0)[1])
   minoutputsize=classifiers[0]->GetOutputDataSize(0)[1];
 }

 // Вектор числа попаданий на определенный класс
 vector<double> classcounter;

 // Вектор суммарного показателя качества
 vector<double> classquality;

 classcounter.assign(minoutputsize,0);
 classquality.assign(minoutputsize,0);

 double maxout;
 int maxindex;

 for(size_t i=0;i<classifiers.size();i++)
 {
  if(!classifiers[i]->GetActivity())
   continue;

  maxout=0;
  maxindex=0;
  for(int j=0;j<minoutputsize;j++)
  {
   if(maxout<classifiers[i]->GetOutputData(0).Double[j])
   {
    maxout=classifiers[i]->GetOutputData(0).Double[j];
    maxindex=j;
   }
  }

  if(maxout>0)
  {
   classcounter[maxindex]+=1;

   classquality[maxindex]+=maxout;
  }
 }

 SetOutputDataSize(0,MMatrixSize(1,minoutputsize));
 for(size_t i=0;i<classquality.size();i++)
  POutputData[0].Double[i]=classquality[i];

 return true;
}

// Устанавливает значения входного вектора для распознавания
bool UCRFusion::SetInput(const vector<double> &input)
{

 return true;
}
// ------------------------


}
//---------------------------------------------------------------------------
#endif
