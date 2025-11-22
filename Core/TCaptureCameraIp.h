/* ***********************************************************

*********************************************************** */

#ifndef TCaptureCameraIpH
#define TCaptureCameraIpH

#include "TCaptureCamera.h"

namespace RDK {
using namespace RDK;

class RDK_LIB_TYPE TCaptureCameraIp: public TCaptureCamera
{
// --------------------------
public: 	// 
// --------------------------
// 
UProperty<std::string,TCaptureCameraIp, ptPubParameter> Address;

// 
UProperty<std::string,TCaptureCameraIp, ptPubParameter> Login;

// 
UProperty<std::string,TCaptureCameraIp, ptPubParameter> Password;
// --------------------------
public: 	// 
// --------------------------
/// 
TCaptureCameraIp(void);

/// 
virtual ~TCaptureCameraIp(void);
// --------------------------
public:		//   
// --------------------------
//  
bool SetAddress(const std::string &num);

//   
bool SetLogin(const std::string &num);

//  
bool SetPassword(const std::string &num);

// --------------------------
protected:	//    
// --------------------------
///        
virtual bool ADefault2(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool ABuild2(void);

///      
virtual bool AReset2(void);

///    
virtual bool ACalculate2(void);

///    
virtual bool ASetEnableCapture1(const bool &value);

///  
virtual bool AStartCapture1(void);

///  
virtual bool AStopCapture1(void);
// --------------------------
// --------------------------
protected:	//      
// --------------------------
///        
virtual bool ADefault3(void)=0;

///     
///   
///    Reset()   Ready  true
///    
virtual bool ABuild3(void)=0;

///      
virtual bool AReset3(void)=0;

///    
virtual bool ACalculate3(void)=0;

///    
virtual bool ASetEnableCapture2(const bool &value)=0;

///  
virtual bool AStartCapture2(void)=0;

///  
virtual bool AStopCapture2(void)=0;
// --------------------------
};
}
#endif
