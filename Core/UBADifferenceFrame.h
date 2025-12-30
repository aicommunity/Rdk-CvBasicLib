/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBADifferenceFrameH
#define UBADifferenceFrameH

#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

///     
class RDK_LIB_TYPE UBADifferenceFrame: public UNet
{
public: //    
///   1
UProperty<UBitmap, UBADifferenceFrame, ptPubParameter> Input1;

///   2
UProperty<UBitmap, UBADifferenceFrame, ptPubParameter> Input2;

protected:
///  
UProperty<UBitmap, UBADifferenceFrame, ptPubParameter> Output;


public: // 
// ---------------------
//   
// ---------------------
UBADifferenceFrame(void);
virtual ~UBADifferenceFrame(void);
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
virtual bool AFDiffDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFDiffBuild(void);

///      
virtual bool AFDiffReset(void);

///    
virtual bool AFDiffCalculate(void);
// --------------------------
};

///    
class RDK_LIB_TYPE UBADifferenceFrameSimple: public UBADifferenceFrame
{
public: // 
// ---------------------
//  
// ---------------------
//     
virtual UBADifferenceFrameSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &deduction, UBitmap &output);
// ---------------------

// --------------------------
//       
// --------------------------
protected:
///        
virtual bool AFDiffDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFDiffBuild(void);

///      
virtual bool AFDiffReset(void);

///    
virtual bool AFDiffCalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif

