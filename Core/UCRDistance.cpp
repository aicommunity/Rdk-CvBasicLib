// ===========================================================
// Version:        3.0.3
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2002.
E-mail:        alexab@ailab.ru
url:            http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */

#include "UCRDistance.h"
#include <algorithm>
#include <fstream>


namespace RDK {

using namespace std;

int elemsort(const void *v1,const void *v2)
{
 double vv1,vv2;

 memcpy(&vv1,v1,sizeof(double));
 memcpy(&vv2,v2,sizeof(double));
 if(vv1<vv2)
  return -1;

 if(vv1>vv2)
  return 1;

 return 0;
}

// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRDistance::UCRDistance(void)
//: UCRClassifier(name),
 : NumLayerInputs("NumLayerInputs",this,&UCRDistance::SetNumLayerInputs),
   DispersioUCRoppingFlag("DispersioUCRoppingFlag",this),
   MaxDispersionValue("MaxDispersionValue",this),
   NumMaxElements("NumMaxElements",this),
  MinElementsDistance("MinElementsDistance",this),
  MaxRecThreshold("MaxRecThreshold",this,&UCRDistance::SetMaxRecThreshold),
 MinRecThreshold("MinRecThreshold",this),
 RecognitionType("RecognitionType",this)
{
/* AddLookupParameter("NumLayerInputs",NumLayerInputs);

 AddLookupParameter("NumMaxElements",NumMaxElements);
 AddLookupParameter("MinElementsDistance",MinElementsDistance);
 AddLookupParameter("DispersioUCRoppingFlag",DispersioUCRoppingFlag);
 AddLookupParameter("MaxDispersionValue",MaxDispersionValue);
 AddLookupParameter("RecognitionType",RecognitionType);

 AddLookupParameter("MinRecThreshold",MinRecThreshold);
 AddLookupParameter("MaxRecThreshold",MaxRecThreshold);
 */
}

UCRDistance::~UCRDistance(void)
{
}
// --------------------------

// -----------------------------
// Методы управления параметрами
// -----------------------------
// Устанавливает число входов всех скрытых слоев
bool UCRDistance::SetNumLayerInputs(const size_t &numinputs)
{
// NumLayerInputs=numinputs;
 Ready=false;

 return true;
}

// Устанавливает скорость обучения сети
bool UCRDistance::SetTrainingRate(const double &tr)
{
 if(tr <= 0)
  return false;

 return true;
}

// Порог распознавания по максимуму суммы превышения
bool UCRDistance::SetMaxRecThreshold(const double &value)
{
// MaxOutputValue=(0.5-MinRecThreshold-value*(0.5-MinRecThreshold))*OutputSize;
// MinOutputValue=0;

 return true;
}
// -----------------------------

// -----------------------------
// Методы доступа к данным модели
// -----------------------------
// Вектор математического ожидания
double UCRDistance::GetMiddleSamples(int i, int j) const
{
 return MiddleSamples[i][j];
}

// Вектор выборки
double UCRDistance::GetSamples(int i, int j, int k) const
{
 return Samples[i][j][k];
}

// Вектор исходных данных выборки
double UCRDistance::GetPreSamples(int i, int j, int k) const
{
 return PreSamples[i][j][k];
}

// Вектор оригинальных выходов слоев сети
const vector<double>& UCRDistance::GetNativeOutput(void) const
{
 return NativeOutput;
}

// Вектор входов
const vector<double>& UCRDistance::GetInputs(void) const
{
 return Inputs;
}

// Дисперсия отклонений
double UCRDistance::GetDispersion(int i, int j) const
{
 return Dispersion[i][j];
}

// Стандартное отклонение
double UCRDistance::GetSDeviation(int i, int j) const
{
 if(fabs(MiddleSamples[i][j])>1e-5)
  return sqrt(Dispersion[i][j])*100.0/fabs(MiddleSamples[i][j]);
 else
  return 1e6;
}


// -----------------------------

// ------------------------
// Методы счета
// ------------------------
// Загружает настройки из файла
bool UCRDistance::AFileLoad(fstream &file)
{
 int i,j,k;
 size_t numclasses;
 int rectype;
 size_t numinputs;
 size_t temp;

 file.read((char*)&numclasses,sizeof(numclasses));
 file.read((char*)&numinputs,sizeof(numinputs));

 if(numclasses <2 || numinputs ==0)
  return false;

 SetOutputDataSize(0,MMatrixSize(1,int(numclasses)));

 SetNumLayerInputs(numinputs);
 Build();

 file.read((char*)&rectype,sizeof(rectype));
 RecognitionType=rectype;


 file.read((char*)&temp,sizeof(temp));
 PreSamples.resize(temp);
 for(i=0;i<(int)PreSamples.size();i++)
 {
  file.read((char*)&temp,sizeof(temp));
  PreSamples[i].resize(temp);
  for(j=0;j<(int)PreSamples[i].size();j++)
  {
   file.read((char*)&temp,sizeof(temp));
   PreSamples[i][j].resize(temp);
   for(k=0;k<(int)PreSamples[i][j].size();k++)
    file.read((char*)&(PreSamples[i][j][k]),sizeof(PreSamples[i][j][k]));
  }
 }

 CalcMiddleSamples();
 CalcMaxElements();

 return true;
}

// Сохраняет настройки в файл
bool UCRDistance::AFileSave(fstream &file)
{
 size_t i,j,k;
 int rectype;

 size_t temp;
 temp=GetOutputDataSize(0)[1];
 file.write((char*)&temp,sizeof(temp));
 temp=NumLayerInputs;
 file.write((char*)&temp,sizeof(temp));

 rectype=RecognitionType;
 file.write((char*)&rectype,sizeof(rectype));

 temp=PreSamples.size();
 file.write((char*)&temp,sizeof(temp));

 for(i=0;i<PreSamples.size();i++)
 {
  temp=PreSamples[i].size();
  file.write((char*)&temp,sizeof(temp));
  for(j=0;j<PreSamples[i].size();j++)
  {
   temp=PreSamples[i][j].size();
   file.write((char*)&temp,sizeof(temp));
   for(k=0;k<PreSamples[i][j].size();k++)
    file.write((char*)&(PreSamples[i][j][k]),sizeof(PreSamples[i][j][k]));
  }
 }

 return true;
}
// ------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UCRDistance* UCRDistance::New(void)
{
 return new UCRDistance;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UCRDistance::ACRDefault(void)
{
 SetOutputDataSize(0,MMatrixSize(1,2));
 SetNumLayerInputs(100);
// MinOutputValue=0;//-0.5;
// MaxOutputValue=10000;//0.5;

 vector<double> minrate,maxrate;
 minrate.assign(GetOutputDataSize(0)[1],10);
 maxrate.assign(GetOutputDataSize(0)[1],90);

 MinQualityRate=minrate;
 MaxQualityRate=maxrate;

 AutoQualityRate=true;
 AutoAlignmentOutput=false;

// NumMaxElements=20;
 MinElementsDistance=1000;

 DispersioUCRoppingFlag=1;
 MaxDispersionValue=50;

 RecognitionType=5;

 MinRecThreshold=0.7;
 MaxRecThreshold=0.98;
 MaxInputValue=0.5;
 MinInputValue=0;
 MinOutputValue=0;
 MaxOutputValue=0.001;//((MaxInputValue-MinInputValue)-MaxRecThreshold*(MaxInputValue-MinInputValue))*NumLayerInputs;

 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UCRDistance::ACRBuild(void)
{
 return true;
}


// Сброс процесса счета.
bool UCRDistance::ACRReset(void)
{
 return true;
}

bool UCRDistance::ACRCalculate(void)
{
 int outputsize=GetOutputDataSize(0)[1];
 NativeOutput.resize(GetOutputDataSize(0)[1]);

 switch(RecognitionType)
 {
 case 0:
  memcpy(&NativeOutput[0],&Inputs[0],outputsize*sizeof(double));
  for(int i=outputsize;i<int(NumLayerInputs);i++)
  {
   int classindex=i/outputsize;
   classindex*=outputsize;
   classindex=i-classindex;
   if(NativeOutput[classindex]<Inputs[i])
    NativeOutput[classindex]=Inputs[i];
  }
  for(int k=0;k<outputsize;k++)
   POutputData[0].Double[k]=NativeOutput[k];
 break;

 case 1:
 for(int j=0;j<outputsize;j++)
 {
  NativeOutput[j]=-1;
  for(size_t k=0;k<Samples[j].size();k++)
  {
   double omin=0;
   for(size_t i=0;i<NumLayerInputs;i++)
    omin+=(Samples[j][k][i]-Inputs[i])*(Samples[j][k][i]-Inputs[i]);
   omin=sqrt(omin);

   if(NativeOutput[j] < 0 || NativeOutput[j] > omin)
    NativeOutput[j]=omin;
  }
 }
 break;

 case 2:
 for(size_t j=0;j<MiddleSamples.size();j++)
 {
  NativeOutput[j]=-1;
  double omin=0;
  for(size_t k=0;k<MiddleSamples[j].size();k++)
   omin+=(MiddleSamples[j][k]-Inputs[k])*(MiddleSamples[j][k]-Inputs[k]);
//  for(size_t k=0;k<NumMaxElements;k++)
//   omin+=(MiddleSamples[j][MaxElementsIndex[k]]-Inputs[MaxElementsIndex[k]])*(MiddleSamples[j][MaxElementsIndex[k]]-Inputs[MaxElementsIndex[k]]);
//  for(size_t k=0;k<MiddleSamples[j].size();k++)
//   omin+=ElementWeights[MaxElementsIndex[k]]*(MiddleSamples[j][k]-Inputs[k])*(MiddleSamples[j][k]-Inputs[k]);

//  for(size_t k=0;k<NumMaxElements;k++)
//   if(find(DispersionBanIndexes.begin(),DispersionBanIndexes.end(),MaxClassElementsIndex[j][k]) == DispersionBanIndexes.end())
//   omin+=Weights[j][MaxClassElementsIndex[j][k]]*(MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]])*
//         (MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]]);

//  for(size_t k=0;k<NumMaxElements;k++)
//   omin+=Weights[j][MaxClassElementsIndex[j][k]]*
//        (MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]])*
//        (MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]]);

  omin=sqrt(omin);
  NativeOutput[j]=omin;
 }
 for(int k=0;k<outputsize;k++)
  POutputData[0].Double[k]=-NativeOutput[k];
 break;

 case 3:
 for(size_t j=0;j<MiddleSamples.size();j++)
 {
  NativeOutput[j]=-1;
  double omin=0;
//  for(size_t k=0;k<NumMaxElements;k++)
//   omin+=(MiddleSamples[j][MaxElementsIndex[k]]-Inputs[MaxElementsIndex[k]])*(MiddleSamples[j][MaxElementsIndex[k]]-Inputs[MaxElementsIndex[k]]);
//  for(size_t k=0;k<MiddleSamples[j].size();k++)
//   omin+=ElementWeights[MaxElementsIndex[k]]*(MiddleSamples[j][k]-Inputs[k])*(MiddleSamples[j][k]-Inputs[k]);

  for(size_t k=0;k<MiddleSamples.size();k++)
   if(find(DispersionBanIndexes.begin(),DispersionBanIndexes.end(),MaxClassElementsIndex[j][k]) == DispersionBanIndexes.end())
   omin+=/*Weights[j][MaxClassElementsIndex[j][k]]**/(MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]])*
         (MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]]);

//  for(size_t k=0;k<NumMaxElements;k++)
//   omin+=Weights[j][MaxClassElementsIndex[j][k]]*
//        (MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]])*
//        (MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]]);

  omin=sqrt(omin);
  NativeOutput[j]=omin;
 }
 for(int k=0;k<outputsize;k++)
  POutputData[0].Double[k]=-NativeOutput[k];

