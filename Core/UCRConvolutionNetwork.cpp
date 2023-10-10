#ifndef UCR_CONVOLUTION_NETWORK_CPP
#define UCR_CONVOLUTION_NETWORK_CPP

#include "UCRConvolutionNetwork.h"
//#include "UCVNetwork/CNetwork.cpp"

namespace RDK {

using namespace std;

// --------------------------
// ������������ � �����������
// --------------------------
UCRConvolutionNetwork::UCRConvolutionNetwork(void)
{
 AddLookupProperty("NetworkNumLayers",ptPubParameter, new UVProperty<int,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetNetworkNumLayers,&UCRConvolutionNetwork::GetNetworkNumLayers));
 AddLookupProperty("NetworkConvStep",ptPubParameter, new UVProperty<vector<int>,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetNetworkConvStep,&UCRConvolutionNetwork::GetNetworkConvStep));
 AddLookupProperty("NetworkConvHeight",ptPubParameter, new UVProperty<vector<int>,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetNetworkConvHeight,&UCRConvolutionNetwork::GetNetworkConvHeight));
 AddLookupProperty("NetworkConvWidth",ptPubParameter, new UVProperty<vector<int>,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetNetworkConvWidth,&UCRConvolutionNetwork::GetNetworkConvWidth));
 AddLookupProperty("NetworkNumFields",ptPubParameter, new UVProperty<vector<int>,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetNetworkNumFields,&UCRConvolutionNetwork::GetNetworkNumFields));
 //AddLookupProperty("NetworkEta",ptPubParameter, new UVProperty<double,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetNetworkEta,&UCRConvolutionNetwork::GetNetworkEta));
 AddLookupProperty("DegWeights",ptPubParameter, new UVProperty<double,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetNetworkDegWeights,&UCRConvolutionNetwork::GetNetworkDegWeights));
 AddLookupProperty("InputWidth",ptPubParameter, new UVProperty<int,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetInputWidth,&UCRConvolutionNetwork::GetInputWidth));
 AddLookupProperty("InputHeight",ptPubParameter, new UVProperty<int,UCRConvolutionNetwork>(this,&UCRConvolutionNetwork::SetInputHeight,&UCRConvolutionNetwork::GetInputHeight));
}

UCRConvolutionNetwork::~UCRConvolutionNetwork(void)
{

}
// -----------------------------
// ������ ������� � ������ ������
// -----------------------------
// ������ � ����
CNetwork& UCRConvolutionNetwork::GetNetwork(void)
{
 return CVNetwork;
}
// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����� ����
const int& UCRConvolutionNetwork::GetNetworkNumLayers(void) const
{
 return CVNetwork.GetNumLayers();
}

bool UCRConvolutionNetwork::SetNetworkNumLayers(const int &value)
{
 CVNetwork.SetNumLayers(value);
 return true;
}

// ��� ���� ������� ��� ������� ����
const vector<int>& UCRConvolutionNetwork::GetNetworkConvStep(void) const
{
 return CVNetwork.GetNetworkConvStep();
}

bool UCRConvolutionNetwork::SetNetworkConvStep(const vector<int>& value)
{
 CVNetwork.SetNetworkConvStep(value);
 return true;
}

// ������ ���� ������� ��� ������� ����
const vector<int>& UCRConvolutionNetwork::GetNetworkConvHeight(void) const
{
 return CVNetwork.GetNetworkConvHeight();
}

bool UCRConvolutionNetwork::SetNetworkConvHeight(const vector<int>& value)
{
 CVNetwork.SetNetworkConvHeight(value);
 return true;
}

// ������ ���� ������� ��� ������� ����
const vector<int>& UCRConvolutionNetwork::GetNetworkConvWidth(void) const
{
 return CVNetwork.GetNetworkConvWidth();
}

bool UCRConvolutionNetwork::SetNetworkConvWidth(const vector<int>& value)
{
 CVNetwork.SetNetworkConvWidth(value);
 return true;
}

// ������ ����� �������� ��� ������� ����
const vector<int>& UCRConvolutionNetwork::GetNetworkNumFields(void) const
{
 return CVNetwork.GetNetworkNumFields();
}

bool UCRConvolutionNetwork::SetNetworkNumFields(const vector<int>& value)
{
 CVNetwork.SetNetworkNumFields(value);
 return true;
}

// �������� �������� ��������
const double& UCRConvolutionNetwork::GetNetworkEta(void) const
{
 return CVNetwork.GetEta();
}

// ������� ������� ������������� ����
const double& UCRConvolutionNetwork::GetNetworkDegWeights(void) const
{
 return CVNetwork.GetDegWeights();
}

bool UCRConvolutionNetwork::SetNetworkDegWeights(const double& value)
{
 return CVNetwork.SetDegWeights(value);
}

// ������� �������� �����������
const int& UCRConvolutionNetwork::GetInputWidth(void) const
{
 return CVNetwork.GetInputWidth();
}

