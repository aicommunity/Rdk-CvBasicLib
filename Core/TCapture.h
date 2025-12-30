/* ***********************************************************

*********************************************************** */

#ifndef TCaptureH
#define TCaptureH

#include "../../../Rdk/Deploy/Include/rdk.h"

//
#define RDK_CAPTURE_EMPTY 0
#define RDK_CAPTURE_CREATED 64
#define RDK_CAPTURE_INITIALIZATION 1
#define RDK_CAPTURE_CONNECTED 2
#define RDK_CAPTURE_PAUSED 4
#define RDK_CAPTURE_ACTIVE 8
#define RDK_CAPTURE_DISCONNECTED 16
#define RDK_CAPTURE_RECONNECT 32

namespace RDK {

//    
class RDK_LIB_TYPE TCapture: public UNet
{
public: // 
///  Fps
UProperty<double, TCapture, ptPubParameter> DesiredFps;

///     , 
UProperty<int, TCapture, ptPubParameter> CloseTimeout;

///   
UProperty<int, TCapture, ptPubParameter> ReconnectTimeout;

///    ,         
UProperty<int, TCapture, ptPubParameter> CaptureTimeout;

///     
/// 0 -   
/// 1 -   
/// 2 -    
UProperty<int, TCapture, ptPubParameter> RestartMode;

///   
UProperty<int, TCapture, ptPubParameter> DesiredWidth;
UProperty<int, TCapture, ptPubParameter> DesiredHeight;

///      
UProperty<bool, TCapture, ptPubParameter> DesiredResolutionFlag;

public: // 
///  
UProperty<int, TCapture, ptPubState> CameraType;

public: // 
UProperty<UBitmap,TCapture, ptPubParameter> OutputImage;
UProperty<unsigned long long, TCapture, ptPubParameter> CaptureTime;
public: 	// 
///   
UProperty<bool, TCapture, ptPubParameter> EnableCapture;

///   
UProperty<bool, TCapture, ptPubParameter> Paused;

///     X
UProperty<bool, TCapture, ptPubParameter> FlipX;

///     Y
UProperty<bool, TCapture, ptPubParameter> FlipY;

///    
UProperty<bool, TCapture, ptPubParameter> RelevData;

///   
bool data_changed;

///   
UProperty<double, TCapture, ptPubParameter> RotationAngle;

///     
/// 0 -  
/// 1 - 90
/// 2 - 180
/// 3 - 270
UProperty<int, TCapture, ptPubParameter> FixedRotation;


public: // 
///     (0 -  -)
UProperty<unsigned long long, TCapture, ptPubState> NumFrames;

///  Fps 
UProperty<double, TCapture, ptPubState> CaptureFps;

///   Fps
UProperty<double, TCapture, ptPubState> RealFps;

///   
UProperty<int, TCapture, ptPubState> CaptureState;

///   
UProperty<unsigned long long, TCapture, ptPubState> FramePosition;

///   , 
/// (   Position  Fps  offline )
UProperty<double, TCapture, ptPubState> FrameTime;


public: // 
// --------------------------
//   
// --------------------------
TCapture(void);
virtual ~TCapture(void);
// --------------------------

// --------------------------
//   
// --------------------------
///  
bool StartCapture(void);
virtual bool AStartCapture(void)=0;

///  
bool StopCapture(void);
virtual bool AStopCapture(void)=0;

///  
bool PauseCapture(void);
virtual bool APauseCapture(void);
// --------------------------

public:	//   
///    
bool SetCameraType(const int &value);
virtual bool ASetCameraType(const int &value);

///    
bool SetDesiredFps(const double &value);
virtual bool ASetDesiredFps(const double &value);

///     , 
bool SetCloseTimeout(const int &value);
virtual bool ASetCloseTimeout(const double &value);

///   
bool SetReconnectTimeout(const int &value);
virtual bool ASetReconnectTimeout(const double &value);

bool SetCaptureTimeout(const int &value);
virtual bool ASetCaptureTimeout(const double &value);

///     
/// 0 -   
/// 1 -   
/// 2 -    
bool SetRestartMode(const int &value);
virtual bool ASetRestartMode(const double &value);

///   
bool SetDesiredWidth(const int &value);
virtual bool ASetDesiredWidth(const double &value);
bool SetDesiredHeight(const int &value);
virtual bool ASetDesiredHeight(const double &value);

///      
bool SetDesiredResolutionFlag(const bool &value);
virtual bool ASetDesiredResolutionFlag(const bool &value);

///    
bool SetEnableCapture(const bool &value);
virtual bool ASetEnableCapture(const bool &value)=0;

///    
bool SetPaused(const bool &value);
virtual bool ASetPaused(const bool &value);

///     X
bool SetFlipX(const bool &value);
virtual bool ASetFlipX(const bool &value);

///     Y
bool SetFlipY(const bool &value);
virtual bool ASetFlipY(const bool &value);
///    
bool SetRelevData(const bool &value);

///   
bool SetRotationAngle(const double &value);
virtual bool ASetRotationAngle(const double &value);

///     
/// 0 -  
/// 1 - 90
/// 2 - 180
/// 3 - 270
bool SetFixedRotation(const int &value);
virtual bool ASetFixedRotation(const int &value);

int GetCaptureState(void);

///      
virtual unsigned long long GetNumFrames(void) const;

///      
virtual unsigned long long GetFramePosition(void) const;

///      
virtual void SetFramePosition(unsigned long long value);

///      
virtual double GetTimeDuration(void) const;

///     
virtual double GetTimePosition(void) const;

///     
virtual void SetTimePosition(double value);

///      value 
virtual void ChangeRelativeFramePosition(long long value);

///      value 
virtual void ChangeRelativeTimePosition(double value);

protected:	//  
///        
virtual bool ADefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool ABuild(void);

///      
virtual bool AReset(void);

///    
virtual bool ACalculate(void);

// --------------------------
protected:	//      
// --------------------------
///        
virtual bool ADefault1(void)=0;

///     
///   
///    Reset()   Ready  true
///    
virtual bool ABuild1(void)=0;

///      
virtual bool AReset1(void)=0;

///    
virtual bool ACalculate1(void)=0;
// --------------------------
};
}
#endif
