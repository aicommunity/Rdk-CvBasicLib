#ifndef UCR_TEACHER_CVNETWORK_BP_CPP
#define UCR_TEACHER_CVNETWORK_BP_CPP

#include "UCRTeacherCVNetworkBP.h"
namespace RDK{

// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRTeacherCVNetworkBP::UCRTeacherCVNetworkBP(void)
: Network("Network",this,4)
// Perseptron("Perseptron",this,3),
// Moment("Moment",this,&UCRTeacherPerseptronBP::SetMoment)
//  TrainErrorResult("TrainErrorResult",this,0)
{
 TrainingEndingFlag=0;
 Err1=0;
 Err2=0;
 SuccessRecognition=0;
 TrainingUsl=0;
}

UCRTeacherCVNetworkBP::~UCRTeacherCVNetworkBP(void)
{
}
// --------------------------

// -----------------------------
// Методы доступа к данным
// -----------------------------
// Флаг состояния обучения
const int& UCRTeacherCVNetworkBP::GetTrainingEndingFlag(void) const
{
 return TrainingEndingFlag;
}

// Доступ к ошибкам первого и второго рода
const double& UCRTeacherCVNetworkBP::GetErr1(void) const
{
 return Err1;
}

const double& UCRTeacherCVNetworkBP::GetErr2(void) const
{
 return Err2;
}

// Процент правильного принятия решения
const double& UCRTeacherCVNetworkBP::GetSuccessRecognition(void) const
{
 return SuccessRecognition;
}
// -----------------------------

// -----------------------------
// Методы управления общедоступными свойствами
// -----------------------------

// -----------------------------

// ------------------------
// Методы счета
// ------------------------
// Загружает настройки из файла 'name'
bool UCRTeacherCVNetworkBP::AFileLoad(fstream &file)
{
 //fstream ofs(Network->TrainFileName.c_str(), ios::out);
 //if(!ofs)
  //return false;

 //Network->AFileLoad(ofs);
 //ofs.close();
 return true;
}

// Сохраняет настройки в файл 'name'
bool UCRTeacherCVNetworkBP::AFileSave(fstream &file)
{
 //fstream ifs(Network->TrainFileName.c_str(), ios::in | ios::trunc | ios::binary | ios::app);
 //if(!ifs)
  //return false;

// Network->AFileLoad(ifs);
 //ifs.close();
 return true;
}
// ------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UCRTeacherCVNetworkBP* UCRTeacherCVNetworkBP::New(void)
{
 return new UCRTeacherCVNetworkBP;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UCRTeacherCVNetworkBP::ACrDefault(void)
{
 //Moment=0.5;
 TrainingRate=0.1;
 SetNumInputs(4);
 Mode=0;
 SetNumOutputs(1);
// SetOutputDataElementSize(0,sizeof(double));
 SetOutputDataSize(0,MMatrixSize(1,1));
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UCRTeacherCVNetworkBP::ACrBuild(void)
{
 //Network=dynamic_cast<UCRConvolutionNetwork*>(&(*Classifier));
 TrainingEndingFlag=0;
 Err1=0;
 Err2=0;
 SuccessRecognition=0;
 TrainingUsl=0;

 return true;
}

// Сброс процесса счета.
bool UCRTeacherCVNetworkBP::ACrReset(void)
{
 time_t tm;
 time(&tm);
 srand(static_cast<unsigned>(tm));

 return true;
}

// Выполняет расчет этого объекта на текущем шаге.
bool UCRTeacherCVNetworkBP::ACrCalculate(void)
{
 switch(Mode)
 {
 case 0:
  if(Classifier)
   Classifier->SetActivity(true);
  if(TrainSample)
   TrainSample->Mode=0;
  if(CrossValidationSample)
   CrossValidationSample->Mode=0;
  if(TestSample)
   TestSample->Mode=1;
  //SetActivity(false);
  if( (TestSample->CurrentSampleIteration == 1)&&(TestSample->CurrentSample == 0) )
  {
   Err1=Err1/TestSample->SampleSize;
   Err2=Err2/TestSample->SampleSize;
   SuccessRecognition=SuccessRecognition/TestSample->SampleSize;;
  }
  if( TestSample->CurrentSampleIteration < 1 )
  {
   MDMatrix<double> Result = *(Network->Result);
   int res_index=(TestSample->CurrentSample)%(Network->NumClasses);
   double result=Result(res_index, 0);
   if( result < 0.9 )
	Err1++;

   if( result >= 0.9 )
	 SuccessRecognition++;

   for(int i=0; i<Result.GetRows(); i++)
   {
	if( (i!=res_index)&&(Result(i, 0)>0.9) )
	 Err2++;
   }
  }
 break;

 case 1:
/*  if(Classifier)
   Classifier->SetActivity(false);
  if(TrainSample)
   TrainSample->Mode=1;
  if(CrossValidationSample)
   CrossValidationSample->Mode=0;
  if(TestSample)
   TestSample->Mode=0;  */
  //SetActivity(true);

  //Classifier->SetActivity(true);
  //Train();
  //Classifier->SetActivity(false);
 break;
 }

 return true;
}
// --------------------------

// --------------------------
// Скрытые методы обучения сети
// --------------------------
// Сброс настроек обучение в исходное состояние
void UCRTeacherCVNetworkBP::ACrResetTraining(void)
{
 //Network->SetNetworkNumLayers(TrainSample->NumClasses);
 //Network->SetNetworkNumLayers(10);
 //Network->AutoSetLayerInputs=false;
 Network->Build();
 Network->ResetTraining();
 TrainingEndingFlag = 0;
}

// Собственно выполнение алгоритма обучения
double UCRTeacherCVNetworkBP::ACrTrainStep(size_t exp_class)
{
 if(!TrainingEndingFlag)
 {
  Network->Train(exp_class);
  TrainingError=Network->GetNetwork().GetError();
 }

 if(TrainingError >= TrainEpsilon)
 {
  TrainingUsl++;
 }

 if(TrainingUsl == 0)
  TrainingEndingFlag = 1;

 return TrainingError;
}

// Завершающие действия при завершении текущего обхода выборки
void UCRTeacherCVNetworkBP::ACrSampleIterationCompleteAction(void)
{
 TrainingUsl=0;
}
// --------------------------

}

#endif
