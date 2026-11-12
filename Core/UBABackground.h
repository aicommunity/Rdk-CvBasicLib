/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBABackgroundH
#define UBABackgroundH
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

///     
class RDK_LIB_TYPE UBABackground: public UNet
{
public: //    
///  
UProperty<UBitmap, UBABackground, ptPubParameter> Input;

///  
UProperty<UBitmap, UBABackground, ptPubParameter> Background;

///, ,     
UProperty<bool, UBABackground, ptPubParameter> IsBGReady;




public: // 
// ---------------------
//   
// ---------------------
UBABackground(void);
virtual ~UBABackground(void);
// ---------------------

// --------------------------
//     
// --------------------------
protected:
///        
virtual bool ADefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool ABuild(void);

///      
virtual bool AReset(void);

///    
virtual bool ACalculate(void);
// --------------------------

// --------------------------
//       
// --------------------------
protected:
///        
virtual bool AFBgDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFBgBuild(void);

///      
virtual bool AFBgReset(void);

///    
virtual bool AFBgCalculate(void);
// --------------------------
};

///    
class RDK_LIB_TYPE UBABackgroundAvg: public UBABackground
{
protected: // 
///    
UProperty<int, UBABackgroundAvg, ptPubParameter> HistorySize;

protected: //  
///  
UBitmapVector History;

///    
int CurrentHistoryIndex;

///    
int CurrentHistorySize;

public: // 
// ---------------------
//   
// ---------------------
UBABackgroundAvg(void);
virtual ~UBABackgroundAvg(void);
// ---------------------

// ---------------------
//  
// ---------------------
//     
virtual UBABackgroundAvg* New(void);

bool BCalculate(UBitmap &input, UBitmap &background);
// ---------------------

// --------------------------
//       
// --------------------------
protected:
///        
virtual bool AFBgDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFBgBuild(void);

///      
virtual bool AFBgReset(void);

///    
virtual bool AFBgCalculate(void);
// --------------------------
};




///      
/// C   tempoUpdate
class RDK_LIB_TYPE UBABackgroundExponnential: public UBABackground
{
    /*protected: // 
    ///    
    int HistorySize;*/

    ///    
    protected:
    int CurrentHistoryIndex;

    ///    
    int CurrentHistorySize;

    ///  
    UProperty<double, UBABackgroundExponnential, ptPubParameter> tempoUpdate;

    public: // 
    // ---------------------
    //   
    // ---------------------
    UBABackgroundExponnential(void);
    virtual ~UBABackgroundExponnential(void);
    // ---------------------

    // ---------------------
    //  
    // ---------------------
    //     
    virtual UBABackgroundExponnential* New(void);

    bool BCalculate(UBitmap &input, UBitmap &background);
    // ---------------------

    // --------------------------
    //       
    // --------------------------
    protected:
    ///        
    virtual bool AFBgDefault(void);

    ///     
    ///   
    ///    Reset()   Ready  true
    ///    
    virtual bool AFBgBuild(void);

    ///      
    virtual bool AFBgReset(void);

    ///    
    virtual bool AFBgCalculate(void);
    // --------------------------
};

///      
/// C   tempoUpdate
///       double 
/// . 1.      
/// 2.  double    
class RDK_LIB_TYPE UBADeltaBackgroundExponnential: public UBABackground
{

    ///    
    protected:
    int CurrentHistoryIndex;

    ///    
    int CurrentHistorySize;

    ///  
    UProperty<double, UBADeltaBackgroundExponnential, ptPubParameter> tempoUpdate;

    public: // 
    // ---------------------
    //   
    // ---------------------
    UBADeltaBackgroundExponnential(void);
    virtual ~UBADeltaBackgroundExponnential(void);
    // ---------------------

    // ---------------------
    //  
    // ---------------------
    //     
    virtual UBADeltaBackgroundExponnential* New(void);

    bool BCalculate(UBitmap &input, UBitmap &background);
    // ---------------------

    // --------------------------
    //       
    // --------------------------
    protected:
    ///        
    virtual bool AFBgDefault(void);

    ///     
    ///   
    ///    Reset()   Ready  true
    ///    
    virtual bool AFBgBuild(void);

    ///      
    virtual bool AFBgReset(void);

    ///    
    virtual bool AFBgCalculate(void);
    // --------------------------
};





///   
///      


class RDK_LIB_TYPE UBABackgroundSimpleAdaptive: public UBABackground
{

