#ifndef CNLAYER_CPP
#define CNLAYER_CPP

#include "CNLayer.h"
//#include "CNField.cpp"

// --------------------------
// ������������ � �����������
// --------------------------
CNLayer::CNLayer(void)
{
}

CNLayer::~CNLayer(void)
{
}
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����� ����
int CNLayer::GetNumFields(void) const
{
 return NumFields;
}

bool CNLayer::SetNumFields(int value)
{
 if(NumFields == value)
  return true;

 NumFields = value;
 Ready=false;

 return true;
}
// --------------------------
int CNLayer::GetLayerFlag(void) const
{
 return LayerFlag;
}

bool CNLayer::SetLayerFlag(int value)
{
 if(LayerFlag==value)
  return true;

 LayerFlag=value;
 return true;
}
// --------------------------
int CNLayer::GetConvolutionStep(void) const
{
 return  ConvolutionStep;
}

bool CNLayer::SetConvolutionStep(int value)
{
 if(ConvolutionStep == value)
  return true;

 ConvolutionStep = value;
 return true;
}
// --------------------------

int CNLayer::GetConvWidth(void) const
{
 return ConvWidth;
}

int CNLayer::GetConvHeight(void) const
{
 return ConvHeight;
}

bool CNLayer::SetConvWidth(int value)
{
 if(ConvWidth==value)
  return true;

 ConvWidth=value;
 return true;
}

bool CNLayer::SetConvHeight(int value)
{
 if(ConvHeight==value)
  return true;

 ConvHeight=value;
 return true;
}
// --------------------------
int CNLayer::GetFieldWidth(void) const
{
 return FieldWidth;
}

bool CNLayer::SetFieldWidth(int value)
{
 if(FieldWidth==value)
  return true;

 FieldWidth=value;
 return true;
}

int CNLayer::GetFieldHeight(void) const
{
 return FieldHeight;
}

bool CNLayer::SetFieldHeight(int value)
{
 if(FieldHeight==value)
  return true;

 FieldHeight=value;
 return true;
}
// --------------------------

// --------------------------
// ������ ���������� �������
// --------------------------
// ���������� ���� �� �������
CNField& CNLayer::GetField(int index)
{
 return Fields[index];
}

// ��������� �� ����- �������� ������
CNLayer* CNLayer::GetSourceLayer(void)
{
 return SourceLayer;
}

bool CNLayer::SetSourceLayer(CNLayer *src)
{
 if(SourceLayer == src)
  return true;

 Ready=false;

 SourceLayer=src;
 return true;
}

// ��������� �� ����- �������� ������
CNetwork* CNLayer::GetNetwork(void)
{
 return Network;
}

bool CNLayer::SetNetwork(CNetwork *src)
{
 if(Network == src)
  return true;

 Network=src;
 return true;
}
// --------------------------


// --------------------------
// ������ ���������� ������
// --------------------------
// ���������� ���� ���� �������� � ��������� ��������
void CNLayer::ResetTrainig(void)
{
 for(size_t j=0;j<Fields.size();j++)
  Fields[j].ResetTrainig();
}
// --------------------------


// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool CNLayer::ADefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool CNLayer::ABuild(void)
{
 Fields.resize(NumFields);

 // ���� �� �����
 // �������������� ����
 for(int i=0;i<NumFields;i++)
 {
  // ��� �������� �������� ����
  Fields[i].SetOwner(this);
  Fields[i].FieldIndex=i;


  if(SourceLayer)
  {
   int width=0;
   int height=0;
   int width_old=SourceLayer->GetField(0).GetWidthField();
   //int conv_width=SourceLayer->GetField(0).GetNeuron(0,0).GetWidth();
   int height_old=SourceLayer->GetField(0).GetHeightField();
   //int conv_height=SourceLayer->GetField(0).GetNeuron(0,0).GetHeight();

   switch(LayerFlag)
   {
	case 0:
	{
	 //��� ����������� width � height �� ����������� ���� SourceLayer...
	 //int h=Fields[i].GetConvolutionStep();

	 width=(width_old-ConvWidth)/ConvolutionStep+1;
	 height=(height_old-ConvHeight)/ConvolutionStep+1;

	 Fields[i].SetWidthField(width);
	 Fields[i].SetHeightField(height);

	 break;
	}

	case 1:
	{
	 Fields[i].SetWidthField(width_old/2);
	 Fields[i].SetHeightField(height_old/2);

	 break;
	}
   }

  }
  else
  {
   Fields[i].SetWidthField(FieldWidth);
   Fields[i].SetHeightField(FieldHeight);
  }

  if(!Fields[i].Build())
   return false;
 }

 return true;
}

// ����� �������� �����.
bool CNLayer::AReset(void)
{
 for(int i=0;i<NumFields;i++)
 {
  if(!Fields[i].Reset())
   return false;
 }
 return true;
}

// ��������� ������ ����� �������
bool CNLayer::ACalculate(void)
{
 for(int i=0;i<NumFields;i++)
 {
  if(!Fields[i].Calculate())
   return false;
 }
 return true;
}
// --------------------------

#endif

