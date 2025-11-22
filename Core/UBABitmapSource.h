/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBABitmapSource_H
#define UBABitmapSource_H

#include "../../Rdk-CvBasicLib/Core/UBASource.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///   -  
class RDK_LIB_TYPE UBABitmapSource: public UNet
{
protected: // 
///   
UProperty<std::vector<UBitmapParam>,UBABitmapSource, ptPubParameter> SourceParamaters;

UProperty<UBitmap, UBABitmapSource, ptPubParameter> Output;

protected: //  

public: // 
// ---------------------
//   
// ---------------------
UBABitmapSource(void);
virtual ~UBABitmapSource(void);
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
// --------------------------
};

///  - 
///  -,     
class RDK_LIB_TYPE UBABitmapSourceSimple: public UBABitmapSource
{
protected: // 

public: // 
// ---------------------
//   
// ---------------------
UBABitmapSourceSimple(void);
virtual ~UBABitmapSourceSimple(void);
// ---------------------

// ---------------------
//  
// ---------------------
///     
virtual UBABitmapSourceSimple* New(void);

bool BCalculate(void);
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
// --------------------------
};

///   ,   
/// Under construction
class RDK_LIB_TYPE UBABitmapSourceFile: public UBABitmapSource
{
protected: // 

public: // 
// ---------------------
//   
// ---------------------
UBABitmapSourceFile(void);
virtual ~UBABitmapSourceFile(void);
// ---------------------

// ---------------------
//  
// ---------------------
///     
virtual UBABitmapSourceFile* New(void);
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
// --------------------------
};


///  - 
class RDK_LIB_TYPE UBASourceFreezeFrame: public UBASource
{
protected: //   
UProperty<bool, UBASourceFreezeFrame, ptPubInput | ptState> FreezeFlag;

protected:

public: // 
// --------------------------
//   
// --------------------------
UBASourceFreezeFrame(void);
virtual ~UBASourceFreezeFrame(void);
// --------------------------

protected:
// --------------------------
//   
// --------------------------
// --------------------------

// --------------------------
//    
// --------------------------
///         
virtual UBASourceFreezeFrame* New(void);
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

