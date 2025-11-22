#ifndef RDK_UDETECTORBASE_H
#define RDK_UDETECTORBASE_H
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {
///  .  ACalculate   .
///     Detect.   bool     
///     ACalculate.       ABeforeCalculate()  AAfterCalculate()
class RDK_LIB_TYPE UDetectorBase: virtual public RDK::UNet
{
protected: // 

/// 
UProperty<double,UDetectorBase, ptPubParameter> ConfidenceThreshold;

///    -
UProperty<double,UDetectorBase, ptPubParameter> NMSthreshold;

///        
//UProperty<bool,UDetectorBase, ptPubParameter | ptOutput> UseRelativeCoords;

///     
UProperty<bool,UDetectorBase, ptPubParameter> UseDebugImage;

protected: //   

///  
UProperty<UBitmap, UDetectorBase, ptPubInput | ptPubOutput> InputImage;

///   
UProperty<UBitmap, UDetectorBase, ptPubParameter> DebugImage;

///  .     
///  :
///    
///  4+1+1=Left; Top; Right; Bottom; ClassReliability; ClassNumber
UProperty<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputObjects;

///       
UProperty<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputRects;

///    
UProperty<MDMatrix<int>, UDetectorBase, ptOutput | ptPubState> OutputClasses;

///    
UProperty<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputReliability;


protected: //  
UGraphics Graph;
UBitmap ProcessedBmp;

public: // 
// --------------------------
//   
// --------------------------
UDetectorBase(void);
virtual ~UDetectorBase(void);
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

// --------------------------

// --------------------------
//    
// --------------------------
virtual bool ACalculate(void);

virtual bool Detect(UBitmap &bmp, MDMatrix<double> &output_rects, MDMatrix<int> &output_classes, MDMatrix<double> &reliabilities)
{ return true; };

protected:
// --------------------------


};



}

#endif



