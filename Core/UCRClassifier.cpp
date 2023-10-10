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

#ifndef UCRCLASSIFIER_CPP
#define UCRCLASSIFIER_CPP


#include "UCRClassifier.h"
//#include "USupport.h"
#include <algorithm>


namespace RDK {
/*
        class UCRClassifier
*/

UCRClassifier::UCRClassifier(void)
// : NADItem(name),
 :
   NumClasses("NumClasses",this,&UCRClassifier::SetNumClasses),
   MinInputValue("MinInputValue",this,&UCRClassifier::SetMinInputValue),
   MaxInputValue("MaxInputValue",this,&UCRClassifier::SetMaxInputValue),
   MinOutputValue("MinOutputValue",this,&UCRClassifier::SetMinOutputValue),
   MaxOutputValue("MaxOutputValue",this,&UCRClassifier::SetMaxOutputValue),
   DesiredMinOutputValue("DesiredMinOutputValue",this),
   DesiredMaxOutputValue("DesiredMaxOutputValue",this),

   MinQualityRate("MinQualityRate",this,&UCRClassifier::SetMinQualityRate),
   MaxQualityRate("MaxQualityRate",this,&UCRClassifier::SetMaxQualityRate),
   TrainFileName("TrainFileName",this,&UCRClassifier::SetTrainFileName),
   ResultsFileName("ResultsFileName",this,&UCRClassifier::SetResultsFileName),
   AutoQualityRate("AutoQualityRate",this),
   AutoAlignmentOutput("AutoAlignmentOutput",this),

