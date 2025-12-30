/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBALabelingH
#define UBALabelingH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///     
class RDK_LIB_TYPE UBALabeling: public UNet
{
protected: //    
UProperty<UBitmap, UBALabeling, ptPubParameter> Input;

///  
UProperty<MDMatrix<double>, UBALabeling, ptPubOutput | ptState> Zones;


public: // 
// ---------------------
//   
// ---------------------
UBALabeling(void);
virtual ~UBALabeling(void);
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
virtual bool AFBgDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFBgBuild(void);

///      
virtual bool AFBgReset(void);

///    
virtual bool AFBgCalculate(void);
// --------------------------
};

///    
class RDK_LIB_TYPE UBALabelingSimple: public UBALabeling
{
protected: // 

protected: //  

public: // 
// ---------------------
//   
// ---------------------
UBALabelingSimple(void);
virtual ~UBALabelingSimple(void);
// ---------------------

// ---------------------
//  
// ---------------------
//     
virtual UBALabelingSimple* New(void);

void LCalculate(UBitmap &bmp, MDMatrix<double> &output);


// ---------------------

// --------------------------
//       
// --------------------------
protected:
///        
virtual bool AFBgDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFBgBuild(void);

///      
virtual bool AFBgReset(void);

///    
virtual bool AFBgCalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif

