#ifndef CNEURON_CPP
#define CNEURON_CPP

#include "CNeuron.h"
#include "CNetwork.h"
#include "CNLayer.h"
#include <iostream>
#include <fstream>


// --------------------------
// ������������ � �����������
// --------------------------
CNeuron::CNeuron(void)
{
}

CNeuron::~CNeuron(void)
{
}
// --------------------------


// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����� ���������� ������
int CNeuron::GetNumSourceField(void) const
{
 return NumSourceField;
}

bool CNeuron::SetNumSourceField(int value)
{
 if(NumSourceField == value)
  return true;

 NumSourceField = value;
 Ready = false;
 return true;
}

// ���������� ����������� ����
int CNeuron::GetX(void) const
{
 return X;
}
bool CNeuron::SetX(int value)
{
 if(X == value)
  return true;

 X = value;
 return true;
}
int CNeuron::GetY(void) const
{
 return Y;
}
bool CNeuron::SetY(int value)
{
 if(Y == value)
  return true;

 Y = value;
 return true;
}
int CNeuron::GetWidth(void) const
{
 return Width;
}
bool CNeuron::SetWidth(int value)
{
 if(Width == value)
  return true;

 Width = value;
 return true;
}
int CNeuron::GetHeight(void) const
{
 return Height;
}
bool CNeuron::SetHeight(int value)
{
 if(Height == value)
  return true;

 Height = value;
 return true;
}
// --------------------------



// --------------------------
// ������ ���������� �������
// --------------------------
// ������� ���������
double CNeuron::ActivationFunc(double x)
{
 return tanh(x);
}

// ����������� ������� ��������� �� ���������
double CNeuron::dActivationFunc(double x)
{
	return (1-x)*(1+x);
}

// ����� �������
double CNeuron::GetOutput(void) const
{
 return Output;
}

bool CNeuron::SetOutput(double value)
{
 if(Output==value)
  return true;

 Output=value;
 return true;
}
//���� �������
double CNeuron::GetInput(void) const
{
 return Input;
}

bool CNeuron::SetInput(double value)
{
 if(Input==value)
  return true;

 Input=value;
 return true;
}

// ���������� ����� �������, ������������� � ����� �� ��������� �����
double CNeuron::GetInputData(int field, int x, int y) const
{
 if(field < 0 || field >= int(SourceField.size()))
  return 0;

 CNField *src=SourceField[field];
 if(src)
  return src->GetNeuron(x+X,y+Y).Output;

 return 0;
}

// ���������� ���� ������� � ��������� ��������
void CNeuron::ResetTrainig(void)
{
 size_t i,j,k;
 double degWeights = NetworkOwner->GetDegWeights();

 if(!Ready)
  return;

 time_t tm;
 time(&tm);
 srand(static_cast<unsigned>(tm));
 for(k=0;k<Weights.size();k++)
  {
   for(i=0;i<Weights[k].size();i++)
    for(j=0;j<Weights[k][i].size();j++)
	 {
	   Weights[k][i][j]=((double)((rand()*100.0)/double(RAND_MAX))/100.0-0.5)*degWeights;
	 }
  }
}


//�������������� ���������� �����
bool CNeuron::SetWeights(vector<vector<vector<double> > > weights)
{
 if(Weights==weights)
  return true;

 Weights=weights;
 return true;
}

// ������ � ������� �����
vector<vector<vector<double> > >& CNeuron::GetWeights(void)
{
 return Weights;
}


// ���������� ����� �������� ������������ ������� � ������ ����� �������
size_t CNeuron::GetNumConnectedNeurons(void) const
{
 return ConnectedNeurons.size();
}

// ���������� ������ ������������ ������� � ������ ����� �������
CNeuronCoord& CNeuron::GetConnectedNeuron(size_t index)
{
 return ConnectedNeurons[index];
}

// --------------------------
// ������ ���������� �������
// --------------------------
// ��������� �� ������������ ����
CNetwork* CNeuron::GetNetworkOwner(void) const
{
 return NetworkOwner;
}

bool CNeuron::SetNetworkOwner(CNetwork* value)
{
 if(NetworkOwner == value)
  return true;

 Ready = false;

 NetworkOwner = value;
 return true;
}
// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool CNeuron::ADefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool CNeuron::ABuild(void)
{
 // �������������� ������
 SourceField.assign(size_t(NumSourceField),0);

 ConnectedNeurons.clear();

 Weights.resize(NumSourceField);
 PrevWeights.resize(NumSourceField);
// Delta.resize(NumSourceField);
 for(int k=0;k<NumSourceField;k++)
 {
  Weights[k].resize(Width);
  PrevWeights[k].resize(Width);
//  Delta[k].resize(Width);
  for(int i=0;i<Width;i++)
  {
   Weights[k][i].resize(Height);
   PrevWeights[k][i].resize(Height);
//   Delta[k].resize(Width);
  }
 }

 return true;
}

// ����� �������� �����.
bool CNeuron::AReset(void)
{
 Output=0;
 return true;
}


// ��������� ������ ����� �������
bool CNeuron::ACalculate(void)
{
   int NumL=int(SourceField.size());
   double sum=0;
   for(int k=0; k<NumL; k++) // ����
   {
	CNField *src=SourceField[k];

	if(src)
	{
	 for(int i=0; i<Width; i++) //
	  for(int j=0; j<Height; j++) //
	  {
	   double x=src->GetNeuron(i+X,j+Y).Output;
	   double weight=Weights[k][i][j];
	   sum+=x*weight;
	  }
	}
   }

 if(NumL>0 && SourceField[0])
 {
  Input=sum;
  Output=ActivationFunc(sum);
 }

 return true;
}

// --------------------------

#endif
