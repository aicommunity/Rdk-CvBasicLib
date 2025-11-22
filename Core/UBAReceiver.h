/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */


#ifndef UBARECEIVER_H
#define UBARECEIVER_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///  - 
///     
class RDK_LIB_TYPE UBAReceiver: public UNet
{
protected: //  
UProperty<UBitmap, UBAReceiver, ptPubParameter> Input;

UProperty<UBitmap, UBAReceiver, ptPubParameter> Output;

public: // 
// --------------------------
//   
// --------------------------
UBAReceiver(void);
virtual ~UBAReceiver(void);
// --------------------------

// --------------------------
//    
// --------------------------
///         
virtual UBAReceiver* New(void);
// --------------------------


// --------------------------
//    
// --------------------------
protected:
///        
virtual bool ADefault(void);

///   .
virtual bool AReset(void);

///    
virtual bool ACalculate(void);
// --------------------------
};

}

#endif



