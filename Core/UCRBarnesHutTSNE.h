#ifndef RDK_UCRBarnesHutTSNE_H
#define RDK_UCRBarnesHutTSNE_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#include <thread>


namespace RDK {
///     

class RDK_LIB_TYPE UCRBarnesHutTSNE: virtual public RDK::UNet
{
protected: // 

/// ,      ,   , 
///  - 
///   ,      
UProperty<bool, UCRBarnesHutTSNE, ptPubParameter> RetrainFlag;

///   ( 0  TrainingData.GetCols())
UProperty<int, UCRBarnesHutTSNE, ptPubParameter> NumOutCoords;

///     
///     /3  
UProperty<double, UCRBarnesHutTSNE, ptPubParameter> Perplexity;

///     
UProperty<double, UCRBarnesHutTSNE, ptPubParameter> Theta;

///       
UProperty<int, UCRBarnesHutTSNE, ptPubParameter> MaxIterations;

///        
///   -1   
UProperty<int, UCRBarnesHutTSNE, ptPubParameter> RandomSeed;


///        
///   -1   
UProperty<int, UCRBarnesHutTSNE, ptPubState> CalcActive;
protected: //   

///    
UProperty<MDMatrix<double>,UCRBarnesHutTSNE, ptPubInput> InputComponents;

///   ()   t-SNE
UProperty<MDMatrix<double>,UCRBarnesHutTSNE, ptPubOutput> OutputComponents;


protected: //  

///  double -   PCA
//UProperty<MDMatrix<double>, UCRBarnesHutTSNE, ptPubState | ptOutput> ...;

///    ()     (1  )   
//UProperty<MDMatrix<double>, UCRBarnesHutTSNE, ptPubState> ...;

protected: //  

bool TSNECalcInProcess;
float CalcProgress;

int N, D, no_dims, max_iter, rand_seed;
double perplexity, theta, *data;

int* landmarks;
double* Y;
double* costs;

std::thread *m_thread;

public: // 
// --------------------------
//   
// --------------------------
UCRBarnesHutTSNE(void);
virtual ~UCRBarnesHutTSNE(void);
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
virtual UCRBarnesHutTSNE* New(void);
// --------------------------

// --------------------------
//    
// --------------------------

virtual bool ACalculate(void);

virtual bool AReset(void);

bool RunTSNECalculation();
void TSNECalculationThread();
void UpdateCalculationState();

};

}
#endif



