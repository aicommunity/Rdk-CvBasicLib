/* ***********************************************************
@Copyright Aleksandr Bakhshiev, 2012.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBStatisticH
#define UBStatisticH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///       
class RDK_LIB_TYPE UBStatistic: public UNet
{
protected: // 
///    
UProperty<std::string,UBStatistic, ptPubParameter> SavePath;

///    
UProperty<std::string,UBStatistic, ptPubParameter> PrefixName;

///     /    Reset
UProperty<bool,UBStatistic, ptPubParameter> SubFolderAfterResetFlag;

///        
UProperty<bool,UBStatistic, ptPubParameter> ReflectionXFlag;

///      
/// 0 -          .
/// 1 -         .
UProperty<int,UBStatistic, ptPubParameter> InputIndexMode;

//         
UProperty<bool,UBStatistic, ptPubParameter> TimeToFileNameFlag;

//        
UProperty<bool,UBStatistic, ptPubParameter> OrderIndexToFileNameFlag;

//         
UProperty<int,UBStatistic, ptPubParameter> NumSkipSteps;

public:
///  
/// 0 - bmp
/// 1 - jpeg
UProperty<int,UBStatistic, ptPubParameter> FileFormat;

///   
/// 0 -  
/// 1 -   
UProperty<int,UBStatistic, ptPubParameter> FileNameSuffix;

///         
UProperty<bool,UBStatistic, ptPubParameter> ExcludeModelFileName;

///     .      
///  "ManualStatisticSwitch"  true
UProperty<bool,UBStatistic, ptPubParameter> UseManualStatistic;

///     .      
///  "ManualStatisticSwitch"  true
UProperty<bool,UBStatistic,ptPubState> ManualStatisticSwitch;

protected: // 
UProperty<std::vector<UBitmap>, UBStatistic, ptPubInput> Input;

protected: //  
/// , ,    Reset.
bool ResetFlag;

///     
std::string CurrentPath;

///   
std::string CurrentFileName;

///     ,     
///    
int CurrentFileNameNumber;

UBitmap TempBitmap;
UBitmap Rgb24TempBitmap;

time_t OldTimeStamp;

///    
int CurrentFileIndex;

int CurrentStep;

std::vector<uint8_t> jpeg_buf;
std::vector<uint8_t> temp_buf;


public: // 
// ---------------------
//   
// ---------------------
UBStatistic(void);
virtual ~UBStatistic(void);
// ---------------------

// ---------------------
//   
// ---------------------
bool SetSavePath(const std::string &value);
bool SetPrefixName(const std::string &value);
bool SetSubFolderAfterResetFlag(bool value);
bool SetReflectionXFlag(bool value);
bool SetInputIndexMode(int value);
// ---------------------

// --------------------------
//     
// --------------------------
protected:
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

// --------------------------
//      
// --------------------------
protected:
///        
virtual bool AFSDefault(void)=0;

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFSBuild(void)=0;

///      
virtual bool AFSReset(void)=0;

///    
virtual bool AFSCalculate(void)=0;
// --------------------------
};

//        
class RDK_LIB_TYPE UBStatisticSimple: public RDK::UBStatistic
{
protected: // 
///    ,    
///  0,    
UProperty<int,UBStatisticSimple, ptPubParameter> TimeInterval;

///  
/// 0 -  
/// 1 -   (   )
UProperty<int,UBStatisticSimple, ptPubParameter> Mode;

///   
///     Calculate
UProperty<bool,UBStatisticSimple, ptPubParameter> WriteSignal;

protected: //  
unsigned long long LastSaveTime;

public: // 
// ---------------------
//   
// ---------------------
UBStatisticSimple(void);
virtual ~UBStatisticSimple(void);
// ---------------------

// ---------------------
//   
// ---------------------
bool SetTimeInterval(int value);
bool SetMode(int value);
bool SetWriteSignal(bool value);
// ---------------------

// ---------------------
//  
// ---------------------
///     
virtual UBStatisticSimple* New(void);
// ---------------------

// --------------------------
//      
// --------------------------
protected:
///        
virtual bool AFSDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFSBuild(void);

///      
virtual bool AFSReset(void);

///    
virtual bool AFSCalculate(void);

///    
virtual bool Save(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif
