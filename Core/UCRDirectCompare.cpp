// ===========================================================
// Version:        3.0.3
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2002.
E-mail:        alexab@ailab.ru
url:            http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */

#include "UCRDirectCompare.h"
#include <algorithm>
#include <fstream>

namespace RDK {

using namespace std;

// --------------------------
// ������������ � �����������
// --------------------------
UCRDirectCompare::UCRDirectCompare(void)
//: UCRClassifier(name),
 // NumInputs(this,&UCRDirectCompare::SetNumInputs),
: MaxRecThreshold("MaxRecThreshold",this,&UCRDirectCompare::SetMaxRecThreshold),
  MinRecThreshold("MinRecThreshold",this),
  MiddleRecThreshold("MiddleRecThreshold",this),
  AbsoluteRecThreshold("AbsoluteRecThreshold",this),
  RecognitionType("RecognitionType",this),
  ReliabilityDistance("ReliabilityDistance",this),
  ReliabilityValue("ReliabilityValue",this)
{
// AddLookupParameter("RecognitionType",RecognitionType);

// AddLookupParameter("MinRecThreshold",MinRecThreshold);
// AddLookupParameter("MaxRecThreshold",MaxRecThreshold);
// AddLookupParameter("MiddleRecThreshold",MiddleRecThreshold);
// AddLookupParameter("AbsoluteRecThreshold",AbsoluteRecThreshold);
}

UCRDirectCompare::~UCRDirectCompare(void)
{
}
// --------------------------

// -----------------------------
// ������ ���������� �����������
// -----------------------------
// ������������� ����� ������ ���� ������� �����
/*bool UCRDirectCompare::SetNumInputs(size_t numinputs)
{
// NumInputs=numinputs;
 Ready=false;

 ModifiedFlag=true;
 return true;
}     */

// ����� ������������� �� ��������� ����� ����������
bool UCRDirectCompare::SetMaxRecThreshold(const double &value)
{
 ModifiedFlag=true;
 return true;
}
// -----------------------------

// -----------------------------
// ������ ������� � ������ ������
// -----------------------------
// ������ �������
double UCRDirectCompare::GetSamples(int i, int j, int k) const
{
 return Samples[i][j][k];
}

// ������ ������������ ������� ����� ����
const vector<double>& UCRDirectCompare::GetNativeOutput(void) const
{
 return NativeOutput;
}

// ������ ������
/*const vector<double>& UCRDirectCompare::GetInputs(void) const
{
 return Inputs;
} */
// -----------------------------

// ------------------------
// ������ �����
// ------------------------
// ��������� ��������� �� �����
bool UCRDirectCompare::AFileLoad(fstream &file)
{
 int i,j,k;
 size_t numclasses;
 int rectype;
 size_t numinputs;
 size_t temp;
 double value;

 file.read((char*)&numclasses,sizeof(numclasses));
 file.read((char*)&numinputs,sizeof(numinputs));

 if(numclasses <2 || numinputs ==0)
  return false;

 SetOutputDataSize(0,MMatrixSize(1,int(numclasses)));

// PInputDataSize[0]=PInputDataSize[0];
 Build();

 file.read((char*)&rectype,sizeof(rectype));
 RecognitionType=rectype;

// ����� ������������� �� ��������� ����� ����������
// � ��������� �� ��������� ������ (0,1)
 file.read((char*)&value,sizeof(value));
 MaxRecThreshold=value;

 file.read((char*)&value,sizeof(value));
 MinRecThreshold=value;

 file.read((char*)&value,sizeof(value));
 MiddleRecThreshold=value;

 file.read((char*)&value,sizeof(value));
 AbsoluteRecThreshold=value;

 file.read((char*)&temp,sizeof(temp));
 Samples.resize(temp);
 for(i=0;i<(int)Samples.size();i++)
 {
  file.read((char*)&temp,sizeof(temp));
  Samples[i].resize(temp);
  for(j=0;j<(int)Samples[i].size();j++)
  {
   file.read((char*)&temp,sizeof(temp));
   Samples[i][j].resize(temp);
   for(k=0;k<(int)Samples[i][j].size();k++)
    file.read((char*)&(Samples[i][j][k]),sizeof(Samples[i][j][k]));
  }
 }

 return true;
}

// ��������� ��������� � ����
bool UCRDirectCompare::AFileSave(fstream &file)
{
 size_t i,j,k;
 int rectype;
 double value;

 size_t temp;
 temp=GetOutputDataSize(0)[1];
 file.write((char*)&temp,sizeof(temp));
 temp=GetInputDataSize(0)[1];
 file.write((char*)&temp,sizeof(temp));

 rectype=RecognitionType;
 file.write((char*)&rectype,sizeof(rectype));

 // ����� ������������� �� ��������� ����� ����������
 // � ��������� �� ��������� ������ (0,1)
 value=MaxRecThreshold;
 file.write((char*)&value,sizeof(value));

 value=MinRecThreshold;
 file.write((char*)&value,sizeof(value));

 value=MiddleRecThreshold;
 file.write((char*)&value,sizeof(value));

 value=AbsoluteRecThreshold;
 file.write((char*)&value,sizeof(value));

 temp=Samples.size();
 file.write((char*)&temp,sizeof(temp));

 for(i=0;i<Samples.size();i++)
 {
  temp=Samples[i].size();
  file.write((char*)&temp,sizeof(temp));
  for(j=0;j<Samples[i].size();j++)
  {
   temp=Samples[i][j].size();
   file.write((char*)&temp,sizeof(temp));
   for(k=0;k<Samples[i][j].size();k++)
    file.write((char*)&(Samples[i][j][k]),sizeof(Samples[i][j][k]));
  }
 }

 return true;
}
// ------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
UCRDirectCompare* UCRDirectCompare::New(void)
{
 return new UCRDirectCompare;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UCRDirectCompare::ACRDefault(void)
{
 SetOutputDataSize(0,MMatrixSize(1,2));
 if(!Build())
  return false;
// PInputDataSize[0]=100;   // ��������!!! ��� ���

 vector<double> minrate,maxrate;
 minrate.assign(GetOutputDataSize(0)[1],10);
 maxrate.assign(GetOutputDataSize(0)[1],90);

 MinQualityRate=minrate;
 MaxQualityRate=maxrate;

// AutoQualityRate=true;
 AutoQualityRate=false;
// AutoAlignmentOutput=false;
 AutoAlignmentOutput=false;
 /*
 RecognitionType=3;
 MinRecThreshold=0.96;
 MaxRecThreshold=0.96;
 MaxInputValue=1;
 MinInputValue=0;
 MinOutputValue=0;
 MaxOutputValue=10;
   */
/*
 RecognitionType=1;
 MinRecThreshold=0.85;
 MaxRecThreshold=0.95;
 MaxInputValue=1;
 MinInputValue=0;
 MinOutputValue=0;
 MaxOutputValue=0.5;
  */
/* RecognitionType=1;
 MinRecThreshold=0.95;
 MaxRecThreshold=0.95;
 MaxInputValue=1;
 MinInputValue=0;
 MinOutputValue=0;
 MaxOutputValue=0.5;
*/
 RecognitionType=6;
 AbsoluteRecThreshold=0.988;
 MaxRecThreshold=0.975;
 MiddleRecThreshold=0.95;
 MinRecThreshold=0.9;
 MaxInputValue=1;
 MinInputValue=0;
 MinOutputValue=0;
 MaxOutputValue=1;

 ReliabilityDistance=0.03;

 ReliabilityValue=4.2;

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UCRDirectCompare::ACRBuild(void)
{
 return true;
}


// ����� �������� �����.
bool UCRDirectCompare::ACRReset(void)
{
 return true;
}

bool UCRDirectCompare::ACRCalculate(void)
{
 int classindex;

 double mininput,maxinput;
 int resclassindex=-1;
 double maxoutput=0;
 int nummethods=0;
 int outputsize=GetOutputDataSize(0)[1];
 int inputsize=GetInputDataSize(0)[1];

 pair<double,int> max_out[2];

 NativeOutput.resize(outputsize);
 vector<vector<double> > sortinput;

 switch(RecognitionType)
 {
 case 0:
  memcpy(&NativeOutput[0],&GetInputData(0)->Double[0],outputsize*sizeof(double));
  for(int i=outputsize;i<inputsize;i++)
  {
   classindex=i/outputsize;
   classindex*=outputsize;
   classindex=i-classindex;
   if(NativeOutput[classindex]<GetInputData(0)->Double[i])
    NativeOutput[classindex]=GetInputData(0)->Double[i];
  }

  for(int k=0;k<outputsize;k++)
   POutputData[0].Double[k]=NativeOutput[k];
 break;

 case 1:
  memset(&NativeOutput[0],0,outputsize*sizeof(double));

  mininput=GetInputData(0)->Double[0];
  maxinput=GetInputData(0)->Double[0];
  for(int i=1;i<GetInputDataSize(0)[1];i++)
  {
   if(mininput>GetInputData(0)->Double[i])
    mininput=GetInputData(0)->Double[i];
   if(maxinput<GetInputData(0)->Double[i])
    maxinput=GetInputData(0)->Double[i];
  }

  if(maxinput<(MaxInputValue()-MinInputValue())*MinRecThreshold)
  {
   for(int k=0;k<outputsize;k++)
    POutputData[0].Double[k]=NativeOutput[k];
   break;
  }

  for(int i=0;i<inputsize;i++)
  {
   classindex=i/outputsize;
   classindex*=outputsize;
   classindex=i-classindex;
   if(GetInputData(0)->Double[i]>maxinput*MaxRecThreshold)
    NativeOutput[classindex]+=GetInputData(0)->Double[i]-maxinput*MaxRecThreshold;
  }
  for(int k=0;k<outputsize;k++)
   POutputData[0].Double[k]=NativeOutput[k];
 break;

 case 2:
  memset(&NativeOutput[0],0,outputsize*sizeof(double));

  mininput=GetInputData(0)->Double[0];
  maxinput=GetInputData(0)->Double[0];
  for(int i=1;i<inputsize;i++)
  {
   if(mininput>GetInputData(0)->Double[i])
    mininput=GetInputData(0)->Double[i];
   if(maxinput<GetInputData(0)->Double[i])
    maxinput=GetInputData(0)->Double[i];
  }

  if(maxinput<(MaxInputValue()-MinInputValue())*MinRecThreshold)
  {
   for(int k=0;k<outputsize;k++)
    POutputData[0].Double[k]=NativeOutput[k];
   break;
  }

  maxinput=(MaxInputValue()-MinInputValue());
  for(int i=0;i<inputsize;i++)
  {
   classindex=i/outputsize;
   classindex*=outputsize;
   classindex=i-classindex;
   if(GetInputData(0)->Double[i]>maxinput*MaxRecThreshold)
    NativeOutput[classindex]+=GetInputData(0)->Double[i]-maxinput*MaxRecThreshold;
  }
  for(int k=0;k<outputsize;k++)
   POutputData[0].Double[k]=NativeOutput[k];
 break;

 case 3:
  memset(&NativeOutput[0],0,outputsize*sizeof(double));

  mininput=GetInputData(0)->Double[0];
  maxinput=GetInputData(0)->Double[0];
  for(int i=1;i<inputsize;i++)
  {
   if(mininput>GetInputData(0)->Double[i])
    mininput=GetInputData(0)->Double[i];
   if(maxinput<GetInputData(0)->Double[i])
    maxinput=GetInputData(0)->Double[i];
  }

  if(maxinput<(MaxInputValue()-MinInputValue())*MinRecThreshold)
  {
   for(int k=0;k<outputsize;k++)
    POutputData[0].Double[k]=NativeOutput[k];
   break;
  }

  for(int i=0;i<inputsize;i++)
  {
   classindex=i/outputsize;
   classindex*=outputsize;
   classindex=i-classindex;
   if(GetInputData(0)->Double[i]>(MaxInputValue()-MinInputValue())*MaxRecThreshold)
    ++NativeOutput[classindex];//=PInputs[0]->Double[i]-maxinput*MaxRecThresholdCoeff;
  }
  for(int k=0;k<outputsize;k++)
   POutputData[0].Double[k]=NativeOutput[k];
 break;

 case 4:
  memset(&NativeOutput[0],0,outputsize*sizeof(double));

  mininput=GetInputData(0)->Double[0];
  maxinput=GetInputData(0)->Double[0];
  for(int i=1;i<inputsize;i++)
  {
   if(mininput>GetInputData(0)->Double[i])
    mininput=GetInputData(0)->Double[i];
   if(maxinput<GetInputData(0)->Double[i])
    maxinput=GetInputData(0)->Double[i];
  }

  if(maxinput<MinRecThreshold*(MaxInputValue()-MinInputValue()))
  {
   for(int k=0;k<outputsize;k++)
    POutputData[0].Double[k]=NativeOutput[k];
   break;
  }

  // ���� ���������� ��������
  if(maxinput>AbsoluteRecThreshold*(MaxInputValue()-MinInputValue()))
  {
   memcpy(&NativeOutput[0],&GetInputData(0)->Double[0],outputsize*sizeof(double));
   for(int i=outputsize;i<inputsize;i++)
   {
    classindex=i/outputsize;
    classindex*=outputsize;
    classindex=i-classindex;
    if(NativeOutput[classindex]<GetInputData(0)->Double[i])
     NativeOutput[classindex]=GetInputData(0)->Double[i];
   }


   maxoutput=0;
   for(int k=0;k<outputsize;k++)
   {
    if(maxoutput<NativeOutput[k])
    {
     maxoutput=NativeOutput[k];
     resclassindex=k;
    }
   }
   for(int k=0;k<outputsize;k++)
    if(resclassindex == int(k))
     POutputData[0].Double[k]=MaxOutputValue;
    else
     POutputData[0].Double[k]=0;
  }
  else
  // ���� ���� ������������� ������ �� ��������� ��������� �� ����� ����������
  if(maxinput>MaxRecThreshold*(MaxInputValue()-MinInputValue()))
  {
   for(int i=0;i<inputsize;i++)
   {
    classindex=i/outputsize;
    classindex*=outputsize;
    classindex=i-classindex;
    if(GetInputData(0)->Double[i]>(MaxInputValue()-MinInputValue())*MaxRecThreshold)
     ++NativeOutput[classindex];
   }

   maxoutput=0;
   for(int k=0;k<outputsize;k++)
   {
    if(maxoutput<NativeOutput[k])
    {
     maxoutput=NativeOutput[k];
     resclassindex=k;
    }
   }
   for(int k=0;k<outputsize;k++)
    if(maxoutput)
     POutputData[0].Double[k]=NativeOutput[k]/maxoutput;
    else
     POutputData[0].Double[k]=0;
  }
  else
  if(maxinput>MiddleRecThreshold*(MaxInputValue()-MinInputValue()))
  {
   for(int i=0;i<inputsize;i++)
   {
    classindex=i/outputsize;
    classindex*=outputsize;
    classindex=i-classindex;
    if(GetInputData(0)->Double[i]>MiddleRecThreshold*(MaxInputValue()-MinInputValue()))
     NativeOutput[classindex]+=GetInputData(0)->Double[i]-MiddleRecThreshold*(MaxInputValue()-MinInputValue());
   }
/*
   for(size_t k=0;k<outputsize;k++)
    POutputData[0].Double[k]=NativeOutput[k];*/

   maxoutput=0;
   for(int k=0;k<outputsize;k++)
   {
    if(maxoutput<NativeOutput[k])
    {
     maxoutput=NativeOutput[k];
     resclassindex=k;
    }
   }
   for(int k=0;k<outputsize;k++)
    if(maxoutput)
     POutputData[0].Double[k]=NativeOutput[k]/maxoutput;
    else
     POutputData[0].Double[k]=0;
  }
  else
  {
   for(int i=0;i<inputsize;i++)
   {
    classindex=i/outputsize;
    classindex*=outputsize;
    classindex=i-classindex;
    if(GetInputData(0)->Double[i]>MinRecThreshold)
     NativeOutput[classindex]+=GetInputData(0)->Double[i]-MinRecThreshold;
   }

/*   for(size_t k=0;k<outputsize;k++)
    POutputData[0].Double[k]=NativeOutput[k];*/
   maxoutput=0;
   for(int k=0;k<outputsize;k++)
   {
    if(maxoutput<NativeOutput[k])
    {
     maxoutput=NativeOutput[k];
     resclassindex=k;
    }
   }
   for(int k=0;k<outputsize;k++)
    if(maxoutput)
     POutputData[0].Double[k]=NativeOutput[k]/maxoutput;
    else
     POutputData[0].Double[k]=0;
  }


 break;

 case 5:
  memset(&NativeOutput[0],0,outputsize*sizeof(double));

  mininput=GetInputData(0)->Double[0];
  maxinput=GetInputData(0)->Double[0];
  for(int i=1;i<inputsize;i++)
  {
   if(mininput>GetInputData(0)->Double[i])
    mininput=GetInputData(0)->Double[i];
   if(maxinput<GetInputData(0)->Double[i])
    maxinput=GetInputData(0)->Double[i];
  }

  if(maxinput<MinRecThreshold*(MaxInputValue()-MinInputValue()))
  {
   for(int k=0;k<outputsize;k++)
    POutputData[0].Double[k]=NativeOutput[k];
   break;
  }

  // ���� ���������� ��������
  memcpy(&NativeOutput[0],&GetInputData(0)->Double[0],outputsize*sizeof(double));
  for(int i=outputsize;i<inputsize;i++)
  {
   classindex=i/outputsize;
   classindex*=outputsize;
   classindex=i-classindex;
   if(NativeOutput[classindex]<GetInputData(0)->Double[i])
    NativeOutput[classindex]=GetInputData(0)->Double[i];
  }
  for(int k=0;k<outputsize;k++)
   POutputData[0].Double[k]=NativeOutput[k];

  // ������������
   maxoutput=0;
   for(int k=0;k<outputsize;k++)
   {
    if(maxoutput<NativeOutput[k])
    {
     maxoutput=NativeOutput[k];
     resclassindex=k;
    }
   }
   for(int k=0;k<outputsize;k++)
    if(maxoutput)
     POutputData[0].Double[k]=NativeOutput[k]/maxoutput;
    else
     POutputData[0].Double[k]=0;

  nummethods++;

  if(maxinput>(MaxInputValue()-MinInputValue())*MaxRecThreshold)
  {
   memcpy(&NativeOutput[0],&GetInputData(0)->Double[0],outputsize*sizeof(double));
   for(int i=0;i<inputsize;i++)
   {
    classindex=i/outputsize;
    classindex*=outputsize;
    classindex=i-classindex;
    if(GetInputData(0)->Double[i]>(MaxInputValue()-MinInputValue())*MaxRecThreshold)
     ++NativeOutput[classindex];
   }

   maxoutput=0;
   for(int k=0;k<outputsize;k++)
   {
    if(maxoutput<NativeOutput[k])
    {
	 maxoutput=NativeOutput[k];
     resclassindex=k;
    }
   }
   for(int k=0;k<outputsize;k++)
    if(maxoutput)
     POutputData[0].Double[k]+=NativeOutput[k]/maxoutput;
    else
     POutputData[0].Double[k]+=0;

   nummethods++;
  }

  if(maxinput>(MaxInputValue()-MinInputValue())*MiddleRecThreshold)
  {
  memcpy(&NativeOutput[0],&GetInputData(0)->Double[0],outputsize*sizeof(double));
   for(int i=0;i<inputsize;i++)
   {
    classindex=i/outputsize;
    classindex*=outputsize;
    classindex=i-classindex;
    if(GetInputData(0)->Double[i]>maxinput*MiddleRecThreshold)
     NativeOutput[classindex]+=GetInputData(0)->Double[i]-maxinput*MiddleRecThreshold;
   }

   maxoutput=0;
   for(int k=0;k<outputsize;k++)
   {
    if(maxoutput<NativeOutput[k])
    {
     maxoutput=NativeOutput[k];
     resclassindex=k;
    }
   }
   for(int k=0;k<outputsize;k++)
    if(maxoutput)
     POutputData[0].Double[k]+=NativeOutput[k]/maxoutput;
    else
     POutputData[0].Double[k]+=0;

   nummethods++;
  }

  memcpy(&NativeOutput[0],&GetInputData(0)->Double[0],outputsize*sizeof(double));
   for(int i=0;i<inputsize;i++)
   {
    classindex=i/outputsize;
    classindex*=outputsize;
    classindex=i-classindex;
    if(GetInputData(0)->Double[i]>maxinput*MinRecThreshold)
     NativeOutput[classindex]+=GetInputData(0)->Double[i]-mininput;//PInputs[0]->Double[i]-maxinput*MinRecThreshold;
   }
   nummethods++;
/*   for(size_t k=0;k<outputsize;k++)
    POutputData[0].Double[k]=NativeOutput[k];*/
   maxoutput=0;
   for(int k=0;k<outputsize;k++)
   {
    if(maxoutput<NativeOutput[k])
    {
     maxoutput=NativeOutput[k];
     resclassindex=k;
    }
   }
   for(int k=0;k<outputsize;k++)
    if(maxoutput)
     POutputData[0].Double[k]+=NativeOutput[k]/maxoutput;
    else
     POutputData[0].Double[k]+=0;

   for(int k=0;k<outputsize;k++)
     POutputData[0].Double[k]/=nummethods;

 break;

 case 6:
  sortinput.resize(outputsize);

  for(int i=0;i<inputsize;i++)
  {
   classindex=i/outputsize;
   classindex*=outputsize;
   classindex=i-classindex;
   sortinput[classindex].push_back(GetInputData(0)->Double[i]);
  }

  for(int i=0;i<outputsize;i++)
  {
   sort(sortinput[i].begin(),sortinput[i].end());
  }

  for(int k=0;k<outputsize;k++)
  {
   POutputData[0].Double[k]=0;
   for(int j=int(sortinput[k].size())-1;j>=int(sortinput[k].size())-5;j--)
   {
    POutputData[0].Double[k]+=sortinput[k][j];
   }
   NativeOutput[k]=POutputData[0].Double[k];
  }


  for(int k=0;k<2;k++)
   max_out[k].first=0;
  for(int k=0;k<outputsize;k++)
  {
   if(max_out[0].first<POutputData[0].Double[k])
   {
    max_out[1].first=max_out[0].first;
    max_out[1].second=max_out[0].second;
    max_out[0].first=POutputData[0].Double[k];
    max_out[0].second=k;
   }
  }

  if((max_out[0].first-max_out[1].first)<ReliabilityDistance ||
     (max_out[0].first<ReliabilityValue))
  for(int k=0;k<outputsize;k++)
   POutputData[0].Double[k]=0;
  for(int k=0;k<outputsize;k++)
   NativeOutput[k]=POutputData[0].Double[k];

 break;

 case 10:
  memcpy(&NativeOutput[0],&GetInputData(0)->Double[0],outputsize*sizeof(double));
  for(int i=outputsize;i<inputsize;i++)
  {
   classindex=i/outputsize;
   classindex*=outputsize;
   classindex=i-classindex;
   if(NativeOutput[classindex]<GetInputData(0)->Double[i])
    NativeOutput[classindex]=GetInputData(0)->Double[i];
  }

  for(int k=0;k<outputsize;k++)
   POutputData[0].Double[k]=NativeOutput[k];
 break;
 }

 return true;
}
// --------------------------


// --------------------------
// ������� ������ �������� ����
// --------------------------
// ����� �������� �������� � �������� ���������
void UCRDirectCompare::AResetTraining(void)
{
 Samples.resize(GetOutputDataSize(0)[1]);
// GetInputData(0)->Double.resize(GetInputDataSize(0));

 for(size_t j=0;j<Samples.size();j++)
 {
  Samples[j].clear();
 }
}

// ����������� �������� �� �������� �������
double UCRDirectCompare::ATrain(size_t exp_class)
{
 double E=0;

// Samples[exp_class].push_back();
 int inputsize=GetInputDataSize(0)[1];
 Samples[exp_class].resize(Samples[exp_class].size()+1);
 Samples[exp_class].back().resize(inputsize);
 for(int i=0;i<inputsize;i++)
  Samples[exp_class].back()[i]=GetInputData(0)->Double[i];


 return E;
}
// --------------------------


// ------------------------
// ������� ������ �����
// ------------------------
// ������������� �������� �������� ������� ��� �������������
/*bool UCRDirectCompare::SetInput(const Real &input)
{
 size_t i;

// PInputs[0]->Double.resize(NumPInputs[0]->Double);

 size_t mmin=(GetInputDataSize(0)<input.size())?GetInputDataSize(0):input.size();
 for(i=0;i<mmin;i++)
  {
   PInputs[0]->Double[i]=input[i];
  }

 return true;
}  */
// ------------------------


}

//---------------------------------------------------------------------------

