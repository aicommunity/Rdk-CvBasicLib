/* ***********************************************************

*********************************************************** */

#ifndef TCaptureImageSequenceH
#define TCaptureImageSequenceH

#include "TCapture.h"

namespace RDK {
using namespace RDK;

class RDK_LIB_TYPE TCaptureImageSequence: public TCapture
{
public: // 
///     
UProperty<std::string, TCaptureImageSequence, ptPubParameter> Path;

/// ,         
UProperty<bool, TCaptureImageSequence, ptPubParameter> IsPathRelativeFromConfig;

///   
UProperty<bool, TCaptureImageSequence, ptPubParameter> RepeatFlag;

///     ()
UProperty<int, TCaptureImageSequence, ptPubParameter> CaptureDelay;

public: // 
///     
UProperty<int, TCaptureImageSequence, ptPubState> NumImages;

///   
UProperty<int, TCaptureImageSequence, ptPubState> CurrentImageIndex;

public: //   
///   
UProperty<std::string, TCaptureImageSequence, ptPubState> CurrentImageFileName;

protected: //  
unsigned long long LastImageTime;

///    
std::vector<std::string> Images;

///  
std::string ActualPath;

// --------------------------
public: 	// 
// --------------------------
/// 
TCaptureImageSequence(void);

/// 
virtual ~TCaptureImageSequence(void);

// --------------------------
//   
// --------------------------
///     
bool SetPath(const std::string &value);

/// ,         
bool SetIsPathRelativeFromConfig(const bool &value);

///   
bool SetRepeatFlag(const bool &value);

///     ()
bool SetCaptureDelay(const int &value);
// --------------------------

// --------------------------
protected:	//    
// --------------------------
///         
virtual TCaptureImageSequence* New(void);

///        
virtual bool ADefault1(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool ABuild1(void);

///      
virtual bool AReset1(void);

///    
virtual bool ACalculate1(void);

///    
virtual bool ASetEnableCapture(const bool &value);

///  
virtual bool AStartCapture(void);

///  
virtual bool AStopCapture(void);

///   
void CalcActualPath(const std::string &path, bool is_relative, std::string &result);
// --------------------------

};
}
#endif
