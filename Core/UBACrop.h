/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBACropH
#define UBACropH
//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///     
class RDK_LIB_TYPE UBACrop: public UNet
{
protected: // 

public: //   
UProperty<UBitmap, UBACrop, ptPubParameter> Input;

/// ,      
///    ,       
/// <left, top, right, bottom>.
UProperty<MDMatrix<int>, UBACrop, ptPubInput | ptParameter> CropRect;

UProperty<UBitmap, UBACrop, ptPubParameter> Output;

protected: //  
UBitmap Buffer;   //?

public: // 
// ---------------------
//   
// ---------------------
UBACrop(void);
virtual ~UBACrop(void);
// ---------------------

// ---------------------
//   
// ---------------------
// ---------------------

// ---------------------
//  
// ---------------------
UBACrop* New(void);
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
