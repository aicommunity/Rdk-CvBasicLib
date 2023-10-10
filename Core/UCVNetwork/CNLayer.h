#ifndef CNLayerH
#define CNLayerH

#include <vector>
#include "CNField.h"

using namespace std;
//using namespace MySDK;

class CNetwork;


class RDK_LIB_TYPE CNLayer: public UModule
{
protected://���������

//����� ����� ����
int NumFields;

// ���� ����
// 0 - ���������� ����
// 1 - ������������������� ����
int LayerFlag;

// ������ ���� �������
int ConvWidth, ConvHeight;

// ��� �������
int ConvolutionStep;

// ����������� �����
int FieldWidth, FieldHeight;

protected: // ������
// ��������� �� ����- �������� ������
CNLayer *SourceLayer;

// ��������� �� ����
CNetwork *Network;

// ����
vector<CNField> Fields;

protected: // ��������� ����������

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
CNLayer(void);
virtual ~CNLayer(void);
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����� ����
int GetNumFields(void) const;
bool SetNumFields(int value);
// --------------------------
int GetLayerFlag(void) const;
bool SetLayerFlag(int value);
// --------------------------
int GetConvWidth(void) const;
int GetConvHeight(void) const;

bool SetConvWidth(int value);
bool SetConvHeight(int value);
// --------------------------
int GetConvolutionStep(void) const;
bool SetConvolutionStep(int value);
// --------------------------
int GetFieldWidth(void) const;
bool SetFieldWidth(int value);

int GetFieldHeight(void) const;
bool SetFieldHeight(int value);
// --------------------------
// ������ ���������� �������
// --------------------------
// ���������� ���� �� �������
CNField& GetField(int index);

// ��������� �� ����- �������� ������
CNLayer* GetSourceLayer(void);
bool SetSourceLayer(CNLayer *src);

// ��������� �� ����
CNetwork* GetNetwork(void);
bool SetNetwork(CNetwork *src);
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

//---------------------------------------------------------------------------
#endif