 break;

 case 4:
 for(size_t j=0;j<MiddleSamples.size();j++)
 {
  NativeOutput[j]=-1;
  double omin=0;
  for(size_t k=0;k<MiddleSamples.size();k++)
   if(find(DispersionBanIndexes.begin(),DispersionBanIndexes.end(),MaxClassElementsIndex[j][k]) == DispersionBanIndexes.end())
   omin+=Weights[j][MaxClassElementsIndex[j][k]]*(MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]])*
         (MiddleSamples[j][MaxClassElementsIndex[j][k]]-Inputs[MaxClassElementsIndex[j][k]]);

  omin=sqrt(omin);
  NativeOutput[j]=omin;
 }
 for(int k=0;k<outputsize;k++)
  POutputData[0].Double[k]=-NativeOutput[k];

 break;
 }

 return true;
}
// --------------------------


// --------------------------
// Скрытые методы обучения сети
// --------------------------
// Сброс настроек обучение в исходное состояние
void UCRDistance::AResetTraining(void)
{
// Samples.resize(GetOutputDataSize(0));
 PreSamples.resize(GetOutputDataSize(0)[1]);
// Inputs.resize(NumLayerInputs);

 for(size_t j=0;j<Samples.size();j++)
 {
  Samples[j].clear();
  PreSamples[j].clear();
 }
}

