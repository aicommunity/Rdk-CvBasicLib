/* ***********************************************************

*********************************************************** */

#ifndef TCaptureImageSequence_CPP
#define TCaptureImageSequence_CPP

#include "TCaptureImageSequence.h"
//#include "../../../../Rdk/Core/Graphics/UGraphicsIO.h"

namespace RDK
{
// --------------------------
// ������������ � �����������
// --------------------------
TCaptureImageSequence::TCaptureImageSequence(void)
 : Path("Path",this, &TCaptureImageSequence::SetPath),
   IsPathRelativeFromConfig("IsPathRelativeFromConfig",this,&TCaptureImageSequence::SetIsPathRelativeFromConfig),
   RepeatFlag("RepeatFlag",this),
   CaptureDelay("CaptureDelay",this),
   NumImages("NumImages",this),
   CurrentImageIndex("CurrentImageIndex",this),
   CurrentImageFileName("CurrentImageFileName",this)
{

}
TCaptureImageSequence::~TCaptureImageSequence(void)
{
}

// --------------------------
// ������ ���������� �����������
// --------------------------
/// ���� �� ����� � �������������
bool TCaptureImageSequence::SetPath(const std::string &value)
{
 CalcActualPath(value, IsPathRelativeFromConfig, ActualPath);
 Ready=false;
 return true;
}

/// �������, ��������� ������������� ���� ��� ������������� �� ����� � �������������
bool TCaptureImageSequence::SetIsPathRelativeFromConfig(const bool &value)
{
 CalcActualPath(Path, value, ActualPath);
 Ready=false;
 return true;
}

/// ���� ������������ ���������������
bool TCaptureImageSequence::SetRepeatFlag(const bool &value)
{
 return true;
}

/// �������� ����� ����������� ����������� (��)
bool TCaptureImageSequence::SetCaptureDelay(const int &value)
{
 return true;
}
// --------------------------

// --------------------------
// ������� ������
// --------------------------
bool TCaptureImageSequence::ASetEnableCapture(const bool &value)
{
// return ASetEnableCapture1(value);
 return true;
}
// --------------------------
bool TCaptureImageSequence::AStartCapture(void)
{
// return AStartCapture1();
 return true;
}
// --------------------------
bool TCaptureImageSequence::AStopCapture(void)
{
// return AStopCapture1();
 return true;
}
// --------------------------

// --------------------------
/// �������� ������ ��� ����� ������ ����� ������� ����� ������
TCaptureImageSequence* TCaptureImageSequence::New(void)
{
 return new TCaptureImageSequence;
}

bool TCaptureImageSequence::ADefault1(void)
{
 CaptureDelay=30;
 RepeatFlag=true;
 EnableCapture=true;
 return true;
}
// --------------------------
bool TCaptureImageSequence::ABuild1(void)
{
 NumImages=0;
 Images.clear();
 FindFilesList(ActualPath, "*.*", true, Images);
 std::sort(Images.begin(), Images.end());
 NumImages=int(Images.size());
 return true;
}
// --------------------------
bool TCaptureImageSequence::AReset1(void)
{
 if(NumImages>0)
  CurrentImageIndex=0;
 else
  CurrentImageIndex=-1;

 LastImageTime=0;
 CurrentImageFileName->clear();
 return true;
}
// --------------------------
bool TCaptureImageSequence::ACalculate1(void)
{
 if(!EnableCapture)
  return true;

 if(Images.empty())
  return true;

 unsigned long long current_time=GetCurrentStartupTime();
 unsigned long long diff=CalcDiffTime(current_time, LastImageTime);

 if(int(diff)<CaptureDelay)
  return true;

 if(CurrentImageIndex<int(Images.size()))
  CurrentImageIndex=CurrentImageIndex+1;

 if(CurrentImageIndex>=int(Images.size()))
 {
  if(RepeatFlag)
   CurrentImageIndex=0;
  else
  {
   return true;
  }
 }

 std::string file_name=Images[CurrentImageIndex];
 std::string file_ext=extract_file_ext(file_name);

 std::transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);
 bool res=false;
 if(file_ext == "bmp")
 {
  res=LoadBitmapFromFile((ActualPath+file_name).c_str(),*OutputImage);
 }
 else
 if(file_ext == "jpg" || file_ext == "jpeg")
 {
  res=LoadJpegFromFile((ActualPath+file_name).c_str(),*OutputImage);
 }

 if(res)
 {
  if(FlipX)
   OutputImage->ReflectionX();

  if(FlipY)
   OutputImage->ReflectionY();

  OutputImage.SetUpdateTime(current_time);
  LastImageTime=current_time;
  *CaptureTime= current_time;
  *CurrentImageFileName=file_name;
  data_changed=true;
 }
 else
 {
  *CurrentImageFileName="";
 }

 return true;
}

/// ��������� ���������� ����
void TCaptureImageSequence::CalcActualPath(const std::string &path, bool is_relative, std::string &result)
{
 if(is_relative)
 {
  result=GetEnvironment()->GetCurrentDataDir()+path;
 }
 else
  result=path;
 if(!path.empty())
 {
  if(path[path.size()-1] != '/' && path[path.size()-1] != '\\')
   result+="/";
 }
}
// --------------------------

}
#endif
