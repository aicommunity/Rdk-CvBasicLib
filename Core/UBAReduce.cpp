#ifndef UBA_REDUCE_CPP
#define UBA_REDUCE_CPP

#include "UBAReduce.h"


namespace RDK {

// ---------------------
// ������������ � �����������
// ---------------------
UBAReduce::UBAReduce(void)
: Input("Input",this),
  Output("Output",this),
  NumCols("NumCols",this),
  NumRows("NumRows",this)
{
}
UBAReduce::~UBAReduce(void)
{

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

 Input->Reduce(NumCols, NumRows, &Output.v);
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------
#endif
