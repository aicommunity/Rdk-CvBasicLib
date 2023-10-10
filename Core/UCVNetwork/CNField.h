//---------------------------------------------------------------------------

#ifndef CNFieldH
#define CNFieldH

#include <vector>
#include <string>
#include <list>
#include <map>
#include <cmath>
//#include "mysdk.h"
#include "CNeuron.h"

using namespace std;
using namespace RDK;

class CNLayer;
//class CNeuron;

class RDK_LIB_TYPE CNField: public UModule
{
protected: // ���������
// ������ ���� ��������
int WidthField;

// ������ ���� ��������
int HeightField;


//��� �������
//int ConvolutionStep;

protected: // ������
// ��������� �� ������������ ����
CNLayer* Owner;

public:
// ������ ����� ����
int FieldIndex;


// �������
vector<vector<CNeuron> > Neurons;

protected: // ������

protected: // ��������� ����������

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
CNField(void);
virtual ~CNField(void);
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� �������� ����
int GetWidthField(void) const;
int GetHeightField(void) const;
bool SetWidthField(int width);
bool SetHeightField(int height);

//��� �������
//int GetConvolutionStep(void) const;
//bool SetConvolutionStep(int value);

// --------------------------

// --------------------------
// ������ ���������� �������
// --------------------------
// ���������� ������ �� ������
CNeuron& GetNeuron(int i,int j);

// ��������� �� ������������ ����
CNLayer* GetOwner(void) const;
bool SetOwner(CNLayer* value);

// ������������� ������ �������� ������� ��������
bool SetOutput(vector<vector<double> > &output);
// --------------------------


// --------------------------
// ������ ���������� ������
// --------------------------
// ���������� ���� ���� �������� � ��������� ��������
void ResetTrainig(void);
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
// --------------------------
};

#endif
//---------------------------------------------------------------------------

