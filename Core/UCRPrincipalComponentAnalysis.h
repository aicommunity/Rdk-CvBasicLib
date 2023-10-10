#ifndef RDK_UCRPrincipalComponentAnalysis_H
#define RDK_UCRPrincipalComponentAnalysis_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
/// ��������� ��� ���������� ����������� �������������

class RDK_LIB_TYPE UCRPrincipalComponentAnalysis: virtual public RDK::UNet
{
public: // ���������

///���� ������������, ������������ ��� ������ ��� ������������ ������������, ����� ����������� PCA ����
/// ���������� �����-�� ���������
ULProperty<bool, UCRPrincipalComponentAnalysis> RetrainFlag;

///����� �������� ��������� (�� 0 �� TrainingData.GetCols())
ULProperty<int, UCRPrincipalComponentAnalysis> OutComponents;

protected: // ����� � ������

/// ������� ������� �� ������������������ ������� ��� �������� PCA
UPropertyInputData<MDMatrix<double>,UCRPrincipalComponentAnalysis, ptPubInput> TrainingData;

/// ������� ������ ��� ���������� PCA, �� ������ ���������� TrainingData
UPropertyInputData<MDMatrix<double>,UCRPrincipalComponentAnalysis, ptPubInput> EncodingData;


public: // ���������� ���������

/// ������� double - ��������� ���������� PCA
UPropertyOutputData<MDMatrix<double>, UCRPrincipalComponentAnalysis, ptPubState | ptOutput> PCAResult;

/// ������� �������������� ����������� (���) � ������ ����������� ����� (��1 ������ �������) � ����� �������
UPropertyOutputData<MDMatrix<double>, UCRPrincipalComponentAnalysis, ptPubState> PCA_X;

protected: // ��������� ����������

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UCRPrincipalComponentAnalysis(void);
virtual ~UCRPrincipalComponentAnalysis(void);
// --------------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ---------------------


// ---------------------
// ������ ���������� ����������� ���������
// ---------------------
// ---------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
// �������� ������ ��� ����� ������ ����� ������� ����� ������
virtual UCRPrincipalComponentAnalysis* New(void);
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------

virtual bool ACalculate(void);

virtual bool AReset(void);

bool TrainPCA(void);
bool ApplyPCA(void);
};

}
#endif