bool UCRConvolutionNetwork::SetInputWidth(const int &value)
{
 CVNetwork.SetInputWidth(value);
 return true;
}

const int& UCRConvolutionNetwork::GetInputHeight(void) const
{
 return CVNetwork.GetInputHeight();
}

bool UCRConvolutionNetwork::SetInputHeight(const int &value)
{
 CVNetwork.SetInputHeight(value);
 return true;
}

// --------------------------
// ������ ���������� �������
// --------------------------
// ��������������� ������� ������ � ������� ����� � ��������� � ������� ���� ����
bool UCRConvolutionNetwork::LoadInputData(double *input, int size)
{
 if(size<(GetInputWidth()*GetInputHeight()))
  return false;

 size_t index=0;
 vector<vector<double> > temp;

 temp.resize(GetInputHeight());
 for(size_t i=0; i<temp.size(); i++)
 {
  temp[i].resize(GetInputWidth());
 }

 for(int i=0; i<GetInputHeight(); i++)
 {
  for(int j=0; j<GetInputWidth(); j++)
  {
   temp[i][j]=input[index];
   index++;
  }
 }

 CVNetwork.SetFieldOutput(0, 0, temp);
 return true;
}

// ��������������� �������� ���� ����� �������� ���� � �������� ������
vector<double> UCRConvolutionNetwork::ConversionOutputData(int size)
{
 vector<double> temp;

 temp.resize(size);
 for(int i=0; i<size; i++)
 {
  temp[i]=CVNetwork.GetLayer(CVNetwork.GetNumLayers()-1).GetField(i).GetNeuron(0,0).GetOutput();
 }

 return temp;
}
// ------------------------
// ������ �����
// ------------------------
// ��������� ��������� ����� �� ����� � ������ 'name'
bool UCRConvolutionNetwork::AFileLoad(fstream &file)
{
int i,j,k,n,m,l,o;

 double eta;
 int inputWidth;
 int inputHeight;
 int numlayers;
 int numclasses;
 vector<int> convStep;
 vector<int> convHeight;
 vector<int> convWidth;
 vector<int> numFields;

 int aFieldsWidth;
 int aFieldsHeight;
 vector<vector<vector<double> > > aWeights;


 file.read((char*)&numlayers,sizeof(numlayers));
 file.read((char*)&numclasses,sizeof(numclasses));
 file.read((char*)&eta,sizeof(eta));
 file.read((char*)&inputWidth,sizeof(inputWidth));
 file.read((char*)&inputHeight,sizeof(inputHeight));

 CVNetwork.SetNumLayers(numlayers);
 NumClasses=numclasses;
 CVNetwork.SetEta(eta);
 CVNetwork.SetInputWidth(inputWidth);
 CVNetwork.SetInputHeight(inputHeight);

 convStep.resize(numlayers);
 convHeight.resize(numlayers);
 convWidth.resize(numlayers);
 numFields.resize(numlayers);

 for(i=0; i<numlayers; i++)
 {
  file.read((char*)&(convStep[i]),sizeof(convStep[i]));
  file.read((char*)&(convHeight[i]),sizeof(convHeight[i]));
  file.read((char*)&(convWidth[i]),sizeof(convWidth[i]));
  file.read((char*)&(numFields[i]),sizeof(numFields[i]));
 }

 CVNetwork.SetNetworkConvStep(convStep);
 CVNetwork.SetNetworkConvHeight(convHeight);
 CVNetwork.SetNetworkConvWidth(convWidth);
 CVNetwork.SetNetworkNumFields(numFields);

 CVNetwork.Build();

 for(n=0; n<numlayers; n++)
 {
  int aNumFields=CVNetwork.GetLayer(n).GetNumFields();
  for(m=0; m<aNumFields; m++)
  {
   aFieldsWidth=CVNetwork.GetLayer(n).GetField(m).GetWidthField();
   aFieldsHeight=CVNetwork.GetLayer(n).GetField(m).GetHeightField();

   for(l=0; l<aFieldsWidth; l++)
   {
	for(o=0; o<aFieldsHeight; o++)
	{
	 aWeights=CVNetwork.GetLayer(n).GetField(m).GetNeuron(l,o).GetWeights();
	 for(k=0; k<int(aWeights.size()); k++)
	 {
	  for(i=0; i<int(aWeights[k].size()); i++)
	  {
	   for(j=0; j<int(aWeights[k][i].size()); j++)
	   file.read((char*)&(aWeights[k][i][j]),sizeof(aWeights[k][i][j]));
	  }
	 }

     CVNetwork.GetLayer(n).GetField(m).GetNeuron(l,o).SetWeights(aWeights);
	}
   }
  }
 }

 return true;
}

