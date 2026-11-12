/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAMovingDetectorH
#define UBAMovingDetectorH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///      
class RDK_LIB_TYPE UBAMovingDetector: public UNet
{
public: // 
///    
int HistorySize;

protected: // 
///   
UProperty<UBitmap, UBAMovingDetector, ptPubParameter> Input;

///  
UBRect* MovedObjects;

///  
UBitmap* LocalContrastedImages;

///   
int CurrentHistorySize;

///    
int CurrentFirstHistoryIndex;

public: // 
// --------------------------
//   
// --------------------------
UBAMovingDetector(void);
~UBAMovingDetector(void);
// --------------------------

// --------------------------
//   
// --------------------------
///    
int GetHistorySize(void) const;
bool SetHistorySize(int value);
// --------------------------

// --------------------------
//    
// --------------------------
///   
const UBitmap* GetInputData(void) const;

///  
const UBRect* GetMovedObjects(void) const;

///  
const UBitmap* GetLocalContrastedImages(void) const;

///   
int GetCurrentHistorySize(void) const;

///    
int GetCurrentFirstHistoryIndex(void) const;
// ---------------------

// --------------------------
//     
// --------------------------
protected:
///  
void HistoryShift(void);

///        
virtual bool ADefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool ABuild(void);

///   .
virtual bool AReset(void);

///    
virtual bool ACalculate(void);
// --------------------------

// --------------------------
//     
// --------------------------
protected:
///        
virtual bool AFCDefault(void)=0;

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFCBuild(void)=0;

///   .
virtual bool AFCReset(void)=0;

///    
virtual bool AFCCalculate(void)=0;
// --------------------------
};

//     
//    
// "A real-time object detecting and tracking system for outdoor night surveillance"
// Kaiqi Huang, Liangsheng Wang, Tieniu Tan, Steve Maybank
class RDK_LIB_TYPE UBANightMovingDetector: public UBAMovingDetector
{
public: // 
///   
int BlockWidth, BlockHeight;

///    
double AdaptiveThresholdPercent;

///  ,   ,
///  
double MoveDetectionPercent;

/// 
double T1;

///    
double Tr;

///   
/// 0 -  
/// 1 -    abs(a-b)/max(a,b)
int MovingDetectionMode;

///   
int HistLeftRange, HistRightRange;

///    
/// 0 -  
/// 1 - 
int MovingFrameMode;

protected: // 
///  
int NumBlocks;

int XBlocks,YBlocks;

///   
double* CL;

///  
double* ML;

///  
double* SigmaL;

///   
UBitmap DiffImage;

///     
UBitmap MovedImage;

/// 
UBHistogram Histogram;

///   
UBRect* ContrastGrid;

///   
UBRect* MovedGrid;


protected: //   
///  
int Width,Height;

protected: //      
protected: //       
///  
double* MCm;
double* ICm;

///     
double* T;
double TT;


protected: //      
NCC2D Correlation;

public: // 
// --------------------------
//   
// --------------------------
UBANightMovingDetector(void);
~UBANightMovingDetector(void);
// --------------------------

// --------------------------
//   
// --------------------------
///   
int GetBlockWidth(void) const;
bool SetBlockWidth(int value);
int GetBlockHeight(void) const;
bool SetBlockHeight(int value);

///   
int GetMovingDetectionMode(void) const;
bool SetMovingDetectionMode(int value);

///   
int GetHistLeftRange(void) const;
bool SetHistLeftRange(int value);
int GetHistRightRange(void) const;
bool SetHistRightRange(int value);

///    
int GetMovingFrameMode(void) const;
bool SetMovingFrameMode(int value);
// --------------------------

// --------------------------
//    
// --------------------------
///     
const UBitmap& GetMovedImage(void) const;

///  
int GetNumBlocks(void) const;

///   
const double* GetCL(void) const;

///  
const double* GetML(void) const;

///  
const double* GetSigmaL(void) const;

///   
const UBitmap& GetDiffImage(void) const;

/// 
const UBHistogram& GetHistogram(void) const;

///   
const UBRect* GetContrastGrid(void) const;
const UBRect& GetContrastGrid(int i) const;

///   
const UBRect* GetMovedGrid(void) const;
const UBRect& GetMovedGrid(int i) const;
// --------------------------

// ---------------------
//  
// ---------------------
///     
UBANightMovingDetector* New(void);
// ---------------------

// ---------------------
//   
// ---------------------
protected:
///    
bool SetRes(int width, int height);

///   
virtual bool CalcLocalContrasting(void);

///    
virtual bool CalcLocalMap(void);

///   
virtual bool CalcMovedObjects(void);

///       
virtual bool CalcNormalMovedObjects(void);

///   
virtual bool CalcAdaptiveThreshold(void);
// ---------------------

// --------------------------
//     
// --------------------------
protected:
///        
virtual bool AFCDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFCBuild(void);

///   .
virtual bool AFCReset(void);

///    
virtual bool AFCCalculate(void);
// --------------------------

};


//
class RDK_LIB_TYPE UBACollateMovingDetector: public UBAMovingDetector
{
public:
///   
UBitmap DiffImage;

public: // 
// --------------------------
//   
// --------------------------
UBACollateMovingDetector(void);
~UBACollateMovingDetector(void);
// --------------------------

// ---------------------
//  
// ---------------------
///     
UBACollateMovingDetector* New(void);
// ---------------------

// --------------------------
//     
// --------------------------
protected:
///        
virtual bool AFCDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFCBuild(void);

///   .
virtual bool AFCReset(void);

///    
virtual bool AFCCalculate(void);
// --------------------------
};

}

#endif
