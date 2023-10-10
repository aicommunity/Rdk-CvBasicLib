#ifndef RDK_UCLASSIFIERBASE_H
#define RDK_UCLASSIFIERBASE_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
/// ������� �������������. ����� ACalculate � ����������� ����������.
/// ������� ������� ���������� ����� classifyBitmap. ����� ���������� bool � ����������� �� ���������� ����������
/// ������� �� ����� �������������� ACalculate. ��� �������������� �������� ����� ������������ � ABeforeCalculate() � AAfterCalculate()

class RDK_LIB_TYPE UClassifierBase: virtual public RDK::UNet
{
protected: // ���������

///����� �����������: ���� ����� �� ��������� ������ �����������, �� �� ������������ � 0, ��� ������ ������������ � 0.
ULProperty<double,UClassifierBase, ptPubParameter> ConfidenceThreshold;

/// ���������� ������� �������� (����� ������ ����� � �������)
ULProperty<int,UClassifierBase, ptPubParameter> NumClasses;

protected: // ����� � ������

/// ������� �����������
/// ������������, ���� ��������� ��������� ���� InputImages
UPropertyInputData<UBitmap,UClassifierBase, ptPubInput | ptPubOutput> InputImage;

/// ������ ������� �����������
UPropertyInputData<std::vector<UBitmap>, UClassifierBase, ptPubInput | ptPubOutput> InputImages;

/// �������� ������� � �������� ��������
UPropertyOutputData<MDMatrix<int>,UClassifierBase, ptPubOutput> OutputClasses;

/// �������� �������. ���������� �������� �� ����� ��������, ���������� ����� � ������� �� ����� �������
/// ������ �������� - ����������� ������
UPropertyOutputData<MDMatrix<double>, UClassifierBase, ptPubOutput> OutputConfidences;


protected: // ���������� ���������
/// �����, ����������� �� �������������, �������
ULProperty<double,UClassifierBase, ptPubState> ClassificationTime;


protected: // ��������� ����������
UBitmap ProcessedBmp;


public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UClassifierBase(void);
virtual ~UClassifierBase(void);
// --------------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ---------------------
bool SetNumClasses(const int &value);

// ---------------------
// ������ ���������� ����������� ���������
// ---------------------
// ---------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------

// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
virtual bool ACalculate(void);

//������������� ������ �����������. ������� ������� ���������� ������ �����
virtual bool ClassifyBitmap(UBitmap &bmp, MDVector<double> &output_confidences, double conf_thresh, int &class_id, bool &is_classified)
{ return true; };

protected:
// --------------------------


};





}
#endif



