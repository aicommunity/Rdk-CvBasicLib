#ifndef CNETWORK_CPP
#define CNETWORK_CPP

#include "CNetwork.h"
//#include "CNLayer.cpp"


// --------------------------
// ������������ � �����������
// --------------------------
CNetwork::CNetwork(void)
{
}

CNetwork::~CNetwork(void)
{
}
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����� ����
const int& CNetwork::GetNumLayers(void) const
{
 return NumLayers;
}

bool CNetwork::SetNumLayers(const int& value)
{
 if(NumLayers == value)
  return true;

 NumLayers = value;
 Ready=false;

 return true;
}

const vector<int>& CNetwork::GetNetworkConvStep(void) const
{
 return NetworkConvolutionStep;
}

bool CNetwork::SetNetworkConvStep(const vector<int>& value)
{
 if(NetworkConvolutionStep==value)
  return true;

 NetworkConvolutionStep=value;
 Ready=false;
 return true;
}

const vector<int>& CNetwork::GetNetworkConvHeight(void) const
{
 return NetworkConvHeight;
}

bool CNetwork::SetNetworkConvHeight(const vector<int>& value)
{
 if(NetworkConvHeight==value)
  return true;

 NetworkConvHeight=value;
 Ready=false;
 return true;
}

const vector<int>& CNetwork::GetNetworkConvWidth(void) const
{
 return NetworkConvWidth;
}

bool CNetwork::SetNetworkConvWidth(const vector<int>& value)
{
 if(NetworkConvWidth==value)
  return true;

 NetworkConvWidth=value;
 Ready=false;
 return true;
}

const vector<int>& CNetwork::GetNetworkNumFields(void) const
{
 return NetworkNumFields;
}

bool CNetwork::SetNetworkNumFields(const vector<int>& value)
{
 if(NetworkNumFields==value)
  return true;

 NetworkNumFields=value;
 Ready=false;
 return true;
}

// ������� �������� �����������
const int& CNetwork::GetInputWidth(void) const
{
 return InputWidth;
}

bool CNetwork::SetInputWidth(const int &value)
{
 if(InputWidth==value)
  return true;

 InputWidth=value;
 Ready=false;
 return true;
}

const int& CNetwork::GetInputHeight(void) const
{
 return InputHeight;
}

bool CNetwork::SetInputHeight(const int &value)
{
 if(InputHeight==value)
  return true;

 InputHeight=value;
 Ready=false;
 return true;
}

// �������� ��������
const double& CNetwork::GetEta(void) const
{
 return Eta;
}

bool CNetwork::SetEta(const double& value)
{
 if(Eta==value)
  return true;

 Eta=value;
 Ready=false;
 return true;
}

//������� ������� ������
const double& CNetwork::GetError(void) const
{
 return Error;
}

bool CNetwork::SetError(double value)
{
 if(Error == value)
  return true;
 Error=value;
// Ready=false;
 return true;
}

// ������� �����
const double& CNetwork::GetDegWeights(void) const
{
 return DegWeights;
}

bool CNetwork::SetDegWeights(double value)
{
 if(DegWeights == value)
  return true;

 DegWeights = value;
 return true;
}
// --------------------------

// --------------------------
// ������ ���������� �������
// --------------------------
// ���������� ���� �� �������
CNLayer& CNetwork::GetLayer(int index)
{
 return Layers[index];
}
// --------------------------

// --------------------------
// ������ ���������� ������
// --------------------------
/*
bool CNetwork::SetInputImage(const UBitmap &input)
{
 if(input.GetColorModel() != ubmY8)
  return false;

 InputImage.SetRes(InputWidth,InputHeight,ubmY8);
 UBResizeEdges(input,InputImage);
 return true;
} */

bool CNetwork::SetFieldOutput(int layer, int field, vector<vector<double> > &output)
{
 if(!Build())
  return false;

 if(layer>=NumLayers || layer<0)
  return false;

 if(field<0 || field>=Layers[layer].GetNumFields())
  return false;

 return Layers[layer].GetField(field).SetOutput(output);
}
// --------------------------


// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool CNetwork::ADefault(void)
{
 DegWeights=0.1;
 NumLayers=6;
 Eta=0.05;
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool CNetwork::ABuild(void)
{
 Layers.resize(NumLayers);

 NetworkConvolutionStep.resize(NumLayers);
 NetworkConvHeight.resize(NumLayers);
 NetworkConvWidth.resize(NumLayers);
 NetworkNumFields.resize(NumLayers);

 for(int i=0; i<NumLayers; i++)
 {
  if(i==0)
  {
   Layers[i].SetConvolutionStep(NetworkConvolutionStep[i]);
   Layers[i].SetConvHeight(NetworkConvHeight[i]);
   Layers[i].SetConvWidth(NetworkConvWidth[i]);
   Layers[i].SetNumFields(NetworkNumFields[i]);
   Layers[i].SetSourceLayer(0);
   Layers[i].SetFieldWidth(InputWidth);
   Layers[i].SetFieldHeight(InputHeight);
   Layers[i].SetLayerFlag(0);
  }

  if(i>0)
  {
   Layers[i].SetConvolutionStep(NetworkConvolutionStep[i]);
   Layers[i].SetConvHeight(NetworkConvHeight[i]);
   Layers[i].SetConvWidth(NetworkConvWidth[i]);
   Layers[i].SetNumFields(NetworkNumFields[i]);
   Layers[i].SetSourceLayer(&Layers[i-1]);
   Layers[i].SetLayerFlag(0);
  }

  Layers[i].SetNetwork(this);
  if(!Layers[i].Build())
   return false;
 }
 /*
 // ���� �� �����
 // �������������� ����
 for(int i=0;i<NumLayers;i++)
 {
  // ������ ��������� �����

  if(i==0)
  {
   Layers[i].SetConvolutionStep(1);
   Layers[i].SetConvHeight(1);
   Layers[i].SetConvWidth(1);
   Layers[i].SetNumFields(1);
   Layers[i].SetSourceLayer(0);
   Layers[i].SetLayerFlag(0);
   //Layers[i].GetField(0).SetConvolutionStep(2);
  }
  if(i==1)
  {
   Layers[i].SetConvolutionStep(1);
   Layers[i].SetConvHeight(5);
   Layers[i].SetConvWidth(5);
   Layers[i].SetNumFields(6); // ��� ����� �������� 6
   Layers[i].SetSourceLayer(&Layers[i-1]);
   Layers[i].SetLayerFlag(0);
   //Layers[i].GetField(0).SetConvolutionStep(2);
  }
  if(i==2)
  {
   Layers[i].SetConvolutionStep(2);
   Layers[i].SetConvHeight(2);
   Layers[i].SetConvWidth(2);
   Layers[i].SetNumFields(6); // ��� ����� �������� 6
   Layers[i].SetSourceLayer(&Layers[i-1]);
   Layers[i].SetLayerFlag(0);
  // Layers[i].GetField(0).SetConvolutionStep(2);
  }
	if(i==3)
  {
   Layers[i].SetConvolutionStep(1);
   Layers[i].SetConvHeight(5);
   Layers[i].SetConvWidth(5);
   Layers[i].SetNumFields(16); // ��� ����� ��������  16
   Layers[i].SetSourceLayer(&Layers[i-1]);
   Layers[i].SetLayerFlag(0);
   //Layers[i].GetField(0).SetConvolutionStep(1);
  }
	if(i==4)
  {
   Layers[i].SetConvolutionStep(2);
   Layers[i].SetConvHeight(2);
   Layers[i].SetConvWidth(2);
   Layers[i].SetNumFields(6); // ��� ����� ��������    6
   Layers[i].SetSourceLayer(&Layers[i-1]);
   Layers[i].SetLayerFlag(0);
   //Layers[i].GetField(0).SetConvolutionStep(1);
  }
	if(i==5)
  {
   Layers[i].SetConvolutionStep(1);
   Layers[i].SetConvHeight(5);
   Layers[i].SetConvWidth(5);
   Layers[i].SetNumFields(5); // ��� ����� ��������
   Layers[i].SetSourceLayer(&Layers[i-1]);
   Layers[i].SetLayerFlag(0);
   //Layers[i].GetField(0).SetConvolutionStep(1);
  }
   */
 return true;
}

// ����� �������� �����.
bool CNetwork::AReset(void)
{
 for(int i=0;i<NumLayers;i++)
 {
  if(!Layers[i].Reset())
   return false;
 }
 return true;
}

// ��������� ������ ����� �������
bool CNetwork::ACalculate(void)
{
 for(int i=1;i<NumLayers;i++)
 {
  if(!Layers[i].Calculate())
   return false;

// ������ ����� � ��� ���� �� �����
 /*
  string filename="layer";
  filename+=sntoa(i);
  filename+=".txt";


  fstream fs(filename.c_str(), ios::out| ios::trunc);

  if(!fs)
   return false;

  for(int n=0;n<Layers[i].GetNumFields();n++)
  {
	 CNField &field=Layers[i].GetField(n);


   for(int m=0;m<field.GetHeightField();m++)
   {
	for(int k=0;k<field.GetWidthField();k++)
	{
	 fs<<field.GetNeuron(m,k).GetOutput()<<" ";
	}
	fs<<"\n";
   }
   fs<<"\n\n";

  }

  fs.close();    */
 }
 return true;
}

void CNetwork::ResetTraining(void)
{
 for(int i=0;i<NumLayers;i++)
 {
  Layers[i].ResetTrainig();
 }
}

// ��������
double CNetwork::ATrain(int exp_class)
{
 if(!Ready)
  return false;

  //������ ���
  Calculate();

 if(!NumLayers)
  return true;

  //������ �������� � ��������� ����
{
 int lastLayerNumFields=GetLayer(NumLayers-1).GetNumFields();
 int lastLayerFieldWidth=GetLayer(NumLayers-1).GetField(0).GetWidthField();
 int lastLayerFieldHeight=GetLayer(NumLayers-1).GetField(0).GetHeightField();

 for(int i=0; i<lastLayerNumFields; i++)
 {
  for(int j=0; j<lastLayerFieldWidth; j++)
  {
   for(int k=0; k<lastLayerFieldHeight; k++)
	{
	 CNeuron &neuron=GetLayer(NumLayers-1).GetField(i).GetNeuron(j,k);
	 double out=neuron.GetOutput();

	 if(i == exp_class)
	 {

		 neuron.Delta=(1.0-out)*neuron.dActivationFunc(out);
	 }
	 else
	 {

		 neuron.Delta=(-1.0-out)*neuron.dActivationFunc(out);
	 }
	}
  }
 }
}

  //��������� ����� �� ���� �����
  for(int l=NumLayers-1; l>0; l--)
   {
	if(l == NumLayers-1)
	 {
	  int conv_width=GetLayer(l).GetField(0).GetNeuron(0,0).GetWidth();
	  int conv_height=GetLayer(l).GetField(0).GetNeuron(0,0).GetHeight();

	  for(int q=0;q<GetLayer(l).GetNumFields();q++)
	   for(int n=0;n<GetLayer(l).GetField(q).GetWidthField();n++)
		for(int m=0;m<GetLayer(l).GetField(q).GetHeightField();m++)
		{
		 CNeuron& neuron=GetLayer(l).GetField(q).GetNeuron(n,m);
		 vector<vector<vector<double> > >& pWeights=neuron.GetWeights();
		 vector<vector<vector<double> > >& pPrevWeights=neuron.PrevWeights;
		 for(int i=0; i<GetLayer(l-1).GetNumFields(); i++)
		 {
		  for(int j=0; j<conv_width; j++)
		  {
		   for(int k=0; k<conv_height; k++)
			{
				double inputSignal=neuron.GetInputData(i,j,k);
				pPrevWeights[i][j][k]=pWeights[i][j][k];
				pWeights[i][j][k]+=Eta*neuron.Delta*inputSignal;
			}
		  }
		 }

	   }
	 }
	else
	 {
	  //������ �������� � �������� ����
	  int LayerNumFields=GetLayer(l).GetNumFields();
	  int LayerFieldWidth=GetLayer(l).GetField(0).GetWidthField();
	  int LayerFieldHeight=GetLayer(l).GetField(0).GetHeightField();
	  for(int i=0; i<LayerNumFields; i++)
	  {
		for(int j=0; j<LayerFieldWidth; j++)
		{
		 for(int k=0; k<LayerFieldHeight; k++)
		 {
		  CNeuron &neuron=GetLayer(l).GetField(i).GetNeuron(j,k);
		  double out=neuron.GetOutput();
		  double sum=0;
          for(int q=0;q<int(neuron.GetNumConnectedNeurons());q++)
		  {
		   CNeuronCoord coord=neuron.GetConnectedNeuron(q);
		   CNeuron &connected_neuron=GetLayer(l+1).GetField(coord.field).GetNeuron(coord.x, coord.y);

		   int cx=coord.x-connected_neuron.GetX();
		   int cy=coord.y-connected_neuron.GetY();
		   if( (cx>=0)&&(cy>=0) )
		   sum+=connected_neuron.Delta*connected_neuron.PrevWeights[i][cx][cy];
		  }

		  neuron.Delta=sum*neuron.dActivationFunc(out);
		 }
		}
 	  }


	  int conv_width=GetLayer(l).GetField(0).GetNeuron(0,0).GetWidth();
	  int conv_height=GetLayer(l).GetField(0).GetNeuron(0,0).GetHeight();

	  for(int q=0;q<GetLayer(l).GetNumFields();q++)
	   for(int n=0;n<GetLayer(l).GetField(q).GetWidthField();n++)
		for(int m=0;m<GetLayer(l).GetField(q).GetHeightField();m++)
		{
		 CNeuron& neuron=GetLayer(l).GetField(q).GetNeuron(n,m);
		 vector<vector<vector<double> > >& pWeights=neuron.GetWeights();
		 vector<vector<vector<double> > >& pPrevWeights=neuron.PrevWeights;
		 for(int i=0; i<GetLayer(l-1).GetNumFields(); i++)
		  for(int j=0; j<conv_width; j++)
		   for(int k=0; k<conv_height; k++)
			{
				double inputSignal=neuron.GetInputData(i,j,k);
				pPrevWeights[i][j][k]=pWeights[i][j][k];
				pWeights[i][j][k]+=Eta*neuron.Delta*inputSignal;
			}

	   }
	 }
   }
 // ���������� ������
{
 int lastLayerNumFields=GetLayer(NumLayers-1).GetNumFields();
 int lastLayerFieldWidth=GetLayer(NumLayers-1).GetField(0).GetWidthField();
 int lastLayerFieldHeight=GetLayer(NumLayers-1).GetField(0).GetHeightField();

 double err=0; // ����� ������� ������ ����

 for(int i=0; i<lastLayerNumFields; i++)
 {
  for(int j=0; j<lastLayerFieldWidth; j++)
  {
   for(int k=0; k<lastLayerFieldHeight; k++)
	{
	 CNeuron &neuron=GetLayer(NumLayers-1).GetField(i).GetNeuron(j,k);
	 double out=neuron.GetOutput();

	 if(i == exp_class)
	 {
		 err+=((1.0-out)*(1.0-out));

	 }
	 else
	 {
		 err+=((-1.0-out)*(-1.0-out));

	 }
	}
  }
 }

 err*=0.5;
 SetError(err);
}

 return 0;
}

// --------------------------

#endif



