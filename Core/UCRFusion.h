// ===========================================================
// Version:        3.0.4
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2002.
E-mail:        alexab@ailab.ru
url:            http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UCRFusionH
#define UCRFusionH

#include "UCRClassifier.h"

namespace RDK {

//     
struct RDK_LIB_TYPE UCRFPreResult
{
 //   
 int Ix1, Ix2;

 //  
 double Res1, Res2;

 UCRFPreResult(void)
 {
  Ix1=Ix2=0;
  Res1=Res2=0;
 };

};


class RDK_LIB_TYPE UCRFusion: public UCRClassifier
{
public: //  
//   
// 0 -    
// 1 -   
// 2 -   
// 3 -    
// 4 -   
// 5 -     
// 6 -   -
RDK::UProperty<int, UCRFusion, ptPubParameter> FusionMode;

//     
RDK::UProperty<int, UCRFusion, ptPubParameter> NumAttempts;

//    
// 1 -   
// 2 -       
// 3 -    
RDK::UProperty<int, UCRFusion, ptPubParameter> AccumulateMode;

//   
RDK::UProperty<vector<vector<double> >, UCRFusion, ptPubState> PreResultsWeigths;

protected: //  
//   
int CurrentAttempt;


protected: //     

protected: //  
vector<RDK::UItemData> AccumOutput;

public:
// --------------------------
//   
// --------------------------
UCRFusion(void);
~UCRFusion(void);
// --------------------------

protected:
// -----------------------------
//    
// -----------------------------
bool SetFusionMode(const int &value);
// -----------------------------

// -----------------------------
//     
// -----------------------------
public:
//   
int GetCurrentAttempt(void) const;
// -----------------------------

// ------------------------
//  
// ------------------------
public:
//        'name'
virtual bool AFileLoad(fstream &file);

//        'name'
virtual bool AFileSave(fstream &file);
// ------------------------

// --------------------------
//    
// --------------------------
//         
virtual UCRFusion* New(void);
// --------------------------

// --------------------------
//    
// --------------------------
protected:
//        
virtual bool ACRDefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool ACRBuild(void);

//   .
virtual bool ACRReset(void);

//       .
virtual bool ACRCalculate(void);
// --------------------------

// --------------------------
//    
// --------------------------
protected:
//      
virtual void AResetTraining(void);

//     
virtual double ATrain(size_t exp_class);
// --------------------------

// ------------------------
//   
// ------------------------
protected:
//       
bool AverageQualityCalculate(void);

//      
bool AverageInputCalculate(void);

//      
bool SumInputCalculate(void);

//        
bool InputRecognitionCounterCalculate(void);

//     -
bool SumInputRecognitionCounterCalculate(void);

//     
bool PairCalculate(void);

//      
bool RecognitionCounterCalculate(void);

public:
//      
virtual bool SetInput(const vector<double> &input);
// ------------------------
};

}
//---------------------------------------------------------------------------
#endif
