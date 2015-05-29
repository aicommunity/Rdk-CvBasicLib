/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBARECEIVER_CPP
#define UBANRECEIVER_CPP

#include "UBAReceiver.h"

namespace RDK {


// ������
// --------------------------
// ������������ � �����������
// --------------------------
UBAReceiver::UBAReceiver(void)
: Input("Input",this),
  Output("Output",this)
{
}

UBAReceiver::~UBAReceiver(void)
{
}
// --------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
/// �������� ������ ��� ����� ������ ����� ������� ����� ������
UBAReceiver* UBAReceiver::New(void)
{
 return new UBAReceiver;
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
/// �������������� �������� �� ��������� � ����� �������� �����
bool UBAReceiver::ADefault(void)
{
 return true;
}

/// ����� �������� �����.
bool UBAReceiver::AReset(void)
{
 return true;
}

/// ��������� ������ ����� �������
bool UBAReceiver::ACalculate(void)
{
 *Output=*Input;
 return true;
}
// --------------------------

}
#endif


