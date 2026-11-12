#ifndef UCRTeacher_H
#define UCRTeacher_H

//#include "../../UNet.h"
#include "UCRClassifier.h"
#include "UCRSample.h"
#include "UCRPerseptron.h"

namespace RDK {

class RDK_LIB_TYPE UCRTeacher: public UNet
{
public: // 
//    
RDK::UProperty<double, UCRTeacher, ptPubParameter>  TrainEpsilon;

//     
RDK::UProperty<size_t, UCRTeacher, ptPubParameter>  TrainMaxStepsNum;

//  
RDK::UProperty<double, UCRTeacher, ptPubParameter> TrainingRate;

// 0 - 
// 1 - 
//  -      
UProperty<int,UCRTeacher, ptPubParameter> Mode;

public:
//    
UPropertyInput<UCRSample,UCRTeacher> TrainSample;

//    
UPropertyInput<UCRSample,UCRTeacher> TestSample;

//    
UPropertyInput<UCRSample,UCRTeacher> CrossValidationSample;

//   
UPropertyInput<UCRClassifier,UCRTeacher> Classifier;


public: //  
UProperty<int,UCRTeacher,ptPubState> CurrentSampleIteration;

//  
RDK::UProperty<double, UCRTeacher,ptPubState>  TrainingError;

//  
RDK::UProperty<MDMatrix<double>, UCRTeacher>  MatrixTrainingError;


public:
// --------------------------
//   
// --------------------------
UCRTeacher(void);
virtual ~UCRTeacher(void);
// --------------------------

// -----------------------------
//    
// -----------------------------
public:
// -----------------------------

protected:
// -----------------------------
//    
// -----------------------------
virtual bool SetMode(const int &value);

//    
bool SetTrainingRate(const double &tr);

//     
bool SetTrainEpsilon(const double &eps);

//     
bool SetTrainMaxStepsNum(const size_t &lmaxsteps);
// -----------------------------

// ------------------------
//  
// ------------------------
public:
//     'name'
virtual bool AFileLoad(fstream &file);

//     'name'
virtual bool AFileSave(fstream &file);
// ------------------------

// --------------------------
//    
// --------------------------
//         
//virtual UCRTeacher* New(void);
// --------------------------

// --------------------------
//    
// --------------------------
protected:
//        
virtual bool ADefault(void);
virtual bool ACrDefault(void)=0;

//     
//   
//    Reset()   Ready  true
//    
virtual bool ABuild(void);
virtual bool ACrBuild(void)=0;

//   .
virtual bool AReset(void);
virtual bool ACrReset(void)=0;

//       .
virtual bool ACalculate(void);
virtual bool ACrCalculate(void)=0;
// --------------------------

// --------------------------
//   
// --------------------------
public:
//      
virtual void ResetTraining(void);
virtual void ACrResetTraining(void)=0;

//  
virtual void Train(void);

//    
virtual double TrainStep(size_t exp_class);
virtual double ACrTrainStep(size_t exp_class)=0;

//       
virtual void SampleIterationCompleteAction(void);
virtual void ACrSampleIterationCompleteAction(void)=0;
// --------------------------
};

}
#endif
