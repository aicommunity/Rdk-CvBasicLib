/* ***********************************************************
@Copyright Alexsandr Nikolskiy, 2011.
E-mail:        alexxxniko@gmail.com
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBShowRectH
#define UBShowRectH

#include "UBAShowObjects.h"

namespace RDK {

//   -
class RDK_LIB_TYPE UBShowRect: public UBAShowObjects
{
protected: //  
///       
UProperty<MDMatrix<double>, UBShowRect, ptPubParameter> MatrixZones;

/// Rect zones vector
UProperty<std::vector<UBRect>, UBShowRect, ptPubParameter> RectZones;

/// Show flags
UProperty<MDMatrix<int>, UBShowRect, ptPubParameter> ShowFlags;

public: // 
// ---------------------
//   
// ---------------------
UBShowRect(void);
virtual ~UBShowRect(void);
// ---------------------

// ---------------------
//  
// ---------------------
///     
virtual UBShowRect* New(void);
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

}
//---------------------------------------------------------------------------
#endif
