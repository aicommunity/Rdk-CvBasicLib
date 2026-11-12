/* ***********************************************************
@Copyright Alexander V. Bakhshiev.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBMathOperatorH
#define UBMathOperatorH

//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

//     
enum { ubmAnd=0, ubmOr=1, ubmXor=2, ubmNot=3, ubmSum=4, ubmSub=5, ubmSubAbs=6 };

//    
class RDK_LIB_TYPE UBMathOperator: public UNet
{
protected: // 
//  
UProperty<int,UBMathOperator, ptPubParameter> OperatorId;

protected: //   
///  1
UProperty<UBitmap, UBMathOperator, ptPubParameter> Input1;

///  2
UProperty<UBitmap, UBMathOperator, ptPubParameter> Input2;

///  
UProperty<UBitmap, UBMathOperator, ptPubParameter> Output;

protected: //  
UBitmap Buffer;

public: // 
// ---------------------
//   
// ---------------------
UBMathOperator(void);
virtual ~UBMathOperator(void);
// ---------------------

// ---------------------
//  
// ---------------------
//     
virtual UBMathOperator* New(void);
// ---------------------


// --------------------------
// ,   
// --------------------------
void And(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Or(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Sub(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Sum(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
// --------------------------

// --------------------------
//     
// --------------------------
protected:
//        
virtual bool ADefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool ABuild(void);

//      
virtual bool AReset(void);

//    
virtual bool ACalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif

