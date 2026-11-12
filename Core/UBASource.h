/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBASOURCE_H
#define UBASOURCE_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///  - 
class RDK_LIB_TYPE UBASource: public UNet
{
public:
UProperty<UBitmap, UBASource, ptPubParameter> Output;
UProperty<UBitmap, UBASource, ptPubParameter> Input;

public: // 
// --------------------------
//   
// --------------------------
UBASource(void);
virtual ~UBASource(void);
// --------------------------

protected:
// --------------------------
//   
// --------------------------
///    
bool SetOutputData(int index, const UBitmap &bitmap);
// --------------------------

// --------------------------
//    
// --------------------------
///         
virtual UBASource* New(void);
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



