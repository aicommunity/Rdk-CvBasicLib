// ===========================================================
// Version:        1.0.0
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2010.
E-mail:        alexab@ailab.ru
url:        http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UCR_SAMPLE_CPP
#define UCR_SAMPLE_CPP

#include "UCRSample.h"
//#include "../../../Utilities/UIniFile.h"
//#include "../../../Graphics/UGraphicsIO.h"
//#include "../../../Engine/UEnvironment.h"
#include "../../../Rdk/Deploy/Include/rdk.h"
//#include "../../../Rdk/Gui/Bcb/TUBitmap.h"
//#include "myrdk.h"

namespace RDK {
//---------------------------------------------------------------------------
// --------------------------
// ������������ � �����������
// --------------------------
UCRSample::UCRSample(void)
// : NADItem(name),
// SampleData("SampleData",this),
: Type("Type",this),
 VectorSize("VectorSize",this,&UCRSample::SetVectorSize),
 SampleImageWidth("SampleImageWidth",this),
 SampleImageHeight("SampleImageHeight",this),
 SampleSize("SampleSize",this,&UCRSample::SetSampleSize),
 SampleFileName("SampleFileName",this,&UCRSample::SetSampleFileName),
 MinInputValue("MinInputValue",this),
 MaxInputValue("MaxInputValue",this),
 MinOutputValue("MinOutputValue",this),
 MaxOutputValue("MaxOutputValue",this),
 ScaleFlag("ScaleFlag",this),
 ReflictionX("ReflictionX",this),
 Mode("Mode",this),
 CurrentSample("CurrentSample",this,&UCRSample::SetCurrentSample),
 CurrentSampleIteration("CurrentSampleIteration",this),
 NumClasses("NumClasses",this)
{
}

UCRSample::~UCRSample(void)
{
}
// --------------------------

// --------------------------
// ������ ���������� �������������� ����������
// --------------------------
// ������� ������� �������
bool UCRSample::SetCurrentSample(const int &value)
{
 if(value<-1 || value >= int(SampleSize))
  return false;

 return true;
}

// ��������� ������� �������
bool UCRSample::SetSampleSize(const int &value)
{
 if(value < SampleSize)
 {
  SampleData.resize(value);
  return true;
 }

 return true;
}

// ��������� ������� ������� �������
bool UCRSample::SetVectorSize(const int &value)
{
 SetOutputDataSize(0,MMatrixSize(1,value));
 return true;
}

// ��� ����� �������
bool UCRSample::SetSampleFileName(const string &value)
{
 Ready=false;
 return true;
}
// --------------------------

// --------------------------
// ������ ���������� ��������
// --------------------------
// ��������� ������� ������� �������� ������
bool UCRSample::Add(int class_index)
{
 if(!NumInputs)
  return false;

 ++SampleSize.v;
 SampleData.resize(SampleSize);

// SampleData[SampleSize-1].first.SetDataSize(sizeof(double));
 SampleData[SampleSize-1].first.Resize(1,0);
 for(int i=0;i<NumInputs;i++)
 {
  if(GetInputDataSize(i)[1]<=0)
   continue;
  SampleData[SampleSize-1].first+=*GetInputData(i);
 }

 if(SampleData[SampleSize-1].first.GetSize() != int(VectorSize))
 {
  --SampleSize.v;
  SampleData.resize(SampleSize);
  return false;
 }

 if(ScaleFlag)
  for(int i=0;i<SampleData[SampleSize-1].first.GetSize();i++)
   SampleData[SampleSize-1].first.Double[i]=(SampleData[SampleSize-1].first.Double[i]-MinInputValue)*(MaxOutputValue-MinOutputValue)/(MaxInputValue-MinInputValue)+MinOutputValue;

 SampleData[SampleSize-1].second=class_index;
 if(NumClasses<=class_index)
  NumClasses=class_index+1;
 return true;
}

// ��������� ������� �������� �������� ������
bool UCRSample::Add(const vector<double> &data, int class_index)
{
 ++SampleSize.v;
 SampleData.resize(SampleSize);
// SampleData[SampleSize-1].first.SetDataSize(sizeof(double));
 SampleData[SampleSize-1].first.Resize(1,int(data.size()));
 for(size_t i=0;i<data.size();i++)
 {
  if(ScaleFlag)
   SampleData[SampleSize-1].first.Double[i]=(data[i]-MinInputValue)*(MaxOutputValue-MinOutputValue)/(MaxInputValue-MinInputValue)+MinOutputValue;
  else
   SampleData[SampleSize-1].first.Double[i]=data[i];
 }

 if(SampleData[SampleSize-1].first.GetSize() != int(VectorSize))
 {
  SampleData[SampleSize-1].first.Resize(1,VectorSize);
 }

 SampleData[SampleSize-1].second=class_index;
 if(NumClasses<=class_index)
  NumClasses=class_index+1;
 return true;
}


// ������� �������� ������� ������� ������ �� �������
bool UCRSample::Del(size_t index)
{
 return true;
}

// ������� �������
void UCRSample::Clear(void)
{
 SampleSize=0;
 SampleData.resize(SampleSize);
 BitmapSampleData.resize(SampleSize);
 NumClasses=0;
}

// ���������� ������ ������ �������� ������� ��������� �������
int UCRSample::GetCurrentClassIndex(void) const
{
 if(CurrentSample.v<0 || CurrentSample.v>=SampleSize)
  return -1;

 return SampleData[CurrentSample].second;
}

// ���������� ������ ��������� �������
const vector<pair<RDK::UItemData,int> >& UCRSample::GetSampleData(void) const
{
 return SampleData;
}

const vector<pair<RDK::UBitmap,int> >& UCRSample::GetBitmapSampleData(void) const
{
 return BitmapSampleData;
}

// ������������� ��� ����� ������� ������ �����������
bool UCRSample::SetSampleData(const RDK::UBitmap &image)
{
 vector<double> data;

 CurrentBitmapSampleData.SetColorModel(ubmY8,false);
 image.ConvertTo(CurrentBitmapSampleData);
 data.resize(CurrentBitmapSampleData.GetLength());
 for(int j=0;j<CurrentBitmapSampleData.GetLength();j++)
  data[j]=CurrentBitmapSampleData.GetData()[j];

// CurrentSampleData.SetDataSize(sizeof(double));
 CurrentSampleData.Resize(1,int(data.size()));
 for(size_t i=0;i<data.size();i++)
 {
  if(ScaleFlag)
   CurrentSampleData.Double[i]=(data[i]-MinInputValue)*(MaxOutputValue-MinOutputValue)/(MaxInputValue-MinInputValue)+MinOutputValue;
  else
   CurrentSampleData.Double[i]=data[i];
 }
 return true;
}

RDK::UBitmap& UCRSample::GetCurrentBitmapSampleData(void)
{
 return CurrentBitmapSampleData;
}


// ��������� ������� ��� ����� ����������� �� ������
// ����� ������ ������ ���� ���� xxxx_classindex.bmp
// ��� ��������� ������ � ������� �� ����� ��������
bool UCRSample::LoadBitmapSample(const string &file_path)
{
 vector<string> file_names;
 FindFilesList(file_path, "*.bmp", true, file_names);

 UBitmap bmp;
 vector<double> data;
 for(size_t i=0;i<file_names.size();i++)
 {
  LoadBitmapFromFile((file_path+string("/")+file_names[i]).c_str(),bmp);
  bmp.SetColorModel(ubmY8);
  if(ReflictionX)
   bmp.ReflectionX();
  data.resize(bmp.GetLength());
  for(int j=0;j<bmp.GetLength();j++)
   data[j]=bmp.GetData()[j];
  int class_index=0;
  size_t start_i=file_names[i].find_first_of("_");
  size_t stop_i=file_names[i].find_first_of(".");
  class_index=atoi(file_names[i].substr(start_i+1,stop_i));
  Add(data,class_index);
  BitmapSampleData.push_back(pair<RDK::UBitmap,int>(bmp,class_index));
 }
 return true;
}


// ��������� ������� ��� ���������� ���������� �����
// ������ ������ - ���� ������� �������
// ������ ����� � ������ - ������ ������, ��������� - ������ ������� �������
// �����������: ��������� ��� ������
// ��� ��������� ������ � ������� �� ����� ��������
bool UCRSample::LoadTextSample(const string &file_name)
{
 return true;
}
// --------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
UContainer* UCRSample::New(void)
{
 return new UCRSample;
}
// --------------------------


// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UCRSample::ADefault(void)
{
 SetNumOutputs(1);
// SetOutputDataElementSize(0,sizeof(double));
 SetOutputDataSize(0,MMatrixSize(1,20));
 SampleSize=1;
 SampleImageWidth=64;
 SampleImageHeight=64;
 VectorSize=SampleImageWidth*SampleImageHeight;
 Type=1;
 Mode=0;

 MinInputValue=0;
 MaxInputValue=255;
 MinOutputValue=0;
 MaxOutputValue=1;
 ScaleFlag=true;
 ReflictionX=true;
 NumClasses=0;

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UCRSample::ABuild(void)
{
 return true;
}

// ����� �������� �����
bool UCRSample::AReset(void)
{
 string path;

 if(GetEnvironment())
  path=GetEnvironment()->GetCurrentDataDir()+"/";

 switch(Type.v)
 {
 case 0:
  Clear();
   if(!LoadTextSample(path+SampleFileName.v))
	return false;
 break;

 case 1:
  Clear();
  if(!LoadBitmapSample(path+SampleFileName.v))
   return false;
 break;
 }
 CurrentSample=-1;
 CurrentSampleIteration=0;

 CurrentBitmapSampleData.SetRes(20,20,ubmY8);
 return true;
}

// ��������� ������ ����� ������� �� ������� ����
bool UCRSample::ACalculate(void)
{
 size_t k=0;
 switch(Mode)
 {
 case 0:
  if(!NumInputs)
   return false;

  for(int i=0;i<NumInputs;i++)
  {
   int num_inputs_data=GetInputDataSize(i)[1];
   for(int j=0;j<num_inputs_data;j++,k++)
	POutputData[0].Double[k]=GetInputData(i)->Double[j];
  }
 break;

 case 1:
 {
  if(SampleSize == 0)
  {
   SetOutputDataSize(0,MMatrixSize(1,VectorSize.v));
   for(int i=0;i<VectorSize.v;i++)
	POutputData[0].Double[i]=0;
   return true;
  }

  ++CurrentSample.v;
  if(CurrentSample>=int(SampleSize.v))
  {
   CurrentSample=0;
   ++CurrentSampleIteration.v;
  }

  SetOutputDataSize(0,MMatrixSize(1,VectorSize.v));
  const RDK::UItemData &data=SampleData[CurrentSample].first;

  for(int i=0;i<VectorSize.v;i++)
   POutputData[0].Double[i]=data.Double[i];
 }
 break;

 case 2:
  SetOutputDataSize(0,MMatrixSize(1,CurrentSampleData.GetSize()));
  Build();
  POutputData[0].Assign(1,CurrentSampleData.GetSize(),CurrentSampleData.Double);
 break;

 }
 return true;
}
// --------------------------

//---------------------------------------------------------------------------
}
#endif
