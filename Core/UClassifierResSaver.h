#ifndef RDK_UCLASSIFIERRESSAVER_H
#define RDK_UCLASSIFIERRESSAVER_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
///     

class RDK_LIB_TYPE UClassifierResSaver: virtual public RDK::UNet
{
protected: // 


/// ,     .
///  : {ProjectPath}/Result/{SaveDirectory}
UProperty<std::string, UClassifierResSaver, ptPubParameter> SaveDirectory;

///   SaveDirectory    (  )
///   -  SaveDirectory     { SaveDirectory_id }
UProperty<bool, UClassifierResSaver, ptPubParameter> OverwriteSaveDirectory;

///  .      ,      ""
///      
UProperty<std::map<int, std::string>, UClassifierResSaver, ptPubParameter> ObjectsName;

protected: //   

///  
/// ,     InputImages
UProperty<UBitmap, UClassifierResSaver, ptPubInput> InputImage;

///   
///  ,   images   
UProperty<UBitmap, UClassifierResSaver, ptPubInput> ImageName;




///   
UProperty<std::vector<UBitmap>, UClassifierResSaver, ptPubInput> InputImages;

///     
UProperty<MDMatrix<int>,UClassifierResSaver, ptPubInput> InputClasses;

///  .     ,       
///   -  
UProperty<MDMatrix<double>, UClassifierResSaver, ptPubInput> InputConfidences;

protected: //  


UProperty<bool, UClassifierResSaver, ptPubState> CalculateFlag;

std::string OldSaveDirectory;

protected: //  

UBitmap ProcessedBmp;

public: // 
// --------------------------
//   
// --------------------------
UClassifierResSaver(void);
virtual ~UClassifierResSaver(void);
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
virtual UClassifierResSaver* New(void);
// --------------------------

// --------------------------
//    
// --------------------------

virtual bool ACalculate(void);

bool SaveImage(UBitmap& img, int class_id, MDMatrix<double>& confidences);
};

}
#endif



