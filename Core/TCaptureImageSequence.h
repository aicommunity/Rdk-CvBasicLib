/* ***********************************************************

*********************************************************** */

#ifndef TCaptureImageSequenceH
#define TCaptureImageSequenceH

#include "TCapture.h"

namespace RDK {
using namespace RDK;

class RDK_LIB_TYPE TCaptureImageSequence: public TCapture
{
public: // ���������
/// ���� �� ����� � �������������
ULProperty<std::string, TCaptureImageSequence> Path;

/// �������, ��������� ������������� ���� ��� ������������� �� ����� � �������������
ULProperty<bool, TCaptureImageSequence> IsPathRelativeFromConfig;

/// ���� ������������ ���������������
ULProperty<bool, TCaptureImageSequence> RepeatFlag;

/// �������� ����� ����������� ����������� (��)
ULProperty<int, TCaptureImageSequence> CaptureDelay;

public: // ���������
/// ����� ����� ����������� � �����
ULProperty<int, TCaptureImageSequence, ptPubState> NumImages;

/// ������ �������� �����������
ULProperty<int, TCaptureImageSequence, ptPubState> CurrentImageIndex;

public: // ����� � ������
/// ������ �������� �����������
UPropertyOutputData<std::string, TCaptureImageSequence, ptPubState> CurrentImageFileName;

protected: // ��������� ����������
unsigned long long LastImageTime;

/// ������ ���� ������ �����������
std::vector<std::string> Images;

/// ����������������� ����
std::string ActualPath;

// --------------------------
public: 	// ������
// --------------------------
/// �����������
TCaptureImageSequence(void);

/// ����������
virtual ~TCaptureImageSequence(void);

// --------------------------
// ������ ���������� �����������
// --------------------------
/// ���� �� ����� � �������������
bool SetPath(const std::string &value);

/// �������, ��������� ������������� ���� ��� ������������� �� ����� � �������������
bool SetIsPathRelativeFromConfig(const bool &value);

/// ���� ������������ ���������������
bool SetRepeatFlag(const bool &value);

/// �������� ����� ����������� ����������� (��)
bool SetCaptureDelay(const int &value);
// --------------------------

// --------------------------
protected:	// ������� ������ ���������� ������
// --------------------------
/// �������� ������ ��� ����� ������ ����� ������� ����� ������
virtual TCaptureImageSequence* New(void);

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

/// ��������� ���������� ����
void CalcActualPath(const std::string &path, bool is_relative, std::string &result);
// --------------------------

};
}
#endif
