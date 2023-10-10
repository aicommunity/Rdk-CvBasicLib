#ifndef CNEURON_H
#define CNEURON_H

#include <vector>
//#include "mysdk.h"
#include "../../../../Rdk/Deploy/Include/rdk.h"

using namespace std;
using namespace RDK;

class CNField;
class CNetwork;

struct RDK_LIB_TYPE CNeuronCoord
{
 int field, x, y;
};

class RDK_LIB_TYPE CNeuron: public UModule
{
friend class CNField;
friend class CNetwork;
protected: // ���������
// ��������� ������� ���������
double ActA, ActB;

// ����� ����� ���������� ������
int NumSourceField;

// ���������� ����������� ����
int X, Y, Width, Height; //width � height ��������� - ���� �������



protected: // ������
// ��������� �� ������������ ����
CNetwork* NetworkOwner;

// ��������� �� ����-�������� ������
vector<CNField*> SourceField;

// ����� �������
double Output;

// ���� �������
double Input;

// ����
vector<vector<vector<double> > > Weights;

public:
// ���������� ����
vector<vector<vector<double> > > PrevWeights;

// ������ �������
//vector<vector<vector<double> > > Delta;
double Delta;

// ������ �������� ��������, ������������ ������� � ������ ����� �������
vector<CNeuronCoord> ConnectedNeurons;

public: // ������

// --------------------------
// ������������ � �����������
// --------------------------
CNeuron(void);
virtual ~CNeuron(void);
// --------------------------


// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����� ���������� ������
int GetNumSourceField(void) const;
bool SetNumSourceField(int value);

// ���������� ����������� ����
int GetX(void) const;
bool SetX(int value);
int GetY(void) const;
bool SetY(int value);
int GetWidth(void) const;
bool SetWidth(int value);
int GetHeight(void) const;
bool SetHeight(int value);
// --------------------------


// ������� ���������
double ActivationFunc(double x);

// ����������� ������� ��������� �� ���������
double dActivationFunc(double x);

// ����� �������
double GetOutput(void) const;
bool SetOutput(double value);

//���� �������
double GetInput(void) const;
bool SetInput(double value);

// ���������� ����� �������, ������������� � ����� �� ��������� �����
double GetInputData(int field, int x, int y) const;

// ���������� ���� ������� � ��������� ��������
void ResetTrainig(void);

//�������������� ���������� �����
bool SetWeights(vector<vector<vector<double> > > weights);

// ������ � ������� �����
vector<vector<vector<double> > >& GetWeights(void);

// ���������� ����� �������� ������������ ������� � ������ ����� �������
size_t GetNumConnectedNeurons(void) const;

// ���������� ������ ������������ ������� � ������ ����� �������
CNeuronCoord& GetConnectedNeuron(size_t index);

// --------------------------
// ������ ���������� �������
// --------------------------
// ��������� �� ������������ ����
CNetwork* GetNetworkOwner(void) const;
bool SetNetworkOwner(CNetwork* value);

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
// --------------------------
};
#endif
