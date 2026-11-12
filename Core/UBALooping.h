/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBALoopingH
#define UBALoopingH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

//    
class RDK_LIB_TYPE UBALooping: public UNet
{
protected: //    
///  
UProperty<UBitmap, UBALooping, ptPubParameter> Input;

///  
UProperty<UBitmap, UBALooping, ptPubParameter> Output;

public: // 
// --------------------------
//   
// --------------------------
UBALooping(void);
virtual ~UBALooping(void);
// --------------------------

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
class RDK_LIB_TYPE UBALoopingSimple: public UBALooping
{
public: // 
// ---------------------
//  
// ---------------------
//     
virtual UBALoopingSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
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
class RDK_LIB_TYPE UBALoopingSobel: public UBALooping
{
public: // 
// ---------------------
//  
// ---------------------
//     
virtual UBALoopingSobel* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
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
