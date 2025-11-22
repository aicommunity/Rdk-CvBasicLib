/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBABinarizationH
#define UBABinarizationH
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

///     
class RDK_LIB_TYPE UBABinarization: public UNet
{
public: //    
///  
UProperty<UBitmap, UBABinarization, ptPubParameter> Input;

///  
UProperty<UBitmap, UBABinarization, ptPubParameter> Output;


public: // 
// ---------------------
//   
// ---------------------
UBABinarization(void);
virtual ~UBABinarization(void);
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
virtual bool AFBgDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFBgBuild(void);

///      
virtual bool AFBgReset(void);

///    
virtual bool AFBgCalculate(void);
// --------------------------
};

///    
class RDK_LIB_TYPE UBABinarizationSimple: public UBABinarization
{
protected: // 
///   
UProperty<UColorT, UBABinarizationSimple, ptPubParameter> Threshold;

protected: //  

public: // 
// ---------------------
//   
// ---------------------
UBABinarizationSimple(void);
virtual ~UBABinarizationSimple(void);
// ---------------------

// ---------------------
//  
// ---------------------
//     
virtual UBABinarizationSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------

// --------------------------
//       
// --------------------------
protected:
///        
virtual bool AFBgDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFBgBuild(void);

///      
virtual bool AFBgReset(void);

///    
virtual bool AFBgCalculate(void);
// --------------------------
};



//----------------------------------------------------------------------------
///      
///
//----------------------------------------------------------------------------

class RDK_LIB_TYPE UBABinarizationSimpleAdaptiveThreshold: public UBABinarization
{
protected: // 
///   
UProperty<UBitmap, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> Threshold;

///
UProperty<UBitmap, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> Background;

UProperty<double, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> KAlpha;
UProperty<double, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> KGamma;

///  ,       1
UProperty<int, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> startThreshold;

UProperty<UBitmap, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> counterFG;

UProperty<int, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> stableBGflag;

///  
UProperty<int, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> modeTypes;

UProperty<UBitmap, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> counterBG;

UProperty<int, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> unstableFlag;

///  - 
UProperty<UBitmap, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> Threshold2;
UProperty<UBitmap, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> output2;

///     
UProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> maxDinamThreshold;

/// 
UProperty<UBitmap, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> invThreshold;

///  ,       
///    0-1, 1-2... 13-14, >14.
std::vector<double> ThresholdStats;

///  ,  
UProperty<int, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> countFirstCleanBgFrame;

///   
UProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> firstThTypes;

///     
UProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold, ptPubParameter> minDinamThreshold;

/// ,   
int nCounter;

protected: //  

public: // 
// ---------------------
//   
// ---------------------
UBABinarizationSimpleAdaptiveThreshold(void);
virtual ~UBABinarizationSimpleAdaptiveThreshold(void);
// ---------------------

// ---------------------
//  
// ---------------------
//     
virtual UBABinarizationSimpleAdaptiveThreshold* New(void);

bool BCalculate0(UBitmap &Background, UBitmap &input, UBitmap &output);
bool BCalculate1(UBitmap &Background, UBitmap &input, UBitmap &Threshold, UBitmap &output, UBitmap &counterFG);
bool BCalculate2(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                 UBitmap &output, UBitmap &counterFG,UBitmap &counterBG);
/// 
bool BCalculate3(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                 UBitmap &output, UBitmap &counterFG,UBitmap &counterBG);
///    countFirstCleanBgFrame  
bool BCalculateFirstThreshold1(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                               UBitmap &output);
///    countFirstCleanBgFrame  
bool BCalculateFirstThreshold2(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                               UBitmap &output);
// ---------------------

// --------------------------
//       
// --------------------------
protected:
///        
virtual bool AFBgDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFBgBuild(void);

///      
virtual bool AFBgReset(void);

///    
virtual bool AFBgCalculate(void);
// --------------------------
};




//----------------------------------------------------------------------------
///     
//----------------------------------------------------------------------------
class RDK_LIB_TYPE UBABinarizationOtsu: public UBABinarization
{
protected: // 
// ,       
UProperty<int, UBABinarizationOtsu, ptPubParameter> minThreshold;
///  - 
UProperty<UBitmap, UBABinarizationOtsu, ptPubParameter> Mask;


//int minThreshold;
//   
//UProperty<UColorT, UBABinarizationSimple, ptPubParameter> Threshold;

protected: //  

public: // 
// ---------------------
//   
// ---------------------
UBABinarizationOtsu(void);
virtual ~UBABinarizationOtsu(void);
// ---------------------

// ---------------------
//  
// ---------------------
//     
virtual UBABinarizationOtsu* New(void);

bool BCalculate(UBitmap &input, UBitmap &output, UBitmap &mask);
// ---------------------

// --------------------------
//       
// --------------------------
protected:
///        
virtual bool AFBgDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFBgBuild(void);

///      
virtual bool AFBgReset(void);

///    
virtual bool AFBgCalculate(void);
// --------------------------
};


}
//---------------------------------------------------------------------------
#endif

