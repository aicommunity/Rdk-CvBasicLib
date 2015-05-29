/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBPIPELINE_CPP
#define UBPIPELINE_CPP

#include <string.h>
#include "UBPipeline.h"


namespace RDK {

// --------------------------
// ������������ � �����������
// --------------------------
UBPipeline::UBPipeline(void)
{
}

UBPipeline::~UBPipeline(void)
{
}
// --------------------------

// ---------------------
// ������ ���������� ���������
// ---------------------
// ---------------------


// --------------------------
// ������ ������� � �����������
// --------------------------
// ����� ��������� �� ������������ ������� ������� ����
// � �������� ���������� ������� �������
// ����� ���������� 'true' � ������ ������������
// � 'false' � ������ ������������� ����
bool UBPipeline::CheckComponentType(UEPtr<UContainer> comp) const
{
 return true;
}
// --------------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBPipeline* UBPipeline::New(void)
{
 return new UBPipeline;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������������
// --------------------------
// ��������� ����������� ���������������� ��������
// ��� ���������� ��������� ���������� � ���� ������
// ����� ����� ������ ������ ���� comp ���
// ������� �������� � ������ ���������
// ����� ���� ������� ��������� �� ��������� ����������
bool UBPipeline::AAddComponent(UEPtr<UContainer> comp, UEPtr<UIPointer> pointer)
{
 return true;
}

// ��������� ��������������� ���������������� ��������
// ��� �������� ��������� ���������� �� ����� �������
// ����� ����� ������ ������ ���� comp
// ���������� � ������ ���������
bool UBPipeline::ADelComponent(UEPtr<UContainer> comp)
{
 return true;
}
// --------------------------

// ---------------------
// ������� ������ �����
// ---------------------
// ---------------------




// class UBParallelPipeline
// --------------------------
// ������������ � �����������
// --------------------------
UBParallelPipeline::UBParallelPipeline(void)
{
}

UBParallelPipeline::~UBParallelPipeline(void)
{
}
// --------------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBParallelPipeline* UBParallelPipeline::New(void)
{
 return new UBParallelPipeline;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBParallelPipeline::ADefault(void)
{
 return true;
}

// ����� �������� �����.
bool UBParallelPipeline::AReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBParallelPipeline::ACalculate(void)
{
 return true;
}
// --------------------------
}

#endif


