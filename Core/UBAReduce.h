#ifndef UBA_REDUCE_H
#define UBA_REDUCE_H

//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///    
class RDK_LIB_TYPE UBAReduce: public UNet
{
protected: // 
///      
UProperty<int,UBAReduce, ptPubParameter> NumCols;
UProperty<int,UBAReduce, ptPubParameter> NumRows;

public: //    
///  
UProperty<UBitmap, UBAReduce, ptPubParameter> Input;

///  
UProperty<UBitmap, UBAReduce, ptPubParameter> Output;

protected: //  
UBitmap Buffer;

public: // 
// ---------------------
//   
// ---------------------
UBAReduce(void);
virtual ~UBAReduce(void);
// ---------------------

public: // 
// ---------------------
//  
// ---------------------
///     
virtual UBAReduce* New(void);

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
};
}
//---------------------------------------------------------------------------

#endif
