/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAMODEL_CPP
#define UBAMODEL_CPP

#include "UBAModel.h"

namespace RDK {

// ������
// --------------------------
// ������������ � �����������
// --------------------------
UBAModel::UBAModel(void)
 : Output("Output",this),
   WorkWidth("WorkWidth",this),
   WorkHeight("WorkHeight",this)
{
}

UBAModel::~UBAModel(void)
{
}
// --------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
UBAModel* UBAModel::New(void)
{
 return new UBAModel;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAModel::ADefault(void)
{
 return AMDefault();
}

bool UBAModel::AMDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAModel::ABuild(void)
{
 return AMBuild();
}

bool UBAModel::AMBuild(void)
{
 return true;
}

// ����� �������� �����.
bool UBAModel::AReset(void)
{
 *WorkWidth=Output->GetWidth();
 *WorkHeight=Output->GetHeight();
 return AMReset();
}

bool UBAModel::AMReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBAModel::ACalculate(void)
{
 *WorkWidth=Output->GetWidth();
 *WorkHeight=Output->GetHeight();
 return AMCalculate();
}

bool UBAModel::AMCalculate(void)
{
 return true;
}
// --------------------------


}
#endif


