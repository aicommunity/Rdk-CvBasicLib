#ifndef UCR_TEACHER_CVNETWORK_BP_H
#define UCR_TEACHER_CVNETWORK_BP_H

#include "UCRTeacher.h"
#include "UCRConvolutionNetwork.h"

namespace RDK{

class RDK_LIB_TYPE UCRTeacherCVNetworkBP : public UCRTeacher
{
public: // 
//  
//DK::UProperty<double, UCRTeacherPerseptronBP, ptPubParameter> Moment;

public:
//    
UPropertyInput<UCRConvolutionNetwork,UCRTeacherCVNetworkBP> Network;

//UProperty<MDMatrix<double>,UCRConvolutionNetwork, ptPubOutput | ptState> TrainErrorResult;
//UEPtr<UCRConvolutionNetwork> Network;

public: //  

protected: // 
//        TrainingError
// 1 -  
// 0 -   
int TrainingEndingFlag;

//     
double Err1, Err2;

//    
double SuccessRecognition;

//    ()
int TrainingUsl;

public:
// --------------------------
//   
// --------------------------
UCRTeacherCVNetworkBP(void);
virtual ~UCRTeacherCVNetworkBP(void);
// --------------------------

// -----------------------------
//    
// -----------------------------
public:
// -----------------------------
//bool SetTrainingEndingFlag(const int &value);
virtual const int& GetTrainingEndingFlag(void) const;

//       
virtual const double& GetErr1(void) const;
virtual const double& GetErr2(void) const;

//    
const double& GetSuccessRecognition(void) const;

protected:
// -----------------------------
//    
// -----------------------------
//bool SetMode(const int &value);

//   
//bool SetMoment(const double &m);
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
virtual UCRTeacherCVNetworkBP* New(void);
// --------------------------

// --------------------------
//    
// --------------------------
protected:
//        
virtual bool ACrDefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool ACrBuild(void);

//   .
virtual bool ACrReset(void);

//       .
virtual bool ACrCalculate(void);
// --------------------------

// --------------------------
//   
// --------------------------
public:
//      
virtual void ACrResetTraining(void);

//    
virtual double ACrTrainStep(size_t exp_class);

//       
virtual void ACrSampleIterationCompleteAction(void);
// --------------------------


};



}


#endif
