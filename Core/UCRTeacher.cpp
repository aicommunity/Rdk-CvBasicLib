#ifndef UCRTeacher_CPP
#define UCRTeacher_CPP

#include "UCRTeacher.h"

namespace RDK {

// --------------------------
// ������������ � �����������
// --------------------------
UCRTeacher::UCRTeacher(void)
:
 TrainEpsilon("TrainEpsilon",this,&UCRTeacher::SetTrainEpsilon),
 TrainMaxStepsNum("TrainMaxStepsNum",this,&UCRTeacher::SetTrainMaxStepsNum),
 TrainingRate("TrainingRate",this,&UCRTeacher::SetTrainingRate),
 Mode("Mode",this,&UCRTeacher::SetMode),

 TrainSample("TrainSample",this,0),
 TestSample("TestSample",this,1),
 CrossValidationSample("CrossValidationSample",this,2),
 Classifier("Classifier",this,3),

 CurrentSampleIteration("CurrentSampleIteration",this),
 TrainingError("TrainingError",this),
 MatrixTrainingError("MatrixTrainingError",this,0)

{
}

UCRTeacher::~UCRTeacher(void)
{
}
// --------------------------

// -----------------------------
// ������ ������� � ������
// -----------------------------
// -----------------------------

// -----------------------------
// ������ ���������� �������������� ����������
// -----------------------------
// ������������� ����������� ���������� ������ ��������
bool UCRTeacher::SetTrainEpsilon(const double &eps)
{
 if(eps <= 0)
  return false;

// TrainEpsilon=eps;
 return true;
}

// ������������� ���������� ����� ����� ��������
bool UCRTeacher::SetTrainMaxStepsNum(const size_t &lmaxsteps)
{
 return true;
}

bool UCRTeacher::SetMode(const int &value)
{
 return true;
}

// ������������� �������� �������� ����
bool UCRTeacher::SetTrainingRate(const double &tr)
{
 if(tr <= 0)
  return false;

// TrainingRate=tr;
 return true;
}
// -----------------------------

// ------------------------
// ������ �����
// ------------------------
// ��������� ��������� �� ����� 'name'
bool UCRTeacher::AFileLoad(fstream &file)
{
 return true;
}

// ��������� ��������� � ���� 'name'
bool UCRTeacher::AFileSave(fstream &file)
{
 return true;
}
// ------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UCRTeacher::ADefault(void)
{
 TrainEpsilon=0.001;
 TrainingRate=0.01;
 TrainMaxStepsNum=1;

 SetNumInputs(4);
 Mode=0;
 MatrixTrainingError->Assign(1,1,1.0);
 return ACrDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UCRTeacher::ABuild(void)
{
 return ACrBuild();
}

// ����� �������� �����.
bool UCRTeacher::AReset(void)
{
 CurrentSampleIteration=0;
 MatrixTrainingError->Assign(1,1,1.0);
 return ACrReset();
}

// ��������� ������ ����� ������� �� ������� ����.
bool UCRTeacher::ACalculate(void)
{
 ACrCalculate();
 switch(Mode)
 {
 case 0:
  if(Classifier)
   Classifier->SetActivity(true);
/*  if(TrainSample)
   TrainSample->Mode=0;
  if(CrossValidationSample)
   CrossValidationSample->Mode=0;
  if(TestSample)
   TestSample->Mode=1;*/
  //SetActivity(false);
 break;

 case 1:
  if(Classifier)
   Classifier->SetActivity(false);
  if(TrainSample)
   TrainSample->Mode=1;
  if(CrossValidationSample)
   CrossValidationSample->Mode=0;
  if(TestSample)
   TestSample->Mode=0;
  //SetActivity(true);

  Classifier->SetActivity(true);
  Train();
  Classifier->SetActivity(false);
 break;
 }

 return true;
}
// --------------------------

// --------------------------
// ������� ������ �������� ����
// --------------------------
// ����� �������� �������� � �������� ���������
void UCRTeacher::ResetTraining(void)
{
 ACrResetTraining();
}

// �������� ��������
void UCRTeacher::Train(void)
{
 int sample_index=TrainSample->CurrentSample;
 if(sample_index>=0)
 {
  size_t exp_class=TrainSample->GetSampleData()[TrainSample->CurrentSample].second;
  double err=TrainStep(exp_class);
  TrainingError=err;
  MatrixTrainingError->Assign(1,1,err);
 }
 if(CurrentSampleIteration<TrainSample->CurrentSampleIteration)
 {
  CurrentSampleIteration=TrainSample->CurrentSampleIteration;
  SampleIterationCompleteAction();
 }
}

// ���������� ���������� ��������� ��������
double UCRTeacher::TrainStep(size_t exp_class)
{
 return ACrTrainStep(exp_class);
}



// ����������� �������� ��� ���������� �������� ������ �������
void UCRTeacher::SampleIterationCompleteAction(void)
{
 ACrSampleIterationCompleteAction();
}

// --------------------------

}
#endif
