#ifndef CNETWORK_H
#define CNETWORK_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//#include "mysdk.h"
#include "CNLayer.h"

using namespace std;
using namespace RDK;

//class CNLayer;

class RDK_LIB_TYPE CNetwork: public UModule
{
protected: // ���������
// ����� ����� ����
int NumLayers;

// ������ ����� �������
vector<int> NetworkConvolutionStep;

// ������ ����� ���� �������
vector<int> NetworkConvHeight;

// ������ ����� ���� �������
vector<int> NetworkConvWidth;

// ������ ���������� ����� � ������ ����
vector<int> NetworkNumFields;

// ������� �������� �����������
int InputWidth,InputHeight;

// ������ ���� �������
//int ConvWidth, ConvHeight; //� ���� ��? ���� � CNeuron.h

// ����� �������
int NumOutputs;

//�������� �������� ��������
double Eta;

//������� ��������� �������
vector<double> trueOtklik;

//������� ������� ������
double Error;

// ������� �����
double DegWeights;

protected: // ������
// ������� �����������
UBitmap InputImage;

// ����
vector<CNLayer> Layers;

protected: // ��������� ����������

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
CNetwork(void);
virtual ~CNetwork(void);
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����� ����
const int& GetNumLayers(void) const;
bool SetNumLayers(const int& value);

const vector<int>& GetNetworkConvStep(void) const;
bool SetNetworkConvStep(const vector<int>& value);

const vector<int>& GetNetworkConvHeight(void) const;
bool SetNetworkConvHeight(const vector<int>& value);

const vector<int>& GetNetworkConvWidth(void) const;
bool SetNetworkConvWidth(const vector<int>& value);

const vector<int>& GetNetworkNumFields(void) const;
bool SetNetworkNumFields(const vector<int>& value);

// ������� �������� �����������
const int& GetInputWidth(void) const;
bool SetInputWidth(const int &value);

const int& GetInputHeight(void) const;
bool SetInputHeight(const int &value);

// �������� ��������
const double& GetEta(void) const;
bool SetEta(const double& value);

//������� ������� ������
const double& GetError(void) const;
bool SetError(double value);

// ������� �����
const double& GetDegWeights(void) const;
bool SetDegWeights(double value);
// --------------------------

// --------------------------
// ������ ���������� �������
// --------------------------
// ���������� ���� �� �������
CNLayer& GetLayer(int index);
// --------------------------

// --------------------------
// ������ ���������� ������
// --------------------------
//bool SetInputImage(const UBitmap &input);

bool SetFieldOutput(int layer, int field, vector<vector<double> > &output);
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
protected:
// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
virtual bool ABuild(void);

// ����� �������� �����.
virtual bool AReset(void);

// ��������� ������ ����� �������
virtual bool ACalculate(void);

public:
//��������
double ATrain(int exp_class);

void ResetTraining(void);
// --------------------------
};

#endif