   Result("Result", this),
   QualityRate("QualityRate",this),
   ScaledResult("ScaledResult",this),
   IsSuccessed("IsSuccessed",this),
   ModifiedFlag("ModifiedFlag",this)
{
 Ready=false;
}

UCRClassifier::~UCRClassifier(void)
{
}
// -----------------------------


// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
UCRClassifier* UCRClassifier::New(void)
{
 return new UCRClassifier;
}
// ---------------------

// -----------------------------
// Методы управления параметрами
// -----------------------------
// Устанавливает число классов
bool UCRClassifier::SetNumClasses(const int &value)
{
 if(value <=0)
  return false;

 Ready=false;
 return true;
}

// Устанавливает граничные величины входных значений классификатора
bool UCRClassifier::SetMinInputValue(const double &value)
{
 ModifiedFlag=true;
 return true;
}

bool UCRClassifier::SetMaxInputValue(const double &value)
{
 ModifiedFlag=true;
 return true;
}

// Устанавливает граничные величины выходных значений классификатора
bool UCRClassifier::SetMinOutputValue(const double &value)
{
 ModifiedFlag=true;
 return true;
}

bool UCRClassifier::SetMaxOutputValue(const double &value)
{
 ModifiedFlag=true;
 return true;
}

// Устанавливает граничные величины допустимого показателя качества
bool UCRClassifier::SetMinQualityRate(const vector<double>& value)
{
// size_t sz=(value.size()<MaxQualityRate->size())?value.size():MaxQualityRate->size();
// for(size_t i=0;i<sz;i++)
//  if(value[i] <0 || value[i] >100)
//   return false;

 ModifiedFlag=true;
 return true;
}

bool UCRClassifier::SetMaxQualityRate(const vector<double>& value)
{
// size_t sz=(value.size()<MinQualityRate->size())?value.size():MinQualityRate->size();
// for(size_t i=0;i<sz;i++)
//  if(value[i] <0 || value[i] >100)
//   return false;

 ModifiedFlag=true;
 return true;
}

// Имя файла загрузки/сохранения состояния обучения
bool UCRClassifier::SetTrainFileName(const string &name)
{
 //if(name == "")
 // return false;

 ModifiedFlag=true;
 return true;
}

// Имя файла сохранения результатов работы сети
bool UCRClassifier::SetResultsFileName(const string &name)
{
 //if(name == "")
 // return false;

 ModifiedFlag=true;
 return true;
}
// -----------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UCRClassifier::ADefault(void)
{
 SetNumOutputs(2);
// SetOutputDataElementSize(0,sizeof(double));
// SetOutputDataElementSize(1,sizeof(double));
 NumClasses=10;
 SetOutputDataSize(0,MMatrixSize(1,10));
// SetOutputDataSize(1,MMatrixSize(1,0));

 MinInputValue=-0.5;
 MaxInputValue=0.5;

 MinOutputValue=-0.5;
 MaxOutputValue=0.5;

 DesiredMinOutputValue=-0.5;
 DesiredMaxOutputValue=0.5;
 double diff=DesiredMaxOutputValue-DesiredMinOutputValue;

 vector<double> minrate,maxrate;
 minrate.assign(GetOutputDataSize(0)[1],diff*0.1);
 maxrate.assign(GetOutputDataSize(0)[1],diff*0.9);

 MinQualityRate=minrate;
 MaxQualityRate=maxrate;

 AutoQualityRate=false;
 AutoAlignmentOutput=false;

// this->ChangeLookupPropertyType("NumOutputs",ptPubParameter);

 return ACRDefault();
}

bool UCRClassifier::ACRDefault(void)
{
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UCRClassifier::ABuild(void)
{
 int output_size=GetOutputDataSize(0)[1];
 SetOutputDataSize(0,MMatrixSize(1,NumClasses.v));
 ScaledResult->resize(output_size);

 int sz=int(MinQualityRate->size());
 MinQualityRate->resize(output_size);
 if(sz<output_size && sz>0)
 {
  for(int i=sz;i<output_size;i++)
   MinQualityRate[i]=MinQualityRate[0];
 }

 sz=int(MaxQualityRate->size());
 MaxQualityRate->resize(output_size);
 if(sz<output_size && sz>0)
 {
  for(int i=sz;i<output_size;i++)
   MaxQualityRate[i]=MaxQualityRate[0];
 }

 //if(GetOutputDataSize(0) != GetOutputDataSize(1))
 SetOutputDataSize(1,GetOutputDataSize(0));

 return ACRBuild();
}

bool UCRClassifier::ACRBuild(void)
{
 return true;
}

// Сброс процесса счета.
bool UCRClassifier::AReset(void)
{
 QualityRate=pair<float,int>(0.0f,0);
 IsSuccessed=false;
 return ACRReset();
}

bool UCRClassifier::ACRReset(void)
{
 return true;
}

// Выполняет расчет этого объекта на текущем шаге.
bool UCRClassifier::ACalculate(void)
{
 if(!ACRCalculate())
  return false;

 int output_size_0=GetOutputDataSize(0)[1];
 // Если разрешено автовырванивание выхода, то проводим его
 if(AutoAlignmentOutput && output_size_0>0)
 {
  double maxoutput=POutputData[0].Double[0];
  double minoutput=POutputData[0].Double[0];
  for(int k=1;k<output_size_0;k++)
  {
   if(maxoutput<POutputData[0].Double[k])
    maxoutput=POutputData[0].Double[k];
   if(minoutput>POutputData[0].Double[k])
    minoutput=POutputData[0].Double[k];
  }

  if(maxoutput && fabs(maxoutput-minoutput)>0)
   for(int k=0;k<output_size_0;k++)
    POutputData[0].Double[k]=
     (POutputData[0].Double[k]-minoutput)*(MaxOutputValue()-MinOutputValue)/(maxoutput-minoutput)+MinOutputValue;
 }

 // Вычисляем маштабированный выход [0;100]
 ScaledResult->resize(output_size_0);
 size_t o1size=GetOutputDataSize(1)[1];
 size_t o0size=output_size_0;

 if(o1size != o0size)
  SetOutputDataSize(1,GetOutputDataSize(0));
 if(NumOutputs>1)
  for(int k=0;k<output_size_0;k++)
   POutputData[1].Double[k]=ScaledResult[k]=(POutputData[0].Double[k]-MinOutputValue)*((DesiredMaxOutputValue()-DesiredMinOutputValue)/(MaxOutputValue()-MinOutputValue))+DesiredMinOutputValue;
 else
  for(int k=0;k<output_size_0;k++)
   ScaledResult[k]=(POutputData[0].Double[k]-MinOutputValue)*((DesiredMaxOutputValue()-DesiredMinOutputValue)/(MaxOutputValue()-MinOutputValue))+DesiredMinOutputValue;

 // Вычисляем показатель качества
 double qual;
 int res;
 vector<double>::iterator I,J;

 I = max_element(ScaledResult->begin(),ScaledResult->end());
 J=ScaledResult->begin();
 for(res=0;res<output_size_0;res++)
  if(J+res == I)
   break;

 // Вычисление показателей качества
 qual=100;
 for(int k=0;k<output_size_0;k++)
  if(k != res && qual>(ScaledResult[res]-ScaledResult[k]))
   qual=ScaledResult[res]-ScaledResult[k];

 QualityRate->first=qual;
 QualityRate->second=res;

 if(MinQualityRate[QualityRate->second] >= qual || MinQualityRate[QualityRate->second] <= 0)
  IsSuccessed=false;
 else
  IsSuccessed=true;

 return true;
}

bool UCRClassifier::ACRCalculate(void)
{
 return true;
}
// --------------------------


// Сброс настроек обучение в исходное состояние
void UCRClassifier::ResetTraining(void)
{
 if(!Ready)
  Build();

 if(AutoQualityRate)
 {
  MaxQualityRate->assign(GetOutputDataSize(0)[1],0);
 }

 ModifiedFlag=true;
 AResetTraining();
}
// --------------------------

// ------------------------
// Методы счета
// ------------------------
// Загружает настройки из файла 'name'
bool UCRClassifier::FileLoad(const string &name)
{
 fstream file((name).c_str(), ios_base::in | ios_base::binary);
 if(!file.is_open())
  return false;

 double temp;
 int itemp;
 string stemp;

 // Граничные величины выходных значений классификатора
 file.read((char*)&temp,sizeof(temp));
 MinOutputValue=temp;
 file.read((char*)&temp,sizeof(temp));
 MaxOutputValue=temp;

 file.read((char*)&temp,sizeof(temp));
 MinInputValue=temp;
 file.read((char*)&temp,sizeof(temp));
 MaxInputValue=temp;


 // Граничные величины допустимого показателя качества
 file.read((char*)&itemp,sizeof(itemp));
 MinQualityRate->resize(itemp);
 for(int i=0;i<itemp;i++)
 {
  file.read((char*)&temp,sizeof(temp));
  MinQualityRate[i]=temp;
 }
 file.read((char*)&itemp,sizeof(itemp));
 MaxQualityRate->resize(itemp);
 for(int i=0;i<itemp;i++)
 {
  file.read((char*)&temp,sizeof(temp));
  MaxQualityRate[i]=temp;
 }

 // Имя файла загрузки/сохранения состояния обучения
 file.read((char*)&itemp,sizeof(itemp));
 stemp.resize(itemp);
 file.read((char*)&stemp[0],itemp);
 TrainFileName=stemp;

 // Признак разрешения автоматической настройки показателя качества
 // по результатам обучения
 file.read((char*)&itemp,sizeof(itemp));
 AutoQualityRate=itemp;

 file.read((char*)&itemp,sizeof(itemp));
 AutoAlignmentOutput=itemp;

 file.read((char*)&itemp,sizeof(itemp));
 Activity=itemp;

 if(file.eof())
  return false;

 if(!AFileLoad(file))
  return false;

 ModifiedFlag=false;
 return true;
}

bool UCRClassifier::AFileLoad(fstream &file)
{
 return true;
}


// Сохраняет настройки в файл 'name'
bool UCRClassifier::FileSave(const string &name)
{
 if(!ModifiedFlag)
  return true;

 if(!Ready)
  return false;

 fstream file((name).c_str(), ios_base::out | ios_base::trunc | ios_base::binary);

 if(!file.is_open())
  return false;

 double temp;
 int itemp;
 string stemp;

 // Граничные величины выходных значений классификатора
 temp=MinOutputValue;
 file.write((char*)&temp,sizeof(temp));
 temp=MaxOutputValue;
 file.write((char*)&temp,sizeof(temp));

 temp=MinInputValue;
 file.write((char*)&temp,sizeof(temp));
 temp=MaxInputValue;
 file.write((char*)&temp,sizeof(temp));

 // Граничные величины допустимого показателя качества
 itemp=int(MinQualityRate->size());
 file.write((char*)&itemp,sizeof(itemp));
 for(int i=0;i<itemp;i++)
 {
  temp=MinQualityRate[i];
  file.write((char*)&temp,sizeof(temp));
 }
 itemp=int(MaxQualityRate->size());
 file.write((char*)&itemp,sizeof(itemp));
 for(int i=0;i<itemp;i++)
 {
  temp=MaxQualityRate[i];
  file.write((char*)&temp,sizeof(temp));
 }

 // Имя файла загрузки/сохранения состояния обучения
 itemp=int(TrainFileName->size());
 file.write((char*)&itemp,sizeof(itemp));
 stemp=TrainFileName;
 file.write((char*)&stemp[0],itemp);

 // Признак разрешения автоматической настройки показателя качества
 // по результатам обучения
 itemp=AutoQualityRate;
 file.write((char*)&itemp,sizeof(itemp));

 itemp=AutoAlignmentOutput;
 file.write((char*)&itemp,sizeof(itemp));

 itemp=Activity;
 file.write((char*)&itemp,sizeof(itemp));

 if(!AFileSave(file))
  return false;

 ModifiedFlag=false;
 return true;
}

bool UCRClassifier::AFileSave(fstream &file)
{
 return true;
}


// --------------------------
// Скрытые методы обучения сети
// --------------------------
// Сброс настроек обучения в исходное состояние
void UCRClassifier::AResetTraining(void)
{

}
// --------------------------



}
#endif



