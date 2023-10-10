#ifndef RDK_UCLASSIFIERRESSAVER_H
#define RDK_UCLASSIFIERRESSAVER_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
/// ��������� ��� ���������� ����������� �������������

class RDK_LIB_TYPE UClassifierResSaver: virtual public RDK::UNet
{
protected: // ���������


/// �����, � ������� ����������� ���������� �������������.
/// ������ ����: {ProjectPath}/Result/{SaveDirectory}
ULProperty<std::string, UClassifierResSaver, ptPubParameter> SaveDirectory;

/// �������������� �� SaveDirectory ��� ��������� ������� (����� ����� �������)
/// ���� ��� - � SaveDirectory ��������� ���������� ��������� ������ { SaveDirectory_id }
ULProperty<bool, UClassifierResSaver, ptPubParameter> OverwriteSaveDirectory;

/// �������� �������. � ������ ������� ����� � ������, ��� ���������� ��������� ����� � "������"
/// � ��������� ������ � ������� ������
UPropertyInputData<std::map<int, std::string>, UClassifierResSaver, ptPubParameter> ObjectsName;

protected: // ����� � ������

/// ������� �����������
/// ������������, ���� ��������� ��������� ���� InputImages
UPropertyInputData<UBitmap, UClassifierResSaver, ptPubInput> InputImage;

/// �������� �������� �����������
/// ���� ���������, �� ����� images �� ����� �����������
UPropertyInputData<UBitmap, UClassifierResSaver, ptPubInput> ImageName;




/// ������ ������� �����������
UPropertyInputData<std::vector<UBitmap>, UClassifierResSaver, ptPubInput> InputImages;

/// ������� ������� � �������� ��������
UPropertyInputData<MDMatrix<int>,UClassifierResSaver, ptPubInput> InputClasses;

/// ������� �������. ���������� �������� �� ����� ��������, ���������� ����� � ������� �� ����� �������
/// ������ �������� - ����������� ������
UPropertyInputData<MDMatrix<double>, UClassifierResSaver, ptPubInput> InputConfidences;

protected: // ���������� ���������


ULProperty<bool, UClassifierResSaver, ptPubState> CalculateFlag;

std::string OldSaveDirectory;

protected: // ��������� ����������

UBitmap ProcessedBmp;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UClassifierResSaver(void);
virtual ~UClassifierResSaver(void);
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
virtual UClassifierResSaver* New(void);
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------

virtual bool ACalculate(void);

bool SaveImage(UBitmap& img, int class_id, MDMatrix<double>& confidences);
};

}
#endif



