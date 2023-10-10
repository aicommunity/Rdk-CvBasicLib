#ifndef CNFIELD_CPP
#define CNFIELD_CPP

#include "CNField.h"
#include "CNetwork.h"
#include "CNLayer.h"
//#include "CNeuron.cpp"

//��� �������
//int CNField::ConvolutionStep=3;
// --------------------------
// ������������ � �����������
// --------------------------
CNField::CNField(void)
{
 //��� �������
 //ConvolutionStep=4;
}

CNField::~CNField(void)
{
}
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------

// ������� ���� ���� ����
int CNField::GetWidthField(void) const
{
 return WidthField;
}

int CNField::GetHeightField(void) const
{
 return HeightField;
}

bool CNField::SetWidthField(int width)
{
 if(WidthField == width)
  return true;

 WidthField = width;
 Ready=false;

 return true;
}

bool CNField::SetHeightField(int height)
{
 if(HeightField == height)
  return true;

 HeightField = height;
 Ready=false;

 return true;
}
/*
//��� �������
int CNField::GetConvolutionStep(void) const
{
	return  ConvolutionStep;
}

bool CNField::SetConvolutionStep(int value)
{
	if(ConvolutionStep == value)
	return true;
	ConvolutionStep = value;

	return true;
} */
// --------------------------
// ������ ���������� �������
// --------------------------
// ���������� ������ �� ������
CNeuron& CNField::GetNeuron(int i,int j)
{
 return Neurons[i][j];
}

// ��������� �� ������������ ����
CNLayer* CNField::GetOwner(void) const
{
 return Owner;
}

bool CNField::SetOwner(CNLayer* value)
{
 if(Owner == value)
  return true;

 Owner=value;
 return true;
}

bool CNField::SetOutput(vector<vector<double> > &output)
{
 if(!Build())
  return false;

 if(!WidthField || !HeightField)
  return true;

 if(int(output.size())<WidthField)
  return false;

 for(int i=0;i<WidthField;i++)
 {
  if(int(output[i].size())<HeightField)
   return false;

  for(int j=0;j<HeightField;j++)
   Neurons[i][j].SetOutput(output[i][j]);
 }
 return true;
}
// --------------------------

// --------------------------
// ������ ���������� ������
// --------------------------
// ���������� ���� ���� �������� � ��������� ��������
void CNField::ResetTrainig(void)
{
 for(size_t i=0;i<Neurons.size();i++)
  for(size_t j=0;j<Neurons[i].size();j++)
   Neurons[i][j].ResetTrainig();
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool CNField::ABuild(void)
{
 Neurons.resize(WidthField);
 for(int i=0;i<WidthField;i++)
  Neurons[i].resize(HeightField);

 int aConvolutionStep=Owner->GetConvolutionStep();

 if(Owner->GetSourceLayer())
 {
  // ���� �� ��������
  int y=0;
//  int height=0;

  for(int i=0;i<HeightField;i++)
  {
//   int width=0;
   int x=0;
   for(int j=0;j<WidthField;j++)
   {
	Neurons[i][j].SetNumSourceField(Owner->GetSourceLayer()->GetNumFields());
	Neurons[i][j].SetWidth(Owner->GetConvWidth());   // ��� ��������� CNetwork
	Neurons[i][j].SetHeight(Owner->GetConvHeight());  // ��� ��������� CNetwork

	Neurons[i][j].SetNetworkOwner(Owner->GetNetwork());
	if(!Neurons[i][j].Build())
	 return false;

	// ��� �� ��������� ������ � ���������� ������
    for(int k=0;k<int(Neurons[i][j].SourceField.size());k++)
	{
	 Neurons[i][j].SourceField[k]=&(Owner->GetSourceLayer()->GetField(k));

	 for(int n=0;n<Neurons[i][j].GetWidth();n++)
	  for(int m=0;m<Neurons[i][j].GetHeight();m++)
	  {
//	   int w=Neurons[i][j].GetWidth();
//	   int h=Neurons[i][j].GetHeight();

	   CNeuron &prev_neuron=Neurons[i][j].SourceField[k]->GetNeuron(n+x,m+y);
	   CNeuronCoord coord;
	   coord.field=FieldIndex;
	   coord.x=i;
	   coord.y=j;
	   prev_neuron.ConnectedNeurons.push_back(coord);
	  }
	}

	// ��� ��������� x,y...
	Neurons[i][j].SetX(y);
	Neurons[i][j].SetY(x);
  //	width=Neurons[i][j].GetWidth();
	x=x+aConvolutionStep;
   }
//   height=width;
   y=y+aConvolutionStep;
  }
 }
 else // ����� �� �� 0 ����
 {
  // ���� �� ��������
  int y=0;
//  int height=0;
  for(int i=0;i<WidthField;i++)
  {
  // int width=0;
   int x=0;
   for(int j=0;j<HeightField;j++)
   {
	Neurons[i][j].SetNumSourceField(1);
	Neurons[i][j].SetWidth(Owner->GetConvWidth());   // ����� ������� ���� �������
	Neurons[i][j].SetHeight(Owner->GetConvHeight());  // ����� ������� ���� �������

	Neurons[i][j].SetNetworkOwner(Owner->GetNetwork());
	if(!Neurons[i][j].Build())
	 return false;

	// ��� �� ��������� ������ � ���������� ������
	for(size_t k=0;k<Neurons[i][j].SourceField.size();k++)
	{
	 Neurons[i][j].SourceField[k]=0;
	}

	// ��� ��������� x,y...
	Neurons[i][j].SetX(y);
	Neurons[i][j].SetY(x);
	x=x+aConvolutionStep;
  //	width=Neurons[i][j].GetWidth();
   }
   y=y+aConvolutionStep;
//   height=width;
  }
 }

 return true;
}


// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool CNField::ADefault(void)
{
 //��� �������
 //ConvolutionStep=4;

 return true;
}
// ����� �������� �����.
bool CNField::AReset(void)
{
 for(int i=0;i<WidthField;i++)
	for(int j=0;j<HeightField;j++)
 {
  if(!Neurons[i][j].Reset())
   return false;
 }
 return true;
}
// ��������� ������ ����� �������
bool CNField::ACalculate(void)
{
 for(int i=0;i<WidthField;i++)
  for(int j=0;j<HeightField;j++)
 {
  if(!Neurons[i][j].Calculate())
   return false;
 }
 return true;
}
// --------------------------

#endif