// Однократное обучение на заданном примере
double UCRDistance::ATrain(size_t exp_class)
{
 double E=0;

 PreSamples[exp_class].push_back(Inputs);

 // Расчет максимальных элементов вектора
 if(int(exp_class) == GetOutputDataSize(0)[1]-1)
 {
  CalcMiddleSamples();
  CalcMaxElements();
 }

 return E;
}

// Расчет средних ожидаемых векторов
void UCRDistance::CalcMiddleSamples(void)
{
 // Считаем среднее
 MiddleSamples.resize(PreSamples.size());

 for(size_t i=0;i<PreSamples.size();i++)
 {
  MiddleSamples[i].assign(PreSamples[i][0].size(),0);
  for(size_t k=0;k<PreSamples[i][0].size();k++)
  {
   for(size_t j=0;j<PreSamples[i].size();j++)
   {
    MiddleSamples[i][k]+=PreSamples[i][j][k];
   }
   MiddleSamples[i][k]/=PreSamples[i].size();
  }
 }

 // Считаем дисперсию
 Dispersion.resize(PreSamples.size());
 DispersionBanIndexes.clear();

 for(size_t i=0;i<PreSamples.size();i++)
 {
  Dispersion[i].assign(PreSamples[i][0].size(),0);
  for(size_t k=0;k<PreSamples[i][0].size();k++)
  {
   for(size_t j=0;j<PreSamples[i].size();j++)
   {
    Dispersion[i][k]+=(MiddleSamples[i][k]-PreSamples[i][j][k])*
                      (MiddleSamples[i][k]-PreSamples[i][j][k]);
   }
   Dispersion[i][k]/=PreSamples[i].size();
//   Dispersion[i][k]=sqrt(Dispersion[i][k]);
//   Dispersion[i][k]/=MiddleSamples[i][k];
//   Dispersion[i][k]*=100;

   // Считаем запрещенные индексы
   if(GetSDeviation(int(i),int(k))>MaxDispersionValue)
    DispersionBanIndexes.push_back(int(k));
  }
 }

// CalcDispersioUCRopping();
 Samples=PreSamples;
// CalcMiddleSamples();
}

