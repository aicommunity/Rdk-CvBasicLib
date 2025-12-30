/* ***********************************************************
@Copyright Aleksandr Bakhshiev, 2011.
E-mail:        palexab@gmail.com
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAShowObjectsH
#define UBAShowObjectsH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

///    
class RDK_LIB_TYPE UBAShowObjects: public UNet
{
protected: // 
///  
UProperty<RDK::UColorT,UBAShowObjects, ptPubParameter> PenColor;

///  
UProperty<int,UBAShowObjects, ptPubParameter> PenWidth;

///   
UProperty<bool,UBAShowObjects, ptPubParameter> EnableShowFlag;

public: //    
///  
UProperty<UBitmap, UBAShowObjects, ptPubParameter> Input;

///  
UProperty<UBitmap, UBAShowObjects, ptPubParameter> Output;

///    
///          
UProperty<std::vector<UColorT>, UBAShowObjects, ptPubInput | ptParameter> ObjectsColor;

///   
UProperty<std::vector<std::string>, UBAShowObjects, ptPubInput | ptParameter> ObjectsName;

///   
UProperty<MDMatrix<int>, UBAShowObjects, ptPubInput | ptParameter> ObjectsId;


protected: // 
UBitmap Canvas;
UGraphics Graphics;

public: // 
// ---------------------
//   
// ---------------------
UBAShowObjects(void);
virtual ~UBAShowObjects(void);
// ---------------------

// --------------------------
//   
// --------------------------
bool SetActivity(const bool &activity);
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
virtual bool AFSDefault(void)=0;

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFSBuild(void)=0;

///      
virtual bool AFSReset(void)=0;

///    
virtual bool AFSCalculate(void)=0;
// --------------------------
};

//   -
class RDK_LIB_TYPE UBAShowObjectsSimple: public RDK::UBAShowObjects
{
protected: //  
///    
UProperty<std::vector<UBPoint>, UBAShowObjectsSimple, ptPubParameter> Zones;

/// Matrix points
UProperty<MDMatrix<double>, UBAShowObjectsSimple, ptPubParameter> MatrixPoints;

public: // 
// ---------------------
//   
// ---------------------
UBAShowObjectsSimple(void);
virtual ~UBAShowObjectsSimple(void);
// ---------------------

// ---------------------
//  
// ---------------------
///     
virtual UBAShowObjectsSimple* New(void);
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
