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

#ifndef UCRPERSEPTRON_H
#define UCRPERSEPTRON_H

#include "UCRClassifier.h"

namespace RDK {

class RDK_LIB_TYPE UCRPerseptron: public UCRClassifier
{
public: //  
//   
RDK::UProperty<int,UCRPerseptron, ptPubParameter> NumLayers;

//   
RDK::UProperty<vector<int>, UCRPerseptron> NumLayerInputs;

//   
RDK::UProperty<bool,UCRPerseptron, ptPubParameter> AutoSetLayerInputs;

//   
// 0 - 
// 1 -   
RDK::UProperty<int,UCRPerseptron, ptPubParameter> Mode;

///  
RDK::UProperty<double,UCRPerseptron, ptPubParameter> Alpha;

///    ,    
RDK::UProperty<std::string, UCRPerseptron, ptPubParameter> NameBin;

public: //  
//    
vector<vector<vector<double> > > Weights;

//   
RDK::UProperty<vector<double>,UCRPerseptron,ptPubState> Inputs;

//    
RDK::UProperty<vector<vector<double> >,UCRPerseptron,ptPubState> Outputs;


public: //  
vector<vector<vector<double> > > dWeights;

public:
// --------------------------
//   
// --------------------------
UCRPerseptron(void);
~UCRPerseptron(void);
// --------------------------

// -----------------------------
//    
// -----------------------------
public:
double GetWeight(int layer, int col, int row);

double GetInputs(int row);
double GetOutputs(int layer, int row);
// -----------------------------

protected:
// -----------------------------
//    
// -----------------------------
//    
bool SetNumLayers(const int &num);

//      
bool SetNumLayerInputs(const vector<int> &numinputs);

//   
bool SetAutoSetLayerInputs(const bool &value);
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
virtual UCRPerseptron* New(void);
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
public:
//      
virtual void AResetTraining(void);

//        
virtual void LayerResetTraining(size_t index);
// --------------------------

// ------------------------
//   
// ------------------------
public:
//      
virtual bool SetInput(const vector<double> &input);

public:
//    
void CalcLayer(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights);

void ReverseCalcLayer(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights, vector<vector<double> > &prev_weights);

void ReverseCalcLayer0(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights, vector<double> &fi);

//    
void CalcNetwork(vector<double> &inputs);

//    
void CalcDeepNetwork(vector<double> &inputs);

double Sigmoid(double x);
// ------------------------
};

}
#endif


