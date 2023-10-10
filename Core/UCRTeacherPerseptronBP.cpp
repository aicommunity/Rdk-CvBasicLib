#ifndef UCRTeacherPerseptronBP_CPP
#define UCRTeacherPerseptronBP_CPP

#include "UCRTeacherPerseptronBP.h"

namespace RDK {

// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRTeacherPerseptronBP::UCRTeacherPerseptronBP(void)
:
// Mode("Mode",this,&UCRTeacherPerseptronBP::SetMode),

 Moment("Moment",this,&UCRTeacherPerseptronBP::SetMoment),
 Perseptron("Perseptron",this,4)   // 3

{
}

UCRTeacherPerseptronBP::~UCRTeacherPerseptronBP(void)
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
bool UCRTeacherPerseptronBP::SetMode(const int &value)
{
 return true;
}

// Устанавливает момент сети
bool UCRTeacherPerseptronBP::SetMoment(const double &m)
{
 if(m < 0 || m > 1.0)
  return false;

 return true;
}

// -----------------------------

// ------------------------
// Методы счета
// ------------------------
// Загружает настройки из файла 'name'
bool UCRTeacherPerseptronBP::AFileLoad(fstream &file)
{
 return true;
}

// Сохраняет настройки в файл 'name'
bool UCRTeacherPerseptronBP::AFileSave(fstream &file)
{
 return true;
}
// ------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UCRTeacherPerseptronBP* UCRTeacherPerseptronBP::New(void)
{
 return new UCRTeacherPerseptronBP;
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UCRTeacherPerseptronBP::ACrDefault(void)
{
 Moment=0.5;
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
bool UCRTeacherPerseptronBP::ACrBuild(void)
{

 return true;
}

// Сброс процесса счета.
bool UCRTeacherPerseptronBP::ACrReset(void)
{
 time_t tm;
 time(&tm);
 srand(static_cast<unsigned>(tm));

 return true;
}

// Выполняет расчет этого объекта на текущем шаге.
bool UCRTeacherPerseptronBP::ACrCalculate(void)
{
 return true;
}
// --------------------------

// --------------------------
// Скрытые методы обучения сети
// --------------------------
// Сброс настроек обучение в исходное состояние
void UCRTeacherPerseptronBP::ACrResetTraining(void)
{
 Perseptron->NumClasses=TrainSample->NumClasses;
 Perseptron->AutoSetLayerInputs=false;
 Perseptron->Build();
 Perseptron->ResetTraining();
}

// Собственно выполнение алгоритма обучения
double UCRTeacherPerseptronBP::ACrTrainStep(size_t exp_class)
{
 if(Perseptron->NumLayers == 0)
  return 1;

 //int i,j,l;
 double E;
 double corr;
 vector<double> delta;
 vector<double> delta_prev;
 vector<vector<double> > weights_prev;
 vector<vector<vector<double> > > &weights=Perseptron->Weights;
 vector<vector<vector<double> > > &dweights=Perseptron->dWeights;
 vector<vector<double> > &outputs=Perseptron->Outputs.v;
 vector<double> &inputs=Perseptron->Inputs.v;

 Perseptron->Mode=0;
 if(!Perseptron->IsReady())
  return 0;

 // Проводим распознавание примера
 Perseptron->Calculate();

 double alpha=Perseptron->Alpha;

 // Рассчитываем поправки выходному слою
 delta.assign(weights[Perseptron->NumLayers-1].size(),0);
 for(int j=0;j<(int)weights[Perseptron->NumLayers-1].size();j++)
  {
   if(j == (int)exp_class)
	delta[j]=outputs[Perseptron->NumLayers-1][j]-Perseptron->MaxOutputValue;
   else
	delta[j]=outputs[Perseptron->NumLayers-1][j]-Perseptron->MinOutputValue;
  }

 // Корректируем веса всем слоям
 for(int l=Perseptron->NumLayers-1;l>=0;l--)
  {
   vector<vector<double> > *pweights=&(weights[l]);
   vector<vector<double> > *pdweights=&(dweights[l]);

   if(l<(int)Perseptron->NumLayers()-1)
    {
     delta.assign(pweights->size(),0);
	 for(int i=0;i<(int)outputs[l].size();i++)
	  {
	   for(int j=0;j<(int)outputs[l+1].size();j++)
		delta[i]+=delta_prev[j]*weights_prev[j][i];

	   delta[i]*=outputs[l][i]*(1-outputs[l][i]); // Проверить почему это за суммой!!!!
	  }
	}

   if(l > 0)
    {
     weights_prev.resize(pweights->size());
	 for(int i=0;i<(int)pweights->size();i++)
	  {
	   weights_prev[i].resize((*pweights)[0].size());
	   for(int j=0;j<(int)(*pweights)[0].size();j++)
        weights_prev[i][j]=(*pweights)[i][j];
      }
    }


   for(int i=0;i<(int)pweights->size();i++)
    {
     corr=alpha*delta[i];
	 for(int j=0;j<(int)(*pweights)[0].size()-1;j++)
	  {
	   if(l>0)
		(*pdweights)[i][j]=-TrainingRate*corr*outputs[l-1][j]+Moment*(*pdweights)[i][j];
	   else
		(*pdweights)[i][j]=-TrainingRate*corr*inputs[j]+Moment*(*pdweights)[i][j];

	   (*pweights)[i][j]+=(*pdweights)[i][j];
	  }

	 (*pdweights)[i][(*pdweights)[0].size()-1]=TrainingRate*corr*0.5+ // почему не считается разность с предыдущим шагом??
							  Moment*(*pdweights)[i][(*pdweights)[0].size()-1];
	 (*pweights)[i][(*pweights)[0].size()-1]+=(*pdweights)[i][(*pdweights)[0].size()-1];

	}

   delta_prev.resize(delta.size());
   for(int i=0;i<(int)delta.size();i++)
	delta_prev[i]=delta[i];
  }

 // Вычисляем ошибку
 E=0;
 for(int i=0;i<(int)outputs[Perseptron->NumLayers-1].size();i++)
  {
   if(i == (int)exp_class)
	E+=(outputs[Perseptron->NumLayers-1][i]-Perseptron->MaxOutputValue)*(outputs[Perseptron->NumLayers-1][i]-Perseptron->MaxOutputValue);
   else
	E+=(outputs[Perseptron->NumLayers-1][i]-Perseptron->MinOutputValue)*(outputs[Perseptron->NumLayers-1][i]-Perseptron->MinOutputValue);
  }
 return 0.5*E;
}

// Завершающие действия при завершении текущего обхода выборки
void UCRTeacherPerseptronBP::ACrSampleIterationCompleteAction(void)
{

}
// --------------------------

}
#endif
