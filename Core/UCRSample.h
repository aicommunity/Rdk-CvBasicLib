// ===========================================================
// Version:        1.0.0
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2010.
E-mail:        alexab@ailab.ru
url:        http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UCRSampleH
#define UCRSampleH

#include "../../../Rdk/Deploy/Include/rdk.h"

//---------------------------------------------------------------------------
namespace RDK {

//using namespace RDK;

class RDK_LIB_TYPE UCRSample: public UNet
{
public: //  
//  
// 0 - 
// 1 -  
RDK::UProperty<int, UCRSample, ptPubParameter> Type;

//    
RDK::UProperty<int, UCRSample, ptPubParameter> VectorSize;

//   
RDK::UProperty<int, UCRSample, ptPubParameter> SampleImageWidth;

//   
RDK::UProperty<int, UCRSample, ptPubParameter> SampleImageHeight;

//  
RDK::UProperty<int, UCRSample,ptPubState> SampleSize;

//    
RDK::UProperty<string, UCRSample, ptPubParameter> SampleFileName;

//      
RDK::UProperty<double, UCRSample, ptPubParameter>  MinInputValue, MaxInputValue;

//      
RDK::UProperty<double, UCRSample, ptPubParameter>  MinOutputValue, MaxOutputValue;

//     
RDK::UProperty<bool, UCRSample, ptPubParameter>  ScaleFlag;

//     
RDK::UProperty<bool, UCRSample, ptPubParameter>  ReflictionX;

//  
// 0 -  (     )
// 1 -  (     )
// 2 -     
RDK::UProperty<int, UCRSample, ptPubParameter> Mode;

//   
RDK::UProperty<int, UCRSample,ptPubState> CurrentSample;

//    
RDK::UProperty<int, UCRSample,ptPubState> CurrentSampleIteration;

//    
RDK::UProperty<int, UCRSample,ptPubState> NumClasses;


protected: //  
//  
vector<pair<RDK::UItemData,int> > SampleData;

//  
vector<pair<RDK::UBitmap,int> > BitmapSampleData;

///      
RDK::UItemData CurrentSampleData;

RDK::UBitmap CurrentBitmapSampleData;

public:
// --------------------------
//   
// --------------------------
UCRSample(void);
~UCRSample(void);
// --------------------------

// --------------------------
//    
// --------------------------
//   
bool SetCurrentSample(const int &value);

//   
bool SetSampleSize(const int &value);

//    
bool SetVectorSize(const int &value);

//   
bool SetSampleFileName(const string &value);
// --------------------------

// --------------------------
//   
// --------------------------
//     
bool Add(int class_index);

//     
bool Add(const vector<double> &data, int class_index);

//       
bool Del(size_t index);

//  
void Clear(void);

//       
int GetCurrentClassIndex(void) const;

//    
virtual const vector<pair<RDK::UItemData,int> >& GetSampleData(void) const;
virtual const vector<pair<RDK::UBitmap,int> >& GetBitmapSampleData(void) const;

//      
virtual bool SetSampleData(const RDK::UBitmap &image);
RDK::UBitmap& GetCurrentBitmapSampleData(void);

//       ,
//     file_name
//      xxxx_classindex.bmp
//        
bool LoadBitmapSample(const string &file_path);

//      
//   -   
//     -  ,  -   
// :   
//        
bool LoadTextSample(const string &file_name);
// --------------------------

// --------------------------
//    
// --------------------------
//         
virtual UContainer* New(void);
// --------------------------

// --------------------------
//    
// --------------------------
protected:
//        
virtual bool ADefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool ABuild(void);

//   .
virtual bool AReset(void);

//       .
virtual bool ACalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif
