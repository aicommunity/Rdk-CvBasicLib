/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAColorConvertH
#define UBAColorConvertH

#include "../../../Rdk/Deploy/Include/rdk.h"
//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"

namespace RDK {

///     
class RDK_LIB_TYPE UBAColorConvert: public UNet
{
protected: // 
///   
UProperty<UBMColorModel,UBAColorConvert, ptPubParameter> NewColorModel;

public: //   
UProperty<UBitmap, UBAColorConvert, ptPubParameter> Input;

UProperty<UBitmap, UBAColorConvert, ptPubParameter> Output;

protected: //  
UBitmap Buffer;   //?

public: // 
// ---------------------
//   
// ---------------------
UBAColorConvert(void);
virtual ~UBAColorConvert(void);
// ---------------------

// ---------------------
//  
// ---------------------
UBAColorConvert* New(void);
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
};
}
//---------------------------------------------------------------------------
#endif
