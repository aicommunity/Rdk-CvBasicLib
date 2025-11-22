// ===========================================================
// Version:        3.0.3
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

#ifndef UCRCLASSIFIER_H
#define UCRCLASSIFIER_H


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <ctime>

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

//using namespace MySDK;

//    
typedef double ExpectancyT;

class RDK_LIB_TYPE UCRClassifier: public UNet
{
public: //  
//  
RDK::UProperty<int, UCRClassifier, ptPubParameter>  NumClasses;

//     
RDK::UProperty<double, UCRClassifier, ptPubParameter>  MinInputValue, MaxInputValue;

//     
RDK::UProperty<double, UCRClassifier, ptPubParameter>  MinOutputValue, MaxOutputValue;

//    
RDK::UProperty<double, UCRClassifier, ptPubParameter>  DesiredMinOutputValue, DesiredMaxOutputValue;

//     
RDK::UProperty<vector<double>, UCRClassifier>  MinQualityRate, MaxQualityRate;

//   /  
RDK::UProperty<string, UCRClassifier, ptPubParameter>  TrainFileName;

//      
RDK::UProperty<string, UCRClassifier, ptPubParameter>  ResultsFileName;

//      
//   
RDK::UProperty<bool, UCRClassifier, ptPubParameter>  AutoQualityRate;

//        
// MaxOutputValue     
RDK::UProperty<bool, UCRClassifier, ptPubParameter>  AutoAlignmentOutput;

RDK::UProperty<MDMatrix<double>,UCRClassifier, ptPubOutput | ptState> Result;


public: //   
//   < ,   >
RDK::UProperty<pair<double,int, ptPubParameter>, UCRClassifier,ptPubState>  QualityRate;

//   
RDK::UProperty<vector<double>, UCRClassifier,ptPubState>  ScaledResult;

//    
RDK::UProperty<bool, UCRClassifier,ptPubState>  IsSuccessed;

protected: //  
RDK::UProperty<bool, UCRClassifier,ptPubState>  ModifiedFlag;

protected: //  

public: // 
// --------------------------
//   
// --------------------------
UCRClassifier(void);
virtual ~UCRClassifier(void);
// --------------------------


// ---------------------
//  
// ---------------------
///     
virtual UCRClassifier* New(void);
// ---------------------

protected:
// -----------------------------
//    
// -----------------------------
//   
bool SetNumClasses(const int &value);

//      
bool SetMinInputValue(const double &value);
bool SetMaxInputValue(const double &value);

//      
bool SetMinOutputValue(const double &value);
bool SetMaxOutputValue(const double &value);

//      
bool SetMinQualityRate(const vector<double>& value);
bool SetMaxQualityRate(const vector<double>& value);

//   /  
bool SetTrainFileName(const string &name);

//      
bool SetResultsFileName(const string &name);
// -----------------------------

// --------------------------
//    
// --------------------------
protected:
//        
virtual bool ADefault(void);
virtual bool ACRDefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool ABuild(void);
virtual bool ACRBuild(void);

//   .
virtual bool AReset(void);
virtual bool ACRReset(void);

//       .
virtual bool ACalculate(void);
virtual bool ACRCalculate(void);
// --------------------------

// --------------------------
//   
// --------------------------
public:
//      
virtual void ResetTraining(void);
// --------------------------

// ------------------------
//  
// ------------------------
public:
//     'name'
virtual bool FileLoad(const string &name);
virtual bool AFileLoad(fstream &file);

//     'name'
virtual bool FileSave(const string &name);
virtual bool AFileSave(fstream &file);

//      
//virtual bool SetInput(const Real &input)=0;
// ------------------------

// --------------------------
//    
// --------------------------
protected:
//      
virtual void AResetTraining(void);
// --------------------------
};

}
#endif