// Расчет максимальных элементов вектора
void UCRDistance::CalcMaxElements(void)
{
 if(MiddleSamples.size() == 0 ||
    MiddleSamples[0].size() == 0)
  return;

 // Считаем максимальные компоненты выборочно для класса
 NumMaxElements->resize(MiddleSamples.size());
 MaxClassElements.resize(MiddleSamples.size());
 MaxClassElementsIndex.resize(MiddleSamples.size());

 for(size_t k=0;k<MiddleSamples.size();k++)
 {
  MaxClassElements[k].assign(MiddleSamples[k].size(),1e6);
  MaxClassElementsIndex[k].assign(MiddleSamples[k].size(),0);

  for(size_t j=0;j<MiddleSamples[k].size();j++)
  {
   for(size_t i=0;i<MiddleSamples.size();i++)
   {
    if(i != k && MaxClassElements[k][j]>fabs(MiddleSamples[k][j]-MiddleSamples[i][j]))
    {
     MaxClassElements[k][j]=fabs(MiddleSamples[k][j]-MiddleSamples[i][j]);
    }
   }
  }
 }

 for(size_t k=0;k<MaxClassElements.size();k++)
 {
  vector<double> temp=MaxClassElements[k];
  qsort(&temp[0],temp.size(),sizeof(double),elemsort);
  reverse(temp.begin(),temp.end());
  vector<double> orig=MaxClassElements[k];

  // Расчет индексов максимальных компонент
  for(size_t j=0;j<MiddleSamples[0].size();j++)
   for(size_t i=0;i<MiddleSamples[0].size();i++)
   if(temp[j] != -1 && orig[i] == temp[j])
   {
    MaxClassElementsIndex[k][j]=i;
    orig[i]=-1;
    break;
   }

 }

 // Расчет весов компонент выборочно для класса
 Weights.resize(MaxClassElements.size());
 for(size_t k=0;k<Weights.size();k++)
 {
  Weights[k].assign(MaxClassElements[k].size(),1);
  double emax,emin;
  emax=emin=MaxClassElements[k][0];
  for(size_t i=1;i<MaxClassElements[k].size();i++)
  {
   if(MaxClassElements[k][i]<emin)
    emin=MaxClassElements[k][i];
   if(MaxClassElements[k][i]>emax)
    emax=MaxClassElements[k][i];
  }

  if(emax-emin>0)
   for(size_t i=0;i<MaxClassElements[k].size();i++)
   {
//     Weights[k][i]=fabs((MaxClassElements[k][i]-emin)/(emax-emin));
//    if(Dispersion[k][i]>0)
//     Weights[k][i]=fabs(((MaxClassElements[k][i]-emin)/(emax-emin))/(GetSDeviation(k,i)/MaxDispersionValue));
//    else
     Weights[k][i]=fabs((MaxClassElements[k][i]-emin)/(emax-emin));
   }

 }


// NumMaxElements=NumLayerInputs/3;//MiddleSamples.size();//NumLayerInputs;
}


