#ifndef UBA_REDUCE_CPP
#define UBA_REDUCE_CPP

#include "UBAReduce.h"


namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBAReduce::UBAReduce(void)
: Input("Input",this,0),
  Output("Output",this,0)
{
 AddLookupProperty("NumCols",ptPubParameter, new UVProperty<int,UBAReduce>(this,&UBAReduce::SetNumCols,&UBAReduce::GetNumCols));
 AddLookupProperty("NumRows",ptPubParameter, new UVProperty<int,UBAReduce>(this,&UBAReduce::SetNumRows,&UBAReduce::GetNumRows));
}
UBAReduce::~UBAReduce(void)
{

}
// ---------------------
// ������ ���������� �����������
// ---------------------
/// ����� ������ � ������� ��� ����������
const int& UBAReduce::GetNumCols(void) const
{
 return NumCols;
}

const int& UBAReduce::GetNumRows(void) const
{
 return NumRows;
}

bool UBAReduce::SetNumCols(const int &value)
{
 if(NumCols == value)
  return true;

 if(value == 0)
  return false;

 NumCols=value;
  return true;
}

bool UBAReduce::SetNumRows(const int &value)
{
 if(NumRows == value)
  return true;

 if(value == 0)
  return false;

 NumRows=value;
  return true;
}

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBAReduce* UBAReduce::New(void)
{
 return new UBAReduce;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAReduce::ADefault(void)
{
 NumCols=1;
 NumRows=1;
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAReduce::ABuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBAReduce::AReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBAReduce::ACalculate(void)
{
 if(!Input->GetData())
  return true;

 Input->Reduce(NumCols, NumRows, Output);
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------
#endif