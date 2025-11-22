/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBARotateH
#define UBARotateH
//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///    
class RDK_LIB_TYPE UBARotate: public UNet
{
public: // 
///   ()
UProperty<float, UBARotate, ptPubParameter> Angle;

///    ( ,  !)
//UProperty<bool, UBARotate, ptPubParameter> Enlarge;
bool Enlarge;

protected: //    
///  
UProperty<UBitmap, UBARotate, ptPubParameter> Input;

///  
UProperty<UBitmap, UBARotate, ptPubParameter> Output;

protected: //  
UBitmap Buffer;

public: // 
// ---------------------
//   
// ---------------------
UBARotate(void);
virtual ~UBARotate(void);
// ---------------------

// ---------------------
//   
// ---------------------
///   ()
float GetAngle(void) const;
bool SetAngle(const float &angle);

///  
bool GetEnlarge(void) const;
bool SetEnlarge(const bool &enlarge);
// ---------------------

// ---------------------
// 
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, UBitmap &output, float angle, bool enlarge=false);
// ---------------------

// --------------------------
//    
// --------------------------
protected:
virtual bool BCalculate(UBitmap &input, UBitmap &output)=0;

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

///     
class RDK_LIB_TYPE UBARotateSimple: public UBARotate
{
public: // 
// ---------------------
//  
// ---------------------
///     
virtual UBARotateSimple* New(void);

virtual bool BCalculate(UBitmap &input, UBitmap &output);
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
//---------------------------------------------------------------------------
#endif

