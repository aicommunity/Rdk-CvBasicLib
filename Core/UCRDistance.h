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

#ifndef UCRDistanceH
#define UCRDistanceH

#include "UCRClassifier.h"

namespace RDK {

class RDK_LIB_TYPE UCRDistance: public UCRClassifier
{
public: //  
//   
RDK::UProperty<size_t, UCRDistance, ptPubParameter> NumLayerInputs;

//       
// 0 -  
// 1 -  
// 2 -  
RDK::UProperty<int, UCRDistance, ptPubParameter> DispersioUCRoppingFlag;

//    
RDK::UProperty<double, UCRDistance, ptPubParameter> MaxDispersionValue;

//   
RDK::UProperty<vector<size_t>,UCRDistance, ptPubParameter> NumMaxElements;

//     
RDK::UProperty<double,UCRDistance, ptPubParameter> MinElementsDistance;

//      
//      (0,1)
RDK::UProperty<double,UCRDistance, ptPubParameter> MaxRecThreshold;

RDK::UProperty<double,UCRDistance, ptPubParameter> MinRecThreshold;

//  
// 0 -      
// 1 -      
// 2 -     
// 3 -        
// 4 -  3,      
// 5 -         
// 6 -         
// 7 -        
RDK::UProperty<int,UCRDistance, ptPubParameter> RecognitionType;


protected: //  
//public:
//   
vector<vector<vector<double> > > PreSamples;

//  
vector<vector<vector<double> > > Samples;

//   
vector<vector<double> > MiddleSamples;

//  
vector<vector<double> > Dispersion;

//   
vector<vector<int> > MaxMiddleIndex;

//   
vector<double> Inputs;

//     
vector<double> NativeOutput;

public:
//    
//   
vector<vector<double> > Weights;

//    
//   
vector<vector<double> > MaxClassElements;

//     
//   
vector<vector<size_t> > MaxClassElementsIndex;

//    
vector<int> DispersionBanIndexes;


protected: //     
//      
//size_t CurrentTrainingSample;

protected: //  


public:
// --------------------------
//   
// --------------------------
UCRDistance(void);
~UCRDistance(void);
// --------------------------

protected:
// -----------------------------
//    
// -----------------------------
//      
bool SetNumLayerInputs(const size_t &numinputs);

//    
bool SetTrainingRate(const double &tr);

//      
bool SetMaxRecThreshold(const double &value);
// -----------------------------

// -----------------------------
//     
// -----------------------------
public:
//   
double GetMiddleSamples(int i, int j) const;

//  
double GetSamples(int i, int j, int k) const;

//    
double GetPreSamples(int i, int j, int k) const;

//  
double GetDispersion(int i, int j) const;

//  
double GetSDeviation(int i, int j) const;

//     
const vector<double>& GetNativeOutput(void) const;

//  
const vector<double>& GetInputs(void) const;
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
virtual UCRDistance* New(void);
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

//    
void CalcMiddleSamples(void);

//    
void CalcMaxElements(void);

//       
void CalcDispersioUCRopping(void);
// --------------------------

// ------------------------
//   
// ------------------------
public:
//      
virtual bool SetInput(const vector<double> &input);
// ------------------------
};

}

#endif
