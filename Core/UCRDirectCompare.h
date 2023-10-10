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

#ifndef UCRDirectCompareH
#define UCRDirectCompareH

#include "UCRClassifier.h"

namespace RDK {

class RDK_LIB_TYPE UCRDirectCompare: public UCRClassifier
{
public: // ������������� ��������
// ����� ������������� �� ��������� ����� ����������
// � ��������� �� ��������� ������ (0,1)
RDK::ULProperty<double,UCRDirectCompare> MaxRecThreshold;

RDK::ULProperty<double,UCRDirectCompare> MinRecThreshold;

RDK::ULProperty<double,UCRDirectCompare> MiddleRecThreshold;

RDK::ULProperty<double,UCRDirectCompare> AbsoluteRecThreshold;

// ��� �������������
// 0 - �� ��������� ������� �� ���� �������
// 1 - �� ��������� ����� ���������� ���������� ������ �� ���� �������
// 2 - �� ��������� ����� ���������� �������������� ������ �� ���� �������
// 3 - �� ����� ���������� �������������� ������ �� ���� �������
// 4 - ���������� 1 �� � 2 �������� ������
//         ���� max - �� ����� ������
//        ���� max - �� ������� ������
// 5 - ����������� ��������
// 6 - �������� �� 5 ����������
// 10 - ������������ ������ �� �����
RDK::ULProperty<int,UCRDirectCompare> RecognitionType;

// ������� �������� ������������ ���������� (�� �������� ���� ����������)
RDK::ULProperty<double,UCRDirectCompare> ReliabilityDistance;

// ����� �������� ������������� ���������� �� ����������� �������� ���������
RDK::ULProperty<double,UCRDirectCompare> ReliabilityValue;

protected: // ������ ������
//public:
// ��������� �������
vector<vector<vector<double> > > Samples;

// ������ ������ ����
//vector<double> Inputs;

// ������ ������������ ������� ����� ����
vector<double> NativeOutput;

protected: // ������ � ��������� �������� ����

protected: // ��������� ����������


public:
// --------------------------
// ������������ � �����������
// --------------------------
UCRDirectCompare(void);
~UCRDirectCompare(void);
// --------------------------

protected:
// -----------------------------
// ������ ���������� �������������� ����������
// -----------------------------
// ������������� ����� ������ ���� ������� �����
//bool SetNumInputs(size_t numinputs);

// ����� ������������� �� ��������� ����� ����������
bool SetMaxRecThreshold(const double &value);
// -----------------------------

// -----------------------------
// ������ ������� � ������ ������
// -----------------------------
public:
// ������ �������
double GetSamples(int i, int j, int k) const;

// ������ ������������ ������� ����� ����
const vector<double>& GetNativeOutput(void) const;

// ������ ������
//const vector<double>& GetInputs(void) const;
// -----------------------------

// ------------------------
// ������ �����
// ------------------------
public:
// ��������� ��������� ����� �� ����� � ������ 'name'
virtual bool AFileLoad(fstream &file);

// ��������� ��������� ����� � ���� � ������ 'name'
virtual bool AFileSave(fstream &file);
// ------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
virtual UCRDirectCompare* New(void);
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
protected:
// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ACRDefault(void);

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
virtual bool ACRBuild(void);

// ����� �������� �����.
virtual bool ACRReset(void);

// ��������� ������ ����� ������� �� ������� ����.
virtual bool ACRCalculate(void);
// --------------------------

// --------------------------
// ������� ������ �������� ����
// --------------------------
protected:
// ����� �������� �������� � �������� ���������
virtual void AResetTraining(void);

// ����������� �������� �� �������� �������
virtual double ATrain(size_t exp_class);
// --------------------------

// ------------------------
// ������� ������ �����
// ------------------------
public:
// ������������� �������� �������� ������� ��� �������������
//virtual bool SetInput(const Real &input);
// ------------------------
};

}

//---------------------------------------------------------------------------
#endif
