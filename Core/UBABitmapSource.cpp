/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBABitmapSource_CPP
#define UBABitmapSource_CPP

#include "UBABitmapSource.h"
//#include "../../UGraphics.h"
//#include "../../UGraphicsXMLSerialize.h"
//#include "../../UGraphicsBinarySerialize.h"
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBABitmapSource::UBABitmapSource(void)
: Output("Output",this),
  SourceParamaters("SourceParamaters",this)
{
}

UBABitmapSource::~UBABitmapSource(void)
{
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABitmapSource::ADefault(void)
{
 return AFSDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABitmapSource::ABuild(void)
{
// SourceParamaters.resize(NumOutputs);
 return AFSBuild();
}

// ����� �������� ����� ��� ������ ��������
bool UBABitmapSource::AReset(void)
{
 return AFSReset();
}

// ��������� ������ ����� �������
bool UBABitmapSource::ACalculate(void)
{
 for(int i=0;i<1;i++) // ��������!!
  Output->SetRes(SourceParamaters[i].Width,SourceParamaters[i].Height,SourceParamaters[i].ColorModel);
 return AFSCalculate();
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABitmapSource::AFSDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABitmapSource::AFSBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABitmapSource::AFSReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBABitmapSource::AFSCalculate(void)
{
 return true;
}
// --------------------------


/* UBABitmapSourceSimple */
// ---------------------
// ������������ � �����������
// ---------------------
UBABitmapSourceSimple::UBABitmapSourceSimple(void)
{
}

UBABitmapSourceSimple::~UBABitmapSourceSimple(void)
{
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBABitmapSourceSimple* UBABitmapSourceSimple::New(void)
{
 return new UBABitmapSourceSimple;
}

bool UBABitmapSourceSimple::BCalculate(void)
{

 return true;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABitmapSourceSimple::AFSDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABitmapSourceSimple::AFSBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABitmapSourceSimple::AFSReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBABitmapSourceSimple::AFSCalculate(void)
{
 return true;
}
// --------------------------

/* UBABitmapSourceSimple */
// ---------------------
// ������������ � �����������
// ---------------------
UBABitmapSourceFile::UBABitmapSourceFile(void)
{
}

UBABitmapSourceFile::~UBABitmapSourceFile(void)
{
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBABitmapSourceFile* UBABitmapSourceFile::New(void)
{
 return new UBABitmapSourceFile;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBABitmapSourceFile::AFSDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBABitmapSourceFile::AFSBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBABitmapSourceFile::AFSReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBABitmapSourceFile::AFSCalculate(void)
{
 return true;
}
// --------------------------


// ������ UBASourceFreezeFrame
// --------------------------
// ������������ � �����������
// --------------------------
UBASourceFreezeFrame::UBASourceFreezeFrame(void)
: FreezeFlag("FreezeFlag",this)
{
}

UBASourceFreezeFrame::~UBASourceFreezeFrame(void)
{
}
// --------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
UBASourceFreezeFrame* UBASourceFreezeFrame::New(void)
{
 return new UBASourceFreezeFrame;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBASourceFreezeFrame::ADefault(void)
{
 *FreezeFlag=false;
 return true;
}

// ����� �������� �����.
bool UBASourceFreezeFrame::AReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBASourceFreezeFrame::ACalculate(void)
{
 if(*FreezeFlag)
 {
  *FreezeFlag=false;
  *Output=*Input;
 }

 return true;
}
// --------------------------

}

#endif

