/* ***********************************************************

*********************************************************** */

#ifndef TCaptureH
#define TCaptureH

#include "../../../Rdk/Deploy/Include/rdk.h"

//���������
#define RDK_CAPTURE_EMPTY 0
#define RDK_CAPTURE_CREATED 64
#define RDK_CAPTURE_INITIALIZATION 1
#define RDK_CAPTURE_CONNECTED 2
#define RDK_CAPTURE_PAUSED 4
#define RDK_CAPTURE_ACTIVE 8
#define RDK_CAPTURE_DISCONNECTED 16
#define RDK_CAPTURE_RECONNECT 32

namespace RDK {

// ������� ����� ������� ������
class RDK_LIB_TYPE TCapture: public UNet
{
public: // ���������
/// �������� Fps
ULProperty<double, TCapture> DesiredFps;

/// ������� �� �������� ���������� �������, ��
ULProperty<int, TCapture> CloseTimeout;

/// ������� ����� �����������������
ULProperty<int, TCapture> ReconnectTimeout;

/// ������� �� ����������� ��������, ��� ���������� �������� ������������ ��������� ������ ����� � ����������
ULProperty<int, TCapture> CaptureTimeout;

/// ����� �������������� ����� ���� �������
/// 0 - �� ������ ������
/// 1 - ���������� ������������ ������
/// 2 - ������� ����� �������� �������
ULProperty<int, TCapture> RestartMode;

/// �������� ���������� �������
ULProperty<int, TCapture> DesiredWidth;
ULProperty<int, TCapture> DesiredHeight;

/// ���� ��������� ������ ��������� ���������� �������
ULProperty<bool, TCapture> DesiredResolutionFlag;

public: // ���������
/// ��� ������������
ULProperty<int, TCapture, ptPubState> CameraType;

public: // ������
UPropertyOutputData<UBitmap,TCapture> OutputImage;
UPropertyOutputData<unsigned long long, TCapture> CaptureTime;
public: 	// �����
/// ���� ������� �������
ULProperty<bool, TCapture> EnableCapture;

/// ���� ������������ �������
ULProperty<bool, TCapture> Paused;

/// ���� �������� �� ��� X
ULProperty<bool, TCapture> FlipX;

/// ���� �������� �� ��� Y
ULProperty<bool, TCapture> FlipY;

/// ���� �������� ������������ ������
ULProperty<bool, TCapture> RelevData;

/// ���� ���������� ������
bool data_changed;

/// ��������� ���� ��������
ULProperty<double, TCapture> RotationAngle;

/// ������� ����������� �� ������������� ����
/// 0 - ��� ��������
/// 1 - 90
/// 2 - 180
/// 3 - 270
ULProperty<int, TCapture> FixedRotation;


public: // ������
/// ����� ������ � ������������������ (0 - ��� ������-����������)
ULProperty<unsigned long long, TCapture, ptPubState> NumFrames;

/// ������� Fps �������
ULProperty<double, TCapture, ptPubState> CaptureFps;

/// ������� �������� Fps
ULProperty<double, TCapture, ptPubState> RealFps;

/// ������� ��������� �������
ULProperty<int, TCapture, ptPubState> CaptureState;

/// ����� �������� �����
ULProperty<unsigned long long, TCapture, ptPubState> FramePosition;

/// ����� �������� �����, �
/// (������ ����������� �� Position � Fps ��� offline ����������)
ULProperty<double, TCapture, ptPubState> FrameTime;


public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
TCapture(void);
virtual ~TCapture(void);
// --------------------------

// --------------------------
// ������ ���������� ��������
// --------------------------
/// ������ �������
bool StartCapture(void);
virtual bool AStartCapture(void)=0;

/// ������� �������
bool StopCapture(void);
virtual bool AStopCapture(void)=0;

/// ����� �������
bool PauseCapture(void);
virtual bool APauseCapture(void);
// --------------------------

public:	// ������ ���������� �����������
/// ��������� ���� ��������� �������
bool SetCameraType(const int &value);
virtual bool ASetCameraType(const int &value);

/// ��������� �������� ������� ������
bool SetDesiredFps(const double &value);
virtual bool ASetDesiredFps(const double &value);

/// ������� �� �������� ���������� �������, ��
bool SetCloseTimeout(const int &value);
virtual bool ASetCloseTimeout(const double &value);

/// ������� ����� �����������������
bool SetReconnectTimeout(const int &value);
virtual bool ASetReconnectTimeout(const double &value);

bool SetCaptureTimeout(const int &value);
virtual bool ASetCaptureTimeout(const double &value);

/// ����� �������������� ����� ���� �������
/// 0 - �� ������ ������
/// 1 - ���������� ������������ ������
/// 2 - ������� ����� �������� �������
bool SetRestartMode(const int &value);
virtual bool ASetRestartMode(const double &value);

/// �������� ���������� �������
bool SetDesiredWidth(const int &value);
virtual bool ASetDesiredWidth(const double &value);
bool SetDesiredHeight(const int &value);
virtual bool ASetDesiredHeight(const double &value);

/// ���� ��������� ������ ��������� ���������� �������
bool SetDesiredResolutionFlag(const bool &value);
virtual bool ASetDesiredResolutionFlag(const bool &value);

/// ��������� ����� ������� �������
bool SetEnableCapture(const bool &value);
virtual bool ASetEnableCapture(const bool &value)=0;

/// ��������� ����� ������������ �������
bool SetPaused(const bool &value);
virtual bool ASetPaused(const bool &value);

/// ��������� �������� �� ��� X
bool SetFlipX(const bool &value);
virtual bool ASetFlipX(const bool &value);

/// ��������� �������� �� ��� Y
bool SetFlipY(const bool &value);
virtual bool ASetFlipY(const bool &value);
/// ��������� �������� ������������ ������
bool SetRelevData(const bool &value);

/// ��������� ���� ��������
bool SetRotationAngle(const double &value);
virtual bool ASetRotationAngle(const double &value);

/// ������� ����������� �� ������������� ����
/// 0 - ��� ��������
/// 1 - 90
/// 2 - 180
/// 3 - 270
bool SetFixedRotation(const int &value);
virtual bool ASetFixedRotation(const int &value);

int GetCaptureState(void);

/// ���������� ����� ����� ������ � ���������
virtual unsigned long long GetNumFrames(void) const;

/// ���������� ������ �������� ����� � ���������
virtual unsigned long long GetFramePosition(void) const;

/// ������������� ��� �������� ����� � ���������
virtual void SetFramePosition(unsigned long long value);

/// ���������� ����� ����� ������ � ���������
virtual double GetTimeDuration(void) const;

/// ���������� ������� ������� � ���������
virtual double GetTimePosition(void) const;

/// ������������� ������� ������� � ���������
virtual void SetTimePosition(double value);

/// ���������� ������� � ��������� �� value ������
virtual void ChangeRelativeFramePosition(long long value);

/// ���������� ������� � ��������� �� value ������
virtual void ChangeRelativeTimePosition(double value);

protected:	// ������� ������
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool ABuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AReset(void);

/// ��������� ������ ����� �������
virtual bool ACalculate(void);

// --------------------------
protected:	// ������� ������ ���������� ������ �������� �������
// --------------------------
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault1(void)=0;

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool ABuild1(void)=0;

/// ����� �������� ����� ��� ������ ��������
virtual bool AReset1(void)=0;

/// ��������� ������ ����� �������
virtual bool ACalculate1(void)=0;
// --------------------------
};
}
#endif
