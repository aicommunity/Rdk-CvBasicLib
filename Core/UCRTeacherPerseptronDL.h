#ifndef UCRTeacherPerseptronDL_H
#define UCRTeacherPerseptronDL_H

#include "UCRTeacher.h"

namespace RDK {

class RDK_LIB_TYPE UCRTeacherPerseptronDL: public UCRTeacher
{
public: // 
// Mode
// 0 - 
// 1 -   
// 2 -   

public:
//     
UPropertyInput<UCRPerseptron,UCRTeacherPerseptronDL> DeepPerseptron;

public: //  
UProperty<double,UCRTeacherPerseptronDL,ptPubState> dW;
UProperty<double,UCRTeacherPerseptronDL,ptPubState> dB;
UProperty<double,UCRTeacherPerseptronDL,ptPubState> dC;

double Temp_dW;
double Temp_dB;
double Temp_dC;

int WCount, CCount, BCount;

vector<double> x1;
vector<double> Q;
vector<double> h1;
vector<double> P;
vector<double> x2;
vector<double> Q2;

//    
vector<double> Fi;


public:
// --------------------------
//   
// --------------------------
UCRTeacherPerseptronDL(void);
virtual ~UCRTeacherPerseptronDL(void);
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
bool SetMode(const int &value);
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
virtual UCRTeacherPerseptronDL* New(void);
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

//     
//       
//    
virtual int Train1CreateLayer(void);

//     1
virtual double CalcTrain1Estimation(void);
// --------------------------
};

}
#endif
