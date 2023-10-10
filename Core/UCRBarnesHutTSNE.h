#ifndef RDK_UCRBarnesHutTSNE_H
#define RDK_UCRBarnesHutTSNE_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#include <thread>


namespace RDK {
/// ��������� ��� ���������� ����������� �������������

class RDK_LIB_TYPE UCRBarnesHutTSNE: virtual public RDK::UNet
{
protected: // ���������

///���� ������������, ������������ ��� ������ ��� ������������ ������������, ����� ����������� �����, ����
/// ���������� �����-�� ���������
/// ����� ������ �����, ��� ��� ����������� ����� � ����
ULProperty<bool, UCRBarnesHutTSNE> RetrainFlag;

///����� �������� ��������� (�� 0 �� TrainingData.GetCols())
ULProperty<int, UCRBarnesHutTSNE> NumOutCoords;

/// ��������������� �������� ������ � ������
/// �� ����� ��� ����� �����/3 �������� ����
ULProperty<double, UCRBarnesHutTSNE> Perplexity;

/// ��������������� �������� ������ � ������
ULProperty<double, UCRBarnesHutTSNE> Theta;

/// ������������ ����� �������� ������ ������� ��������� �����
ULProperty<int, UCRBarnesHutTSNE> MaxIterations;

/// ������ ����� ������������� ��� ��� ������ ������������� ������������
/// �������� ������ -1 ��� ��������� �������������
ULProperty<int, UCRBarnesHutTSNE> RandomSeed;


/// ������ ����� ������������� ��� ��� ������ ������������� ������������
/// �������� ������ -1 ��� ��������� �������������
ULProperty<int, UCRBarnesHutTSNE, ptPubState> CalcActive;
protected: // ����� � ������

/// ������� ������� ��������� �������
UPropertyInputData<MDMatrix<double>,UCRBarnesHutTSNE, ptPubInput> InputComponents;

/// �������� ������� (���) ����� ���������� t-SNE
UPropertyOutputData<MDMatrix<double>,UCRBarnesHutTSNE, ptPubOutput> OutputComponents;


protected: // ���������� ���������

/// ������� double - ��������� ���������� PCA
//UPropertyOutputData<MDMatrix<double>, UCRBarnesHutTSNE, ptPubState | ptOutput> ...;

/// ������� �������������� ����������� (���) � ������ ����������� ����� (��1 ������ �������) � ����� �������
//UPropertyOutputData<MDMatrix<double>, UCRBarnesHutTSNE, ptPubState> ...;

protected: // ��������� ����������

bool TSNECalcInProcess;
float CalcProgress;

int N, D, no_dims, max_iter, rand_seed;
double perplexity, theta, *data;

int* landmarks;
double* Y;
double* costs;

std::thread *m_thread;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UCRBarnesHutTSNE(void);
virtual ~UCRBarnesHutTSNE(void);
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
virtual UCRBarnesHutTSNE* New(void);
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------

virtual bool ACalculate(void);

virtual bool AReset(void);

bool RunTSNECalculation();
void TSNECalculationThread();
void UpdateCalculationState();

};

}
#endif