    ///    
    protected:
    int CurrentHistoryIndex;

    ///    
    int CurrentHistorySize;

    ///   
    UProperty<double, UBABackgroundSimpleAdaptive, ptPubParameter> tempoUpdate;
    ///   
    UProperty<double, UBABackgroundSimpleAdaptive, ptPubParameter> tempoUpdateFG;
    ///  
    UProperty<double, UBABackgroundSimpleAdaptive, ptPubParameter> tempoUpdateBG;
    ///  
    UProperty<UBitmap, UBABackgroundSimpleAdaptive, ptPubParameter> lastBinarization;
    /// 
    UProperty<unsigned int, UBABackgroundSimpleAdaptive, ptPubParameter> delay;
    // 
    //UProperty<double, UBABackgroundSimpleAdaptive,ptPubState> UpdateFGFlag;
    ///  
    UProperty<int, UBABackgroundSimpleAdaptive, ptPubParameter> modeTypes;
    /// 
    UProperty<UBitmap, UBABackgroundSimpleAdaptive, ptPubParameter> lastInput;
    ///       
    UProperty<double, UBABackgroundSimpleAdaptive, ptPubParameter> deltaFrames;
    ///    
    UProperty<UBitmap, UBABackgroundSimpleAdaptive, ptPubParameter> updateFGFlag;
    ///,     
    UProperty<unsigned int, UBABackgroundSimpleAdaptive, ptPubParameter> zeroingUpdateFlag;
    ///   
    UProperty<UBitmap, UBABackgroundSimpleAdaptive, ptPubParameter> output2;
    ///  ,  
    UProperty<int, UBABackgroundSimpleAdaptive, ptPubParameter> countFirstCleanBgFrame;
    /// ,  
    int nCounterBG;


    public: // 
    // ---------------------
    //   
    // ---------------------
    UBABackgroundSimpleAdaptive(void);
    virtual ~UBABackgroundSimpleAdaptive(void);
    // ---------------------

    // ---------------------
    //  
    // ---------------------
    //     
    virtual UBABackgroundSimpleAdaptive* New(void);

    //bool BCalculate1(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    bool BCalculateSimplAdaptive(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    bool BCalculateExp(UBitmap &input, UBitmap &background);
    bool BCalculateStabilityIndicator(UBitmap &input, UBitmap &background, UBitmap &lastBinarization, UBitmap &lastInput, UBitmap &updateFGFlag);
    //    countFirstCleanBgFrame 
    bool BCalculateFirstBackground(UBitmap &input, UBitmap &background);

    // ---------------------
    // --------------------------
    //       
    // --------------------------
    protected:
    ///        
    virtual bool AFBgDefault(void);

    ///     
    ///   
    ///    Reset()   Ready  true
    ///    
    virtual bool AFBgBuild(void);

    ///      
    virtual bool AFBgReset(void);

    ///    
    virtual bool AFBgCalculate(void);
    // --------------------------
};


//------------------------------------------------------------------------
//           
//------------------------------------------------------------------------




class RDK_LIB_TYPE UBABackgroundDependDiff: public UBABackground
{

    protected:

    ///   
    //UProperty<double, UBABackgroundDependDiff, ptPubParameter> StateTempoDif;
    ///  
    UProperty<UBitmap, UBABackgroundDependDiff, ptPubParameter> deltaImg;
    ///  ,  
    UProperty<int, UBABackgroundDependDiff, ptPubParameter> countFirstCleanBgFrame;
    /// ,  
    int nCounterBG;




    public: // 
    // ---------------------
    //   
    // ---------------------
    UBABackgroundDependDiff(void);
    virtual ~UBABackgroundDependDiff(void);
    // ---------------------

    // ---------------------
    //  
    // ---------------------
    //     
    virtual UBABackgroundDependDiff* New(void);

    //bool BCalculate1(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    double BCalculate1(UBitmap &input, UBitmap &background, UBitmap &delta);
    //    countFirstCleanBgFrame 
    bool BCalculateFirstBackground(UBitmap &input, UBitmap &background);


    // ---------------------
    // --------------------------
    //       
    // --------------------------
    protected:
    ///        
    virtual bool AFBgDefault(void);

    ///     
    ///   
    ///    Reset()   Ready  true
    ///    
    virtual bool AFBgBuild(void);

    ///      
    virtual bool AFBgReset(void);

    ///    
    virtual bool AFBgCalculate(void);
    // --------------------------
};





}
//---------------------------------------------------------------------------
#endif

