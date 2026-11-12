/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBADATA_SIMULATOR_H
#define UBADATA_SIMULATOR_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {


///    
class RDK_LIB_TYPE UBADataSimulator: public UNet
{
protected: // 

protected: //  

public: // 
// ---------------------
//   
// ---------------------
UBADataSimulator(void);
virtual ~UBADataSimulator(void);
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

///      
class RDK_LIB_TYPE UBADataSimulatorSimple: public UBADataSimulator
{
protected: // 
///   
UProperty<std::vector<MVector<double,2> >, UBADataSimulatorSimple, ptPubOutput | ptPubParameter> ScreenPoints;

///   
UProperty<std::vector<MVector<double,3> >, UBADataSimulatorSimple, ptPubOutput | ptPubParameter>  PlanePoints;

///   
UProperty<std::vector<MVector<double,4> >, UBADataSimulatorSimple, ptPubOutput | ptPubParameter>  SpacePoints;

public: // 
// ---------------------
//   
// ---------------------
UBADataSimulatorSimple(void);
virtual ~UBADataSimulatorSimple(void);
// ---------------------

// ---------------------
//  
// ---------------------
//     
virtual UBADataSimulatorSimple* New(void);
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

#endif

