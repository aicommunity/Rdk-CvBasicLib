#ifndef RDK_UDETECTORBASE_H
#define RDK_UDETECTORBASE_H
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {
/// ������� ��������. ����� ACalculate � ����������� ����������.
/// ������� ������� ���������� ����� Detect. ����� ���������� bool � ����������� �� ���������� ����������
/// ������� �� ����� �������������� ACalculate. ��� �������������� �������� ����� ������������ � ABeforeCalculate() � AAfterCalculate()
class RDK_LIB_TYPE UDetectorBase: virtual public RDK::UNet
{
protected: // ���������

///����� �����������
ULProperty<double,UDetectorBase, ptPubParameter> ConfidenceThreshold;

///����� ������������ � ���������� ��-����������
ULProperty<double,UDetectorBase, ptPubParameter> NMSthreshold;

///�������� �� ���������� ���������� ��������� �� ������ � ������
//ULProperty<bool,UDetectorBase, ptPubParameter | ptOutput> UseRelativeCoords;

///�������� ��� �� �������� ���������� �����������
ULProperty<bool,UDetectorBase, ptPubParameter> UseDebugImage;

protected: // ����� � ������

/// ������� �����������
UPropertyInputData<UBitmap, UDetectorBase, ptPubInput | ptPubOutput> InputImage;

/// �������� ���������� �����������
UPropertyOutputData<UBitmap, UDetectorBase> DebugImage;

/// �������� �������. ���������� ����� �� ����� ��������
/// ������ �������:
/// ������ �� ���������� ��������
/// ������ 4+1+1=Left; Top; Right; Bottom; ClassReliability; ClassNumber
UPropertyOutputData<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputObjects;

/// �������� ������� ������ ��������������� � ��������� ������������
UPropertyOutputData<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputRects;

/// �������� ������� ��������������� �������
UPropertyOutputData<MDMatrix<int>, UDetectorBase, ptOutput | ptPubState> OutputClasses;

/// �������� ������� ������ ��������������
UPropertyOutputData<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputReliability;


protected: // ��������� ����������
UGraphics Graph;
UBitmap ProcessedBmp;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UDetectorBase(void);
virtual ~UDetectorBase(void);
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

// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
virtual bool ACalculate(void);

virtual bool Detect(UBitmap &bmp, MDMatrix<double> &output_rects, MDMatrix<int> &output_classes, MDMatrix<double> &reliabilities)
{ return true; };

protected:
// --------------------------


};



}

#endif



