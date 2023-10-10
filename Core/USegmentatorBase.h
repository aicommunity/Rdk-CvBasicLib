#ifndef RDK_USEGMENTATORBASE_H
#define RDK_USEGMENTATORBASE_H
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {
/// ������� �����������.  ����� ACalculate � ����������� ����������.
/// ������� ������� ���������� ����� Inference. ����� ���������� bool � ����������� �� ���������� ����������
/// ������� �� ����� �������������� ACalculate. ��� �������������� �������� ����� ������������ � ABeforeCalculate() � AAfterCalculate()
class RDK_LIB_TYPE USegmentatorBase: virtual public RDK::UNet
{
protected: // ����� � ������
/// ������� �����������
UPropertyInputData<UBitmap, USegmentatorBase> InputImage;

/// �������� ����������� c �������������� ������
UPropertyOutputData<UBitmap, USegmentatorBase> OutputImage;


protected: // ���������� ���������
/// ������������ ������� � ������
ULProperty<std::vector< UColorT>,USegmentatorBase, ptPubParameter> ClassColors;


protected: // ��������� ����������
UBitmap ProcessedBmp;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
USegmentatorBase(void);
virtual ~USegmentatorBase(void);
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

virtual bool Inference(UBitmap &bmp, UBitmap &mask) { return true; };

protected:
// --------------------------


};



}

#endif



