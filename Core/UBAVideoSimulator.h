/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAVIDEO_SIMULATOR_H
#define UBAVIDEO_SIMULATOR_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

struct RDK_LIB_TYPE UBVSObject
{
int ObjectX,ObjectY;
int ObjectWidth,ObjectHeight;
int XShift,YShift;
UColorT Color;
UColorT Color2;
UColorT Color3;
UColorT Color4;
bool Visible;
int MovingDirection;

// 0 -  
// 1 -   
int Mode;

public:
// --------------------------
//   
// --------------------------
UBVSObject(void);
// --------------------------
bool operator == (const UBVSObject &copy) const;

bool operator != (const UBVSObject &copy) const;
};

// struct UBVSObject
RDK_LIB_TYPE USerStorageXML& operator << (USerStorageXML& storage, const UBVSObject &data);
RDK_LIB_TYPE USerStorageXML& operator >> (USerStorageXML& storage, UBVSObject &data); 
RDK_LIB_TYPE USerStorageBinary& operator << (USerStorageBinary& storage, const UBVSObject &data);
RDK_LIB_TYPE USerStorageBinary& operator >> (USerStorageBinary& storage, UBVSObject &data);  

///    
class RDK_LIB_TYPE UBAVideoSimulator: public UNet
{
public: // 
///    
/// 0 -   
/// 1 -    BgMode
UProperty<int,UBAVideoSimulator, ptPubParameter> BgMode;

///  
UProperty<UColorT ,UBAVideoSimulator, ptPubParameter> BgColor;

///      
UProperty<bool,UBAVideoSimulator, ptPubParameter> HideAllFlag;

///  
UProperty<int,UBAVideoSimulator, ptPubParameter> NumObjects;

///   
UProperty<UBRect,UBAVideoSimulator, ptPubParameter> WorkArea;

///   
UProperty<bool, UBAVideoSimulator, ptPubParameter> ShowGrid;

///    ( )
UProperty<int, UBAVideoSimulator, ptPubParameter> PixelGridStep;

///  
UProperty<UColorT, UBAVideoSimulator, ptPubParameter> PixelGridColor;

///   
UProperty<int, UBAVideoSimulator, ptPubParameter> PixelGridWidth;

protected: //    
UProperty<UBitmap, UBAVideoSimulator, ptPubInput | ptState> InputData;

///  
UProperty<UBitmap, UBAVideoSimulator, ptPubParameter> Input;

///  
UProperty<UBitmap, UBAVideoSimulator, ptPubParameter> Output;

///  
UProperty<std::vector<UBVSObject>, UBAVideoSimulator, ptPubParameter> Objects;

protected: // 
///   
int CurrentObjectIndex;

protected: //  
UAGraphics *Graphics;

UBitmap Canvas;


public: // 
// ---------------------
//   
// ---------------------
UBAVideoSimulator(void);
virtual ~UBAVideoSimulator(void);
// ---------------------

// ---------------------
//   
// ---------------------
///    
/// ( )
const int& GetBgMode(void) const;
bool SetBgMode(const int &value);

///      
const bool& GetHideAllFlag(void) const;
bool SetHideAllFlag(const bool &value);

///   
const UBRect& GetWorkArea(void) const;
bool SetWorkArea(const UBRect &value);
// ---------------------

// ---------------------
//   
// ---------------------
///   
void ClearObjects(void);

///  
const int& GetNumObjects(void) const;
bool SetNumObjects(const int &value);

///  
const UBVSObject& GetObjectData(int index) const;
bool SetObjectData(int index, const UBVSObject &data);
const UBVSObject& GetCurrentObjectData(void) const;
bool SetCurrentObjectData(const UBVSObject &data);

///   
int GetCurrentObjectIndex(void) const;
bool SetCurrentObjectIndex(int value);
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
virtual bool AFSDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFSBuild(void);

///      
virtual bool AFSReset(void);

///    
virtual bool AFSCalculate(void);
// --------------------------
};

///     
class RDK_LIB_TYPE UBAVideoSimulatorSimple: public UBAVideoSimulator
{
protected: // 


public: // 
// ---------------------
//   
// ---------------------
UBAVideoSimulatorSimple(void);
virtual ~UBAVideoSimulatorSimple(void);
// ---------------------

// ---------------------
//  
// ---------------------
///     
virtual UBAVideoSimulatorSimple* New(void);
// ---------------------

// --------------------------
//      
// --------------------------
protected:
void CreateFillBackground(UBitmap &canvas);

///        
virtual bool AFSDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFSBuild(void);

///      
virtual bool AFSReset(void);

///    
virtual bool AFSCalculate(void);
// --------------------------
};

///              
class RDK_LIB_TYPE UBAVideoSimulatorSimpleBin: public UBAVideoSimulator
{
protected: // 
    ///   
    UProperty<UBitmap, UBAVideoSimulatorSimpleBin, ptPubParameter> BinarOutput;
    ///  ,  
    UProperty<int, UBAVideoSimulatorSimpleBin, ptPubParameter> countFirstCleanBgFrame;
    /// ,  
    int nCounterBG;
    UBitmap CanvasBin;


public: // 
// ---------------------
//   
// ---------------------
UBAVideoSimulatorSimpleBin(void);
virtual ~UBAVideoSimulatorSimpleBin(void);
// ---------------------

// ---------------------
//  
// ---------------------
///     
virtual UBAVideoSimulatorSimpleBin* New(void);
// ---------------------

// --------------------------
//      
// --------------------------
protected:
void CreateFillBackground(UBitmap &canvas);


/// 
void DrawSimple(UBitmap &canvas, int isBin);

///        
virtual bool AFSDefault(void);

///     
///   
///    Reset()   Ready  true
///    
virtual bool AFSBuild(void);

///      
virtual bool AFSReset(void);

///    
virtual bool AFSCalculate(void);
// --------------------------
};
}

#endif

