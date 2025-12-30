#ifndef UBAGuiSelectionH
#define UBAGuiSelectionH

#include "../../../Rdk/Deploy/Include/rdk.h"


struct RDK_LIB_TYPE StateTMouse
{
 int Previous, Current;
};

namespace RDK {


//  
class RDK_LIB_TYPE UMouse
{
public: // 
int X_mouse, Y_mouse;

//   
int NumClickes;

StateTMouse LeftClickMouse, RightClickMouse;

public:
UMouse(void);
virtual ~UMouse(void);

// ---------------------
//   
// ---------------------
bool SetDecartMouse(int x, int y);
int GetX_Mouse(void);
int GetY_Mouse(void);
// ---------------------

// ---------------------
//   (on/off)
// ---------------------
//    0,  1
//1 -  
//0 -   
bool SetModeLCMouse(int click);
bool SetModeRCMouse(int click);

StateTMouse GetModeLCMouse(void);
StateTMouse GetModeRCMouse(void);
// ---------------------
};

///     .
class RDK_LIB_TYPE UBAGuiSelection: public UNet
{
protected: //    
///  
UProperty<UBitmap, UBAGuiSelection, ptPubParameter> Input;

///  
UProperty<UBitmap, UBAGuiSelection, ptPubParameter> Output;

public: // 
// --------------------------
//   
// --------------------------
UBAGuiSelection(void);
virtual ~UBAGuiSelection(void);
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

//    
virtual bool ACalculate(void);
// --------------------------

// --------------------------
//     
// --------------------------
protected:
//        
virtual bool AFCDefault(void)=0;

//     
//   
//    Reset()   Ready  true
//    
virtual bool AFCBuild(void)=0;

//   .
virtual bool AFCReset(void)=0;

//    
virtual bool AFCCalculate(void)=0;
// --------------------------
};

class RDK_LIB_TYPE UBAGuiSelectionRect: public UBAGuiSelection
{
protected: // 
UGraphics Graphics;
public:
UMouse MouseState;

int CurrentX, CurrentY, PreviousX, PreviousY, IWidth, IHeight, TIWidth, TIHeight;

public: // 
// ---------------------
//   
// ---------------------
UBAGuiSelectionRect(void);
virtual ~UBAGuiSelectionRect(void);
// ---------------------

// ---------------------
//  
// ---------------------
//     
virtual UBAGuiSelectionRect* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);

//    
bool SetImageParams(int width , int height);
int GetIWidth(void);
int GetIHeight(void);

//  ,     
bool SetTImageParamsWH(int wight, int height);
int GetTIWidth(void);
int GetTIHeight(void);

//   
bool SetDecartPrevious(int x, int y);
bool SetDecartCurrent(int x, int y);

int GetRectangleXCurr(void);
int GetRectangleYCurr(void);
int GetRectangleXPrev(void);
int GetRectangleYPrev(void);

bool SetDecartFromMousUse(void);
// ---------------------


// --------------------------
//     
// --------------------------
protected:
//        
virtual bool AFCDefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool AFCBuild(void);

//   .
virtual bool AFCReset(void);

//    
virtual bool AFCCalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif