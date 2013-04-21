/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBGRAPHICS_BASIC_CPP
#define UBGRAPHICS_BASIC_CPP

#include "Basic.h"
#include "Basic_lite.cpp"
#include "UBAColorConvert.cpp"
//#include "UBAResize.cpp"
//#include "UBARotate.cpp"


namespace RDK{

Basic BasicLibrary;

// --------------------------
// ������������ � �����������
// --------------------------
Basic::Basic(void)
 : ULibrary("BasicLibrary","1.0")
{
}
// --------------------------

// --------------------------
// ������ ����������� �����������
// --------------------------
// ��������� ������ ClassSamples �������� ������������ �������� � �� �������.
// �� ��������� ��������������� ������� ������� � ������ ������.
void Basic::CreateClassSamples(UStorage *storage)
{
 UContainer *cont;
 cont=new UBAColorConvert;
 cont->SetName("ColorConvert");
 cont->Default();
 UploadClass("ColorConvert",cont);

 cont=new UBAResizeEdges;
 cont->SetName("ResizeEdges");
 cont->Default();
 UploadClass("ResizeEdges",cont);

 cont=new UBARotateSimple;
 cont->SetName("RotateSimple");
 cont->Default();
 UploadClass("RotateSimple",cont);
}
// --------------------------


}

#endif
