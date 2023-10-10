/* ***********************************************************

*********************************************************** */

#ifndef TCaptureCameraH
#define TCaptureCameraH

#include "TCapture.h"

namespace RDK {
using namespace RDK;

class RDK_LIB_TYPE TCaptureCamera: public TCapture
{
// --------------------------
public: 	// ������
// --------------------------
/// �����������
TCaptureCamera(void);

/// ����������
virtual ~TCaptureCamera(void);

// --------------------------
protected:	// ������� ������ ���������� ������
// --------------------------
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault1(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool ABuild1(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AReset1(void);

/// ��������� ������ ����� �������
virtual bool ACalculate1(void);

/// ��������� ����� ������� �������
virtual bool ASetEnableCapture(const bool &value);

/// ������ �������
virtual bool AStartCapture(void);

/// ������� �������
virtual bool AStopCapture(void);
// --------------------------
// --------------------------
protected:	// ������� ������ ���������� ������ �������� �������
// --------------------------
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault2(void)=0;

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool ABuild2(void)=0;

/// ����� �������� ����� ��� ������ ��������
virtual bool AReset2(void)=0;

/// ��������� ������ ����� �������
virtual bool ACalculate2(void)=0;

/// ��������� ����� ������� �������
virtual bool ASetEnableCapture1(const bool &value)=0;

/// ������ �������
virtual bool AStartCapture1(void)=0;

/// ������� �������
virtual bool AStopCapture1(void)=0;
// --------------------------
};
}
#endif