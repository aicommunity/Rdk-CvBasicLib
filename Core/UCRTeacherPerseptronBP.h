#ifndef UCRTeacherPerseptronBP_H
#define UCRTeacherPerseptronBP_H

#include "UCRTeacher.h"

namespace RDK {

class RDK_LIB_TYPE UCRTeacherPerseptronBP: public UCRTeacher
{
public: // 
//  
RDK::UProperty<double, UCRTeacherPerseptronBP, ptPubParameter> Moment;

public:
//   
UPropertyInput<UCRPerseptron,UCRTeacherPerseptronBP> Perseptron;

public: //  


public:
// --------------------------
//   
// --------------------------
UCRTeacherPerseptronBP(void);
virtual ~UCRTeacherPerseptronBP(void);
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

//   
bool SetMoment(const double &m);
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
virtual UCRTeacherPerseptronBP* New(void);
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
