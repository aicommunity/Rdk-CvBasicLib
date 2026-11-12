#ifndef UCR_CONVOLUTION_NETWORK_H
#define UCR_CONVOLUTION_NETWORK_H

#include "UCRClassifier.h"
#include "UCVNetwork/CNetwork.h"

namespace RDK{
class RDK_LIB_TYPE UCRConvolutionNetwork : public UCRClassifier
{
public: //  
//      
// RDK::UProperty<string, UCRClassifier, ptPubParameter>  ResultsFileName;

protected: // 
//   
CNetwork CVNetwork;

protected: //     

protected: //  

public: // 
// --------------------------
//   
// --------------------------
UCRConvolutionNetwork(void);
virtual ~UCRConvolutionNetwork(void);
// --------------------------

// -----------------------------
//     
// -----------------------------
public:
//   
CNetwork& GetNetwork(void);
//  
//double GetSamples(int i, int j, int k) const;

// --------------------------
//   
// --------------------------
//   
const int& GetNetworkNumLayers(void) const;
bool SetNetworkNumLayers(const int& value);

//      
const vector<int>& GetNetworkConvStep(void) const;
bool SetNetworkConvStep(const vector<int>& value);

//      
const vector<int>& GetNetworkConvHeight(void) const;
bool SetNetworkConvHeight(const vector<int>& value);

//      
const vector<int>& GetNetworkConvWidth(void) const;
bool SetNetworkConvWidth(const vector<int>& value);

//      
const vector<int>& GetNetworkNumFields(void) const;
bool SetNetworkNumFields(const vector<int>& value);

//   
const double& GetNetworkEta(void) const;
//bool SetNetworkEta(const double &value);
//    
const double& GetNetworkDegWeights(void) const;
bool SetNetworkDegWeights(const double& value);

//   
const int& GetInputWidth(void) const;
bool SetInputWidth(const int& value);

const int& GetInputHeight(void) const;
bool SetInputHeight(const int& value);

// --------------------------
//   
// --------------------------
//            
bool LoadInputData(double *input, int size);

//         
vector<double> ConversionOutputData(int size);

//bool LoadImage(const string &file_name);
//double ScaleImage(double a, double b, double m, double n, double data);
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
virtual UCRConvolutionNetwork* New(void);
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

public:
//     
virtual double Train(size_t exp_class);
// --------------------------

};


}


#endif
