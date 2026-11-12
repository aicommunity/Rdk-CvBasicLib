#ifndef RDK_UDETRESSAVERPVOC_H
#define RDK_UDETRESSAVERPVOC_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
///     

class RDK_LIB_TYPE UDetResSaverPVOC: virtual public RDK::UNet
{
protected: // 

/// ,     .
///  : {ProjectPath}/Result/{SaveDirectory}
///  {SaveDirectory}     images  annotations
UProperty<std::string, UDetResSaverPVOC, ptPubParameter> SaveDirectory;

///   SaveDirectory    (  )
///   -  SaveDirectory     { SaveDirectory_id }
UProperty<bool, UDetResSaverPVOC, ptPubParameter> OverwriteSaveDirectory;

///  .      ,      ""
///      
UProperty<std::map<int, std::string>, UDetResSaverPVOC, ptPubParameter> ObjectsName;

protected: //   

///  .     
///  :
///    
///  4+1+1=Left; Top; Right; Bottom; ClassReliability; ClassNumber
UProperty<MDMatrix<double>, UDetResSaverPVOC, ptPubInput > InputObjects;

///  
UProperty<UBitmap, UDetResSaverPVOC, ptPubInput> InputImage;

///   
///  ,   images   
///        xml   annotations
UProperty<std::string, UDetResSaverPVOC, ptPubInput> ImageName;

protected: //  

UProperty<bool, UDetResSaverPVOC, ptPubState> CalculateFlag;

std::string OldSaveDirectory;

protected: //  

UBitmap ProcessedBmp;

public: // 
// --------------------------
//   
// --------------------------
UDetResSaverPVOC(void);
virtual ~UDetResSaverPVOC(void);
// --------------------------

// ---------------------
//   
// ---------------------
// ---------------------


// ---------------------
//    
// ---------------------
// ---------------------

// --------------------------
//    
// --------------------------
//         
virtual UDetResSaverPVOC* New(void);
// --------------------------

// --------------------------
//    
// --------------------------
virtual bool ACalculate(void);

bool SaveImage();
};

}
#endif