// ��������� ��������� ����� � ���� � ������ 'name'
bool UCRConvolutionNetwork::AFileSave(fstream &file)
{
 int i,j,k,n,m,l,o;

 double eta;
 int inputWidth;
 int inputHeight;
 int numlayers;
 vector<int> convStep;
 vector<int> convHeight;
 vector<int> convWidth;
 vector<int> numFields;

 vector<vector<vector<double> > > aWeights;

 int temp;
 temp=GetNetworkNumLayers();
 file.write((char*)&temp,sizeof(temp));
 temp=GetOutputDataSize(0)[1];
 file.write((char*)&temp,sizeof(temp));
 eta=GetNetworkEta();
 file.write((char*)&eta,sizeof(eta));
 inputWidth=GetInputWidth();
 file.write((char*)&inputWidth,sizeof(inputWidth));
 inputHeight=GetInputHeight();
 file.write((char*)&inputHeight,sizeof(inputHeight));

 numlayers=GetNetworkNumLayers();
 convStep=GetNetworkConvStep();
 convHeight=GetNetworkConvHeight();
 convWidth=GetNetworkConvWidth();
 numFields=GetNetworkNumFields();

 for(i=0; i<numlayers; i++)
 {
  file.write((char*)&(convStep[i]),sizeof(convStep[i]));
  file.write((char*)&(convHeight[i]),sizeof(convHeight[i]));
  file.write((char*)&(convWidth[i]),sizeof(convWidth[i]));
  file.write((char*)&(numFields[i]),sizeof(numFields[i]));
 }

 for(n=0; n<numlayers; n++)
 {
  int aNumFields=CVNetwork.GetLayer(n).GetNumFields();
  for(m=0; m<aNumFields; m++)
  {
   int aFieldsWidth=CVNetwork.GetLayer(n).GetField(m).GetWidthField();
   int aFieldsHeight=CVNetwork.GetLayer(n).GetField(m).GetHeightField();

   for(l=0; l<aFieldsWidth; l++)
   {
	for(o=0; o<aFieldsHeight; o++)
	{
	 aWeights=CVNetwork.GetLayer(n).GetField(m).GetNeuron(l,o).GetWeights();
	 for(k=0; k<int(aWeights.size()); k++)
	 {
	  for(i=0; i<int(aWeights[k].size()); i++)
	  {
	   for(j=0; j<int(aWeights[k][i].size()); j++)
	   file.write((char*)&(aWeights[k][i][j]),sizeof(aWeights[k][i][j]));
	  }
	 }
	}
   }
  }
 }

 return true;
}
// ------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
UCRConvolutionNetwork* UCRConvolutionNetwork::New(void)
{
 return new UCRConvolutionNetwork;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UCRConvolutionNetwork::ACRDefault(void)
{
 CVNetwork.Default();
 CVNetwork.SetNumLayers(2);
 SetInputWidth(1);
 SetInputHeight(1);


 SetOutputDataSize(0,MMatrixSize(1,2));
 MinOutputValue=-1.0;
 MaxOutputValue=1.0;

 vector<double> minrate,maxrate;
 minrate.assign(GetOutputDataSize(0)[1],10);
 maxrate.assign(GetOutputDataSize(0)[1],90);

 MinQualityRate=minrate;
 MaxQualityRate=maxrate;

 TrainFileName = "NetworkParams.txt";
 ResultsFileName = "NetworkResults.txt";

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UCRConvolutionNetwork::ACRBuild(void)
{
 SetOutputDataSize(0,MMatrixSize(1,NumClasses.v));
 CVNetwork.Build();

 return true;
}

// ����� �������� �����.
bool UCRConvolutionNetwork::ACRReset(void)
{
 CVNetwork.Reset();

 return true;
}

// ��������� ������ ����� ������� �� ������� ����.
bool UCRConvolutionNetwork::ACRCalculate(void)
{
 if(!LoadInputData(GetInputData(0)->Double, GetInputDataSize(0)[1]))
  return false;

 CVNetwork.Calculate();
 ModifiedFlag=true;

 //if(GetOutputDataSize(0) > 0 && int(GetOutputDataSize(0)) == CVNetwork.GetLayer(CVNetwork.GetNumLayers()).GetNumFields())
 //{
  vector<double> temp=ConversionOutputData(NumClasses);
  Result->Resize(int(temp.size()),1);
  for(int i=0; i<Result->GetRows(); i++)
  {
   (*Result)(i,0)=temp[i];
  }
  //memcpy(POutputData[0].Void, &temp, GetOutputDataSize(0)*sizeof(double));
 //}

 return true;
}
// --------------------------

// --------------------------
// ������� ������ �������� ����
// --------------------------
// ����� �������� �������� � �������� ���������
void UCRConvolutionNetwork::AResetTraining(void)
{
 CVNetwork.ResetTraining();

 return;
}

// ����������� �������� �� �������� �������
double UCRConvolutionNetwork::Train(size_t exp_class)
{
 CVNetwork.ATrain(int(exp_class));
 ModifiedFlag=true;

 return CVNetwork.GetError();
}
// --------------------------
}
#endif
