/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAFlipImageH
#define UBAFlipImageH
//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///    
class RDK_LIB_TYPE UBAFlipImage: public UNet
{
public: // 
///  
/// 0 -  
/// 1 -   
/// 2 -   
UProperty<int, UBAFlipImage, ptPubParameter> Mode;

protected: //    
///  
UProperty<UBitmap, UBAFlipImage, ptPubParameter> Input;

///  
UProperty<UBitmap, UBAFlipImage, ptPubParameter> Output;

protected: //  
UBitmap Buffer;

public: // 
// ---------------------
//   
// ---------------------
UBAFlipImage(void);
virtual ~UBAFlipImage(void);
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
class RDK_LIB_TYPE UBAFlipImageSimple: public UBAFlipImage
{
public: // 
// ---------------------
//  
// ---------------------
///     
virtual UBAFlipImageSimple* New(void);

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

