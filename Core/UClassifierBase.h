#ifndef RDK_UCLASSIFIERBASE_H
#define RDK_UCLASSIFIERBASE_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
///  .  ACalculate   .
///     classifyBitmap.   bool     
///     ACalculate.       ABeforeCalculate()  AAfterCalculate()

class RDK_LIB_TYPE UClassifierBase: virtual public RDK::UNet
{
protected: // 

/// :      ,     0,     0.
UProperty<double,UClassifierBase, ptPubParameter> ConfidenceThreshold;

///    (    )
UProperty<int,UClassifierBase, ptPubParameter> NumClasses;

protected: //   

///  
/// ,     InputImages
UProperty<UBitmap,UClassifierBase, ptPubInput | ptPubOutput> InputImage;

///   
UProperty<std::vector<UBitmap>, UClassifierBase, ptPubInput | ptPubOutput> InputImages;

///     
UProperty<MDMatrix<int>,UClassifierBase, ptPubOutput> OutputClasses;

///  .     ,       
///   -  
UProperty<MDMatrix<double>, UClassifierBase, ptPubOutput> OutputConfidences;


protected: //  
/// ,   , 
UProperty<double,UClassifierBase, ptPubState> ClassificationTime;


protected: //  
UBitmap ProcessedBmp;


public: // 
// --------------------------
//   
// --------------------------
UClassifierBase(void);
virtual ~UClassifierBase(void);
// --------------------------

// ---------------------
//   
// ---------------------
// ---------------------
bool SetNumClasses(const int &value);

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

//  .     
virtual bool ClassifyBitmap(UBitmap &bmp, MDVector<double> &output_confidences, double conf_thresh, int &class_id, bool &is_classified)
{ return true; };

protected:
// --------------------------


};





}
#endif



