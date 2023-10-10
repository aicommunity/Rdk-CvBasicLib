#ifndef UCRTeacherPerseptronBP_CPP
#define UCRTeacherPerseptronBP_CPP

#include "UCRTeacherPerseptronBP.h"

namespace RDK {

// --------------------------
// ������������ � �����������
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
// ������ ������� � ������
// -----------------------------
// -----------------------------

// -----------------------------
// ������ ���������� �������������� ����������
// -----------------------------
bool UCRTeacherPerseptronBP::SetMode(const int &value)
{
 return true;
}

// ������������� ������ ����
bool UCRTeacherPerseptronBP::SetMoment(const double &m)
{
 if(m < 0 || m > 1.0)
  return false;

 return true;
}

// -----------------------------

// ------------------------
// ������ �����
// ------------------------
// ��������� ��������� �� ����� 'name'
bool UCRTeacherPerseptronBP::AFileLoad(fstream &file)
{
 return true;
}

// ��������� ��������� � ���� 'name'
bool UCRTeacherPerseptronBP::AFileSave(fstream &file)
{
 return true;
}
// ------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
UCRTeacherPerseptronBP* UCRTeacherPerseptronBP::New(void)
{
 return new UCRTeacherPerseptronBP;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
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

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UCRTeacherPerseptronBP::ACrBuild(void)
{

 return true;
}

// ����� �������� �����.
bool UCRTeacherPerseptronBP::ACrReset(void)
{
 time_t tm;
 time(&tm);
 srand(static_cast<unsigned>(tm));

 return true;
}

// ��������� ������ ����� ������� �� ������� ����.
bool UCRTeacherPerseptronBP::ACrCalculate(void)
{
 return true;
}
// --------------------------

// --------------------------
// ������� ������ �������� ����
// --------------------------
// ����� �������� �������� � �������� ���������
void UCRTeacherPerseptronBP::ACrResetTraining(void)
{
 Perseptron->NumClasses=TrainSample->NumClasses;
 Perseptron->AutoSetLayerInputs=false;
 Perseptron->Build();
 Perseptron->ResetTraining();
}

// ���������� ���������� ��������� ��������
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

 // �������� ������������� �������
 Perseptron->Calculate();

 double alpha=Perseptron->Alpha;

 // ������������ �������� ��������� ����
 delta.assign(weights[Perseptron->NumLayers-1].size(),0);
 for(int j=0;j<(int)weights[Perseptron->NumLayers-1].size();j++)
  {
   if(j == (int)exp_class)
	delta[j]=outputs[Perseptron->NumLayers-1][j]-Perseptron->MaxOutputValue;
   else
	delta[j]=outputs[Perseptron->NumLayers-1][j]-Perseptron->MinOutputValue;
  }

 // ������������ ���� ���� �����
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

	   delta[i]*=outputs[l][i]*(1-outputs[l][i]); // ��������� ������ ��� �� ������!!!!
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

	 (*pdweights)[i][(*pdweights)[0].size()-1]=TrainingRate*corr*0.5+ // ������ �� ��������� �������� � ���������� �����??
							  Moment*(*pdweights)[i][(*pdweights)[0].size()-1];
	 (*pweights)[i][(*pweights)[0].size()-1]+=(*pdweights)[i][(*pdweights)[0].size()-1];

	}

   delta_prev.resize(delta.size());
   for(int i=0;i<(int)delta.size();i++)
	delta_prev[i]=delta[i];
  }

 // ��������� ������
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

// ����������� �������� ��� ���������� �������� ������ �������
void UCRTeacherPerseptronBP::ACrSampleIterationCompleteAction(void)
{

}
// --------------------------

}
#endif
