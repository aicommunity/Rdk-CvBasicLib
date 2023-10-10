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

#ifndef UCRPERSEPTRON_CPP
#define UCRPERSEPTRON_CPP

#include "UCRPerseptron.h"
#include <fstream>

namespace RDK {

// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRPerseptron::UCRPerseptron(void)
//: UCRClassifier(name),
 : NumLayers("NumLayers",this,&UCRPerseptron::SetNumLayers),
  NumLayerInputs("NumLayerInputs",this,&UCRPerseptron::SetNumLayerInputs),
  AutoSetLayerInputs("AutoSetLayerInputs",this,&UCRPerseptron::SetAutoSetLayerInputs),
  Mode("Mode",this),
  Alpha("Alpha",this),
 // Weights("Weights",this),
  NameBin("NameBin", this),
  Inputs("Inputs",this),
  Outputs("Outputs",this)
{
/* AddLookupParameter("NumLayers",NumLayers);
 AddLookupParameter("NumLayerInputs",NumLayerInputs);
 AddLookupParameter("TrainingRate",TrainingRate);
 AddLookupParameter("Moment",Moment);
 AddLookupParameter("AutoSetLayerInputs",AutoSetLayerInputs);
 */
}

UCRPerseptron::~UCRPerseptron(void)
{
}
// --------------------------

// -----------------------------
// Методы доступа к данным
// -----------------------------
double UCRPerseptron::GetWeight(int layer, int col, int row)
{
 return Weights[layer][col][row];
}

double UCRPerseptron::GetInputs(int row)
{
 return Inputs[row];
}

double UCRPerseptron::GetOutputs(int layer, int row)
{
 return Outputs[layer][row];
}
// -----------------------------

// -----------------------------
// Методы управления параметрами
// -----------------------------
// Устанавливает число слоев сети
bool UCRPerseptron::SetNumLayers(const int &num)
{
 Ready=false;

 if(num < 1)
  return false;

// NumLayers=num;
 NumLayerInputs->resize(num);
 return true;
}

// Устанавливает число входов всех скрытых слоев
bool UCRPerseptron::SetNumLayerInputs(const vector<int> &numinputs)
{
 Ready=false; // Заглушка!!
 if(NumLayerInputs->size() == numinputs.size())
  {
   bool key=true;
   for(int i=0;i<int(NumLayerInputs->size());i++)
    if(NumLayerInputs[i] != numinputs[i])
     { key=false; break; }
   if(key)
    return true;
  }

 Ready=false;


 return true;
}

// Автоопределение размера слоев
bool UCRPerseptron::SetAutoSetLayerInputs(const bool &value)
{
 if(AutoSetLayerInputs == false)
 {
  Ready=false;
 }

 return true;
}
// -----------------------------

// ------------------------
// Методы счета
// ------------------------
// Загружает настройки из файла 'name'
bool UCRPerseptron::AFileLoad(fstream &file)
{
 int i,j,k;
 int numlayers,numclasses;
 vector<int> numinputs;

 file.read((char*)&numlayers,sizeof(numlayers));
 file.read((char*)&numclasses,sizeof(numclasses));
 numinputs.resize(numlayers);
 
 for(i=0;i<(int)numlayers;i++)
  file.read((char*)&(numinputs[i]),sizeof(numinputs[i]));

 if(numlayers <=0 || numclasses <2 || numinputs.size() ==0)
  return false;


 NumLayers=numlayers;
 SetOutputDataSize(0,MMatrixSize(1,numclasses));


 SetNumLayerInputs(numinputs);
 Build();

 for(k=0;k<(int)NumLayers();k++)
  {
   for(i=0;i<(int)Weights[k].size();i++)
    for(j=0;j<(int)Weights[k][i].size();j++)
     file.read((char*)&(Weights[k][i][j]),sizeof(Weights[k][i][j]));
  }

 return true;
}

// Сохраняет настройки в файл 'name'
bool UCRPerseptron::AFileSave(fstream &file)
{
 int i,j,k;

 size_t temp;
 temp=NumLayers();
 file.write((char*)&temp,sizeof(temp));
 temp=GetOutputDataSize(0)[1];
 file.write((char*)&temp,sizeof(temp));
 for(i=0;i<(int)NumLayers;i++)
  file.write((char*)&(NumLayerInputs[i]),sizeof(NumLayerInputs[i]));

 for(k=0;k<(int)NumLayers();k++)
  {
   for(i=0;i<(int)Weights[k].size();i++)
    for(j=0;j<(int)Weights[k][i].size();j++)
     file.write((char*)&(Weights[k][i][j]),sizeof(Weights[k][i][j]));
  }

 return true;
}
// ------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UCRPerseptron* UCRPerseptron::New(void)
{
 return new UCRPerseptron;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UCRPerseptron::ACRDefault(void)
{
 vector<int> numinputs;

 NameBin = "Weights.bin";

 numinputs.resize(2);
 numinputs[0]=200;
 numinputs[1]=900;

 NumLayers=2;
 SetOutputDataSize(0,MMatrixSize(1,2));
 SetNumLayerInputs(numinputs);
// MinOutputValue=0;
// MaxOutputValue=100;
 MinOutputValue=-0.5;
 MaxOutputValue=0.5;

 vector<double> minrate,maxrate;
 minrate.assign(GetOutputDataSize(0)[1],10);
 maxrate.assign(GetOutputDataSize(0)[1],90);

 MinQualityRate=minrate;
 MaxQualityRate=maxrate;

 AutoQualityRate=true;
 AutoAlignmentOutput=true;

// AutoAlignmentOutput=false;

 AutoSetLayerInputs=true;

 Mode=0;

 Alpha=1;

 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UCRPerseptron::ACRBuild(void)
{
 int i,j;

 Weights.resize(NumLayers);
 dWeights.resize(NumLayers);
 Outputs->resize(NumLayers);
 NumLayerInputs->resize(NumLayers);

 if(AutoSetLayerInputs())
 {
  vector<int> numinputs=NumLayerInputs();
  for(int i=1;i<NumLayers;i++)
   numinputs[i]=(NumLayerInputs[0]+GetOutputDataSize(0)[1])/(i+1);

  SetNumLayerInputs(numinputs);
 }

 if(NumLayers)
  Inputs->resize(NumLayerInputs[0]);
 else
  Inputs->resize(0);

 for(i=0;i<NumLayers;i++)
  {
   if(i == NumLayers-1)
    Outputs[i].resize(GetOutputDataSize(0)[1]);
   else
    Outputs[i].resize(NumLayerInputs[i+1]);
   }

 for(i=0;i<NumLayers;i++)
  {
   if(i == NumLayers-1)
    {
	 Weights[i].resize(GetOutputDataSize(0)[1]);
     dWeights[i].resize(GetOutputDataSize(0)[1]);
    }
   else
    {
     Weights[i].resize(NumLayerInputs[i+1]);
     dWeights[i].resize(NumLayerInputs[i+1]);
    }

   // Изменяем длины строк матрицы весов
   for(j=0;j<int(Weights[i].size());j++)
    {
     Weights[i][j].resize(NumLayerInputs[i]+1);
     dWeights[i][j].resize(NumLayerInputs[i]+1);
    }
  }

 Ready=true;
 //ResetTraining();
 return true;
}


// Сброс процесса счета.
bool UCRPerseptron::ACRReset(void)
{
 std::string path;
 if(GetEnvironment())
  path=GetEnvironment()->GetCurrentDataDir();
 path+=NameBin;
 FileLoad(path);
 return true;
}

// Выполняет расчет этого объекта на текущем шаге.
bool UCRPerseptron::ACRCalculate(void)
{
 int input_size=GetInputDataSize(0)[1];
 Inputs->resize(input_size);
 for(int i=0;i<input_size;i++)
  Inputs[i]=GetInputData(0)->Double[i];

 switch(Mode)
 {
 case 0:
  CalcNetwork(Inputs.v);
 break;

 case 1:
  CalcDeepNetwork(Inputs.v);
 break;
 }
 if(GetOutputDataSize(0)[1] > 0 && Outputs->size()>0 && int(Outputs[int(Outputs->size())-1].size())>=GetOutputDataSize(0)[1])
  memcpy(POutputData[0].Void, &Outputs[int(Outputs->size())-1][0],GetOutputDataSize(0)[1]*sizeof(double));

 return true;
}
// --------------------------


// --------------------------
// Скрытые методы обучения сети
// --------------------------
// Сброс настроек обучение в исходное состояние
void UCRPerseptron::AResetTraining(void)
{
 size_t i,j;
 int k;

 if(!Ready)
  return;

 time_t tm;
 time(&tm);
 srand(static_cast<unsigned>(tm));
 for(k=0;k<NumLayers;k++)
  {
   for(i=0;i<Weights[k].size();i++)
	for(j=0;j<Weights[k][i].size();j++)
	 {
	   Weights[k][i][j]=((double)((rand()*100.0)/double(RAND_MAX))/100.0-0.5);
	 }
  }

 for(k=0;k<NumLayers;k++)
  {
   for(i=0;i<Weights[k].size();i++)
    for(j=0;j<Weights[k][i].size();j++)
     {
      dWeights[k][i][j]=0;
     }

  }

}

// Сброс настроек обучения выбранного слоя в исходное состояние
void UCRPerseptron::LayerResetTraining(size_t index)
{
 size_t i,j,k;
 k=index;

 if(!Ready)
  return;

 for(i=0;i<Weights[k].size();i++)
  for(j=0;j<Weights[k][i].size();j++)
  {
   Weights[k][i][j]=((double)((rand()*100.0)/double(RAND_MAX))/100.0-0.5)*0.1;
  }

 for(i=0;i<Weights[k].size();i++)
  for(j=0;j<Weights[k][i].size();j++)
  {
   dWeights[k][i][j]=0;
  }
}
// --------------------------


// ------------------------
// Скрытые методы счета
// ------------------------
// Устанавливает значения входного вектора для распознавания
bool UCRPerseptron::SetInput(const vector<double> &input)
{
 int i;

 size_t mmin=(Inputs->size()<input.size())?Inputs->size():input.size();
 for(i=0;i<int(mmin);i++)
  {
   Inputs[i]=input[i];
  }

 return true;
}

// Производит расчет заданного слоя
void UCRPerseptron::CalcLayer(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights)
{
 int i,j;

 if(!Ready)
  return;

 if(weights.empty() || in_x.empty())
  return;

 int out_q_size=int(out_q.size());
 int weights_size_1=int(weights[0].size())-1;
 double *xp=&(in_x[0]);
 for(i=0;i<out_q_size;++i)
  {
   double sum=0;
   double *wp=&(weights[i][0]);
   xp=&(in_x[0]);
   for(j=0;j<weights_size_1;wp++,xp++,j++)
	sum+=(*wp)*(*xp);
   out_q[i]=Sigmoid(sum+(*wp)*MaxOutputValue);
  }
}

void UCRPerseptron::ReverseCalcLayer(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights, vector<vector<double> > &prev_weights)
{
 int i,j;

 if(!Ready)
  return;

 if(weights.empty() || in_x.empty())
  return;

 int out_q_size=int(out_q.size());
 int weights_size_1=int(weights[0].size())-1;
 double *xp=&(in_x[0]);
 for(i=0;i<out_q_size;++i)
  {
   double sum=0;
   double* wp=&(weights[i][0]);
   xp=&(in_x[0]);
   for(j=0;j<weights_size_1;wp++,xp++,j++)
	sum+=(*wp)*(*xp);
   out_q[i]=Sigmoid(sum+prev_weights[i][prev_weights[i].size()-1]*MaxOutputValue);
  }
}

void UCRPerseptron::ReverseCalcLayer0(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights, vector<double> &fi)
{
 int i,j;

 if(!Ready)
  return;

 if(weights.empty() || in_x.empty())
  return;

 int out_q_size=int(out_q.size());
 int weights_size_1=int(weights[0].size())-1;
 double *xp=&(in_x[0]);
 for(i=0;i<out_q_size;++i)
  {
   double sum=0;
   double *wp=&(weights[i][0]);
   xp=&(in_x[0]);
   for(j=0;j<weights_size_1;wp++,xp++,j++)
	sum+=(*wp)*(*xp);
   out_q[i]=Sigmoid(sum+fi[i]*MaxOutputValue);
  }
}


// Производит расчет всей сети
void UCRPerseptron::CalcNetwork(vector<double> &inputs)
{
 int i;
 vector<double> *p_inputs;

 if(!Ready)
  return;


 // Аналогично проводим расчет на всех слоях кроме последнего
 // вплоть до предпоследнего включительно
 p_inputs=&inputs;
 for(i=0;i<NumLayers;i++)
  {
   CalcLayer(*p_inputs,Outputs[i],Weights[i]);
   p_inputs=&(Outputs[i]);
  }

}


// Производит расчет всей сети
void UCRPerseptron::CalcDeepNetwork(vector<double> &inputs)
{
 int i;
 vector<double> *p_inputs;

 if(!Ready)
  return;

 // Аналогично проводим расчет на всех слоях кроме последнего
 // вплоть до предпоследнего включительно
 p_inputs=&inputs;
 for(i=0;i<NumLayers;i++)
  {
   CalcLayer(*p_inputs,Outputs[i],Weights[i]);

   if(i < NumLayers-1)
   {
	for(size_t j=0;j<Outputs[i].size();j++)
	{
	 double x=((double)((rand()*100.0)/double(RAND_MAX))/100.0);
	 Outputs[i][j]=(x<Outputs[i][j])?1:0;
    }
   }

   p_inputs=&(Outputs[i]);
  }

}


double UCRPerseptron::Sigmoid(double x)
{
 double alpha=Alpha;
 if(alpha*x>1.0e3)
  return MaxOutputValue;
//  return 0.5;

 if(alpha*x<-1.0e3)
  return MinOutputValue;
//  return -0.5;

// return 1./(1.+expl(-alpha*x))-0.5;
 return 1./(1.+expl(-alpha*x))-MinOutputValue;
}

// ------------------------


}
#endif


