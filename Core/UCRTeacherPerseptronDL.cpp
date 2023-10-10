#ifndef UCRTeacherPerseptronDL_CPP
#define UCRTeacherPerseptronDL_CPP

#include "UCRTeacherPerseptronDL.h"

namespace RDK {

// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRTeacherPerseptronDL::UCRTeacherPerseptronDL(void)
:
// Mode("Mode",this,&UCRTeacherPerseptronDL::SetMode),
 DeepPerseptron("DeepPerseptron",this,4),     //3

 dW("dW",this),
 dB("dB",this),
 dC("dC",this)

{
 Temp_dW=0;
 Temp_dB=0;
 Temp_dC=0;
 CCount=0;
 BCount=0;
}

UCRTeacherPerseptronDL::~UCRTeacherPerseptronDL(void)
{
}
// --------------------------

// -----------------------------
// Методы доступа к данным
// -----------------------------
// -----------------------------

// -----------------------------
// Методы управления общедоступными свойствами
// -----------------------------
bool UCRTeacherPerseptronDL::SetMode(const int &value)
{
 if(!UCRTeacher::SetMode(value))
  return false;


 return true;
}
// -----------------------------

// ------------------------
// Методы счета
// ------------------------
// Загружает настройки из файла 'name'
bool UCRTeacherPerseptronDL::AFileLoad(fstream &file)
{
 return true;
}

// Сохраняет настройки в файл 'name'
bool UCRTeacherPerseptronDL::AFileSave(fstream &file)
{
 return true;
}
// ------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UCRTeacherPerseptronDL* UCRTeacherPerseptronDL::New(void)
{
 return new UCRTeacherPerseptronDL;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UCRTeacherPerseptronDL::ACrDefault(void)
{
 SetNumInputs(4);
 Mode=0;
 SetNumOutputs(4);
// SetOutputDataElementSize(0,sizeof(double));
// SetOutputDataElementSize(1,sizeof(double));
// SetOutputDataElementSize(2,sizeof(double));
// SetOutputDataElementSize(3,sizeof(double));
 SetOutputDataSize(0,MMatrixSize(1,1));
 SetOutputDataSize(1,MMatrixSize(1,1));
 SetOutputDataSize(2,MMatrixSize(1,1));
 SetOutputDataSize(3,MMatrixSize(1,1));
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UCRTeacherPerseptronDL::ACrBuild(void)
{

 return true;
}

// Сброс процесса счета.
bool UCRTeacherPerseptronDL::ACrReset(void)
{
 Temp_dW=0;
 Temp_dB=0;
 Temp_dC=0;
 return true;
}

// Выполняет расчет этого объекта на текущем шаге.
bool UCRTeacherPerseptronDL::ACrCalculate(void)
{
 switch(Mode)
 {
 case 0:
  POutputData[0].Double[0]=0;
 break;

 case 1:
  POutputData[0].Double[0]=0;
  POutputData[1].Double[0]=dW;
  POutputData[2].Double[0]=dB;
  POutputData[3].Double[0]=dC;
 break;
 }

 return true;
}
// --------------------------

// --------------------------
// Скрытые методы обучения сети
// --------------------------
// Сброс настроек обучение в исходное состояние
void UCRTeacherPerseptronDL::ACrResetTraining(void)
{
 DeepPerseptron->NumLayers=1;
 DeepPerseptron->NumClasses=DeepPerseptron->NumLayerInputs[0];
 DeepPerseptron->AutoSetLayerInputs=false;
 DeepPerseptron->Build();
 DeepPerseptron->ResetTraining();

 // Инициализируем вектор смещений нулевого слоя
 Fi.resize(DeepPerseptron->Inputs->size());
 for(size_t i=0;i<Fi.size();i++)
  Fi[i]=(double)(((rand()*100.0)/double(RAND_MAX))/100.0-0.5)*0.1;
}

// Собственно выполнение алгоритма обучения
double UCRTeacherPerseptronDL::ACrTrainStep(size_t exp_class)
{
 if(DeepPerseptron->NumLayers<1)
  return 0;

 DeepPerseptron->Calculate();
 int hidden_layer_index=DeepPerseptron->NumLayers-1;
 int visible_layer_index=hidden_layer_index-1;

 if(visible_layer_index < 0)
 {
  x1=DeepPerseptron->Inputs;
 }
 else
  x1=DeepPerseptron->Outputs[visible_layer_index];

 Q=DeepPerseptron->Outputs[hidden_layer_index];
 vector<vector<double> > &hidden_weights=DeepPerseptron->Weights[hidden_layer_index];

 h1.resize(Q.size());
 for(size_t i=0;i<h1.size();i++)
  h1[i]=(((double)((rand()*100.0)/double(RAND_MAX))/100.0)<Q[i])?1:0;

 P.resize(h1.size());
 if(visible_layer_index>=0)
 {
  vector<vector<double> > &visible_weights=DeepPerseptron->Weights[visible_layer_index];
  DeepPerseptron->ReverseCalcLayer(h1, P, hidden_weights,visible_weights);
 }
 else
 {
  DeepPerseptron->ReverseCalcLayer0(h1, P, hidden_weights,Fi);
 }

 x2.resize(P.size());
 for(size_t i=0;i<h1.size();i++)
  x2[i]=(((double)((rand()*100.0)/double(RAND_MAX))/100.0)<P[i])?1:0;
 Q2.resize(P.size());

 DeepPerseptron->CalcLayer(x2, Q2, hidden_weights);

 // Настраиваем веса
 for(size_t i=0;i<hidden_weights.size();i++)
 {
  for(size_t j=0;j<hidden_weights[i].size();j++)
  {
   if(j < hidden_weights[i].size()-1)
   {
	double d=(h1[i]*x1[j]-Q2[i]*x2[j]);
//   dW.v=(dW.v<fabs(d))?fabs(d):dW.v;
	Temp_dW+=d*d;
	++WCount;
	hidden_weights[i][j]+=TrainingRate*d;
   }
   else
   if(j == hidden_weights[i].size()-1)// c (hidden layer)
   {
	double d=(h1[i]-Q[i]);
//	dC.v=(dC.v<fabs(d))?fabs(d):dC.v;
	Temp_dC+=d*d;
	hidden_weights[i][j]+=TrainingRate*d;
	++CCount;
   }
  }
 }

 if(visible_layer_index>=0)
 {
  vector<vector<double> > &visible_weights=DeepPerseptron->Weights[visible_layer_index];
  for(size_t i=0;i<visible_weights.size();i++)
  {
   size_t j=visible_weights[i].size()-1;// b (visible layer)
   double d=(x1[i]-x2[i]);
//  dB.v=(dB.v<fabs(d))?fabs(d):dB.v;
   Temp_dB+=d*d;
   visible_weights[i][j]+=TrainingRate*d;
   ++BCount;
  }
 }
 else
 {
  for(size_t i=0;i<Fi.size();i++)
  {
   double d=(x1[i]-x2[i]);
//  dB.v=(dB.v<fabs(d))?fabs(d):dB.v;
   Temp_dB+=d*d;
   Fi[i]+=TrainingRate*d;
   ++BCount;
  }

 }

 return 0;
}

// Создание нового слоя для обучения
// Подготоваливает алгоритм к обучению этого слоя и
// возвращает индекс созданного слоя
int UCRTeacherPerseptronDL::Train1CreateLayer(void)
{
 DeepPerseptron->NumLayers=DeepPerseptron->NumLayers+1;
 vector<int> num_inputs=DeepPerseptron->NumLayerInputs;
 num_inputs.resize(DeepPerseptron->NumLayers);
 num_inputs[DeepPerseptron->NumLayers-1]=num_inputs[0];
 DeepPerseptron->NumLayerInputs=num_inputs;
 DeepPerseptron->Build();
 DeepPerseptron->LayerResetTraining(DeepPerseptron->NumLayers-1);
 TrainSample->Reset();
 Reset();

 return DeepPerseptron->NumLayers-1;
}

// Завершающие действия при завершении текущего обхода выборки
void UCRTeacherPerseptronDL::ACrSampleIterationCompleteAction(void)
{
 switch(Mode)
 {
 case 1:
  if(WCount)
   dW=1000*sqrt(Temp_dW)/WCount;
  if(BCount)
   dB=1000*sqrt(Temp_dB)/BCount;
  if(CCount)
   dC=1000*sqrt(Temp_dC)/CCount;

  Temp_dW=0;
  Temp_dB=0;
  Temp_dC=0;
  CCount=0;
  BCount=0;
  WCount=0;
 break;
 }
}


// Вычисляет оценку обучения этапа 1
double UCRTeacherPerseptronDL::CalcTrain1Estimation(void)
{
 return 0;
}
// --------------------------

}
#endif