// Отсечение выбросов в обучающей выборке по дисперсии
void UCRDistance::CalcDispersioUCRopping(void)
{
 Samples=PreSamples;
 switch(DispersioUCRoppingFlag)
 {
 case 1:
  for(size_t i=0;i<Dispersion.size();i++)
  {
   for(size_t j=0;j<Dispersion[i].size();j++)
   {
    if(GetSDeviation(int(i),int(j))>MaxDispersionValue)
    {
     for(size_t n=0;n<Samples.size();n++)
      for(size_t m=0;m<Samples[n].size();m++)
       Samples[n][m][j]=0;
    }
   }
  }

 break;

 case 2:
  for(size_t i=0;i<Dispersion.size();i++)
  {
   for(size_t j=0;j<Dispersion[i].size();j++)
   {
    if(Dispersion[i][j]>MaxDispersionValue)
    {

    }
   }
  }

 break;
 }

}
// --------------------------


// ------------------------
// Скрытые методы счета
// ------------------------
// Устанавливает значения входного вектора для распознавания
bool UCRDistance::SetInput(const vector<double> &input)
{
 size_t i;

 Inputs.resize(NumLayerInputs);

 size_t mmin=(Inputs.size()<input.size())?Inputs.size():input.size();
 for(i=0;i<mmin;i++)
  {
   Inputs[i]=input[i];
  }

 return true;
}
// ------------------------


}

