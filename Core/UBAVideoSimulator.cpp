/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAVIDEO_SIMULATOR_CPP
#define UBAVIDEO_SIMULATOR_CPP

#include "UBAVideoSimulator.h"
//#include "../../UGraphics.h"
//#include "../../UGraphicsXMLSerialize.h"
//#include "../../UGraphicsBinarySerialize.h"
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

//UBAVideoSimulatorSimple UBVideoSimulatorSimple;

/* class UBVSObject */
UBVSObject::UBVSObject(void)
{
  ObjectX=0;
  ObjectY=0;
  ObjectWidth=20;
  ObjectHeight=30;
  XShift=1;
  YShift=0;
  Visible=true;
  Mode=0;
  MovingDirection=0;
};

bool UBVSObject::operator == (const UBVSObject &copy) const
{
    return !memcmp(this, &copy, sizeof(UBVSObject));
}
bool UBVSObject::operator != (const UBVSObject &copy) const
{
    return !(*this == copy);
}

// struct UBVSObject
USerStorageXML& operator << (USerStorageXML& storage, const UBVSObject &data)
{
 storage.SetNodeAttribute("Type","UBVSObject");

 storage.AddNode("ObjectX");
 operator << (storage,data.ObjectX);
 storage.SelectUp();

 storage.AddNode("ObjectY");
 operator << (storage,data.ObjectY);
 storage.SelectUp();

 storage.AddNode("ObjectWidth");
 operator << (storage,data.ObjectWidth);
 storage.SelectUp();

 storage.AddNode("ObjectHeight");
 operator << (storage,data.ObjectHeight);
 storage.SelectUp();

 storage.AddNode("XShift");
 operator << (storage,data.XShift);
 storage.SelectUp();

 storage.AddNode("YShift");
 operator << (storage,data.YShift);
 storage.SelectUp();

 storage.AddNode("Color");
 operator << (storage,data.Color);
 storage.SelectUp();

 storage.AddNode("Color2");
 operator << (storage,data.Color2);
 storage.SelectUp();

 storage.AddNode("Color3");
 operator << (storage,data.Color2);
 storage.SelectUp();

 storage.AddNode("Color4");
 operator << (storage,data.Color2);
 storage.SelectUp();

 storage.AddNode("Mode");
 operator << (storage,data.Mode);
 storage.SelectUp();

 storage.AddNode("Visible");
 operator << (storage,data.Visible);
 storage.SelectUp();

 storage.AddNode("MovingDirection");
 operator << (storage,data.MovingDirection);
 storage.SelectUp();

 return storage;
}

USerStorageXML& operator >> (USerStorageXML& storage, UBVSObject &data)
{
 if(!storage.SelectNode("ObjectX"))
  return storage;
 operator >> (storage,data.ObjectX);
 storage.SelectUp();

 if(!storage.SelectNode("ObjectY"))
  return storage;
 operator >> (storage,data.ObjectY);
 storage.SelectUp();

 if(!storage.SelectNode("ObjectWidth"))
  return storage;
 operator >> (storage,data.ObjectWidth);
 storage.SelectUp();

 if(!storage.SelectNode("ObjectHeight"))
  return storage;
 operator >> (storage,data.ObjectHeight);
 storage.SelectUp();

 if(!storage.SelectNode("XShift"))
  return storage;
 operator >> (storage,data.XShift);
 storage.SelectUp();

 if(!storage.SelectNode("YShift"))
  return storage;
 operator >> (storage,data.YShift);
 storage.SelectUp();

 if(!storage.SelectNode("Color"))
  return storage;
 operator >> (storage,data.Color);
 storage.SelectUp();

 if(!storage.SelectNode("Color2"))
  return storage;
 operator >> (storage,data.Color2);
 storage.SelectUp();

 if(!storage.SelectNode("Color3"))
  return storage;
 operator >> (storage,data.Color3);
 storage.SelectUp();

 if(!storage.SelectNode("Color4"))
  return storage;
 operator >> (storage,data.Color4);
 storage.SelectUp();

 if(!storage.SelectNode("Mode"))
  return storage;
 operator >> (storage,data.Mode);
 storage.SelectUp();

 if(!storage.SelectNode("Visible"))
  return storage;
 operator >> (storage,data.Visible);
 storage.SelectUp();

 if(!storage.SelectNode("MovingDirection"))
  return storage;
 operator >> (storage,data.MovingDirection);
 storage.SelectUp();

 return storage;
}

USerStorageBinary& operator << (USerStorageBinary& storage, const UBVSObject &data)
{
 operator << (storage,data.ObjectX);
 operator << (storage,data.ObjectY);
 operator << (storage,data.ObjectWidth);
 operator << (storage,data.ObjectHeight);
 operator << (storage,data.XShift);
 operator << (storage,data.YShift);
 operator << (storage,data.Color);
 operator << (storage,data.Color2);
 operator << (storage,data.Color3);
 operator << (storage,data.Color4);
 operator << (storage,data.Visible);
 operator << (storage,data.MovingDirection);

 return storage;
}

USerStorageBinary& operator >> (USerStorageBinary& storage, UBVSObject &data)
{
 operator >> (storage,data.ObjectX);
 operator >> (storage,data.ObjectY);
 operator >> (storage,data.ObjectWidth);
 operator >> (storage,data.ObjectHeight);
 operator >> (storage,data.XShift);
 operator >> (storage,data.YShift);
 operator >> (storage,data.Color);
 operator >> (storage,data.Color2);
 operator >> (storage,data.Color3);
 operator >> (storage,data.Color4);
 operator >> (storage,data.Visible);
 operator >> (storage,data.MovingDirection);

 return storage;
}



// ---------------------
// ������������ � �����������
// ---------------------
UBAVideoSimulator::UBAVideoSimulator(void)
: BgMode("BgMode",this),
  BgColor("BgColor",this),
  HideAllFlag("HideAllFlag",this),
  NumObjects("NumObjects",this),
  WorkArea("WorkArea",this),
  ShowGrid("ShowGrid",this),
  PixelGridStep("PixelGridStep",this),
  PixelGridColor("PixelGridColor",this),
  PixelGridWidth("PixelGridWidth",this),
  InputData("InputData",this),
  Input("Input",this),
  Output("Output",this),
  Objects("Objects",this)
{
 // ����� ���������
 BgMode=0;

 // ����� ��������
 NumObjects=0;

 // ������� ����������� ������
 CurrentObjectIndex=0;

 // ���� ������� ���� �������� � �����������
 HideAllFlag=false;

 Graphics=0;

 WorkArea.v.X=0;
 WorkArea.v.Y=0;
 WorkArea.v.X2(360-1);
 WorkArea.v.Y2(240-1);
}

UBAVideoSimulator::~UBAVideoSimulator(void)
{
 ClearObjects();
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ����� ���������� ���� ���������
// (�� ������������)
const int& UBAVideoSimulator::GetBgMode(void) const
{
 return BgMode.v;
}

bool UBAVideoSimulator::SetBgMode(const int &value)
{
 if(value == BgMode)
  return true;

 BgMode=value;
 return true;
}

// ���� ������� ���� �������� � �����������
const bool& UBAVideoSimulator::GetHideAllFlag(void) const
{
 return HideAllFlag.v;
}

bool UBAVideoSimulator::SetHideAllFlag(const bool &value)
{
 if(value == HideAllFlag)
  return true;

 HideAllFlag=value;
 return true;
}

// ������� ������� �������
const UBRect& UBAVideoSimulator::GetWorkArea(void) const
{
 return WorkArea.v;
}

bool UBAVideoSimulator::SetWorkArea(const UBRect &value)
{
 if(WorkArea.v == value)
  return true;

 WorkArea = value;
 return true;
}
// ---------------------

// ---------------------
// ������ ���������� �������
// ---------------------
// ������� ��� �������
void UBAVideoSimulator::ClearObjects(void)
{
 Objects.resize(0);
 NumObjects=0;
}

// ����� ��������
const int& UBAVideoSimulator::GetNumObjects(void) const
{
 return NumObjects.v;
}

bool UBAVideoSimulator::SetNumObjects(const int &value)
{
 if(NumObjects == value)
  return true;

 Objects.resize(value);
 NumObjects=value;
 return true;
}

// ������ ��������
const UBVSObject& UBAVideoSimulator::GetObjectData(int index) const
{
 return Objects[index];
}

bool UBAVideoSimulator::SetObjectData(int index, const UBVSObject &data)
{
 Objects[index]=data;
 return true;
}

const UBVSObject& UBAVideoSimulator::GetCurrentObjectData(void) const
{
 return Objects[CurrentObjectIndex];
}

bool UBAVideoSimulator::SetCurrentObjectData(const UBVSObject &data)
{
 Objects[CurrentObjectIndex]=data;
 return true;
}

// ������� ����������� ������
int UBAVideoSimulator::GetCurrentObjectIndex(void) const
{
 return CurrentObjectIndex;
}

bool UBAVideoSimulator::SetCurrentObjectIndex(int value)
{
 if(CurrentObjectIndex == value)
  return true;

 CurrentObjectIndex=value;
 return true;
}
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAVideoSimulator::ADefault(void)
{
 return AFSDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAVideoSimulator::ABuild(void)
{
 return AFSBuild();
}

// ����� �������� ����� ��� ������ ��������
bool UBAVideoSimulator::AReset(void)
{
 return AFSReset();
}

// ��������� ������ ����� �������
bool UBAVideoSimulator::ACalculate(void)
{
 return AFSCalculate();
}
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAVideoSimulator::AFSDefault(void)
{
 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAVideoSimulator::AFSBuild(void)
{
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBAVideoSimulator::AFSReset(void)
{
 return true;
}

// ��������� ������ ����� �������
bool UBAVideoSimulator::AFSCalculate(void)
{
 return true;
}
// --------------------------


/* UBAVideoSimulatorSimple */
// ---------------------
// ������������ � �����������
// ---------------------
UBAVideoSimulatorSimple::UBAVideoSimulatorSimple(void)
{
 Graphics=new UGraphics;
}

UBAVideoSimulatorSimple::~UBAVideoSimulatorSimple(void)
{
 if(Graphics)
 {
  delete Graphics;
  Graphics=0;
 }
}
// ---------------------

// ---------------------
// ������ ���������� �����������
// ---------------------
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBAVideoSimulatorSimple *UBAVideoSimulatorSimple::New(void)
{
 return new UBAVideoSimulatorSimple;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
void UBAVideoSimulatorSimple::CreateFillBackground(UBitmap &canvas)
{
 canvas.Fill(BgColor);
}

// �������������� �������� �� ��������� � ����� �������� �����
bool UBAVideoSimulatorSimple::AFSDefault(void)
{
 SetNumObjects(2);
 UBVSObject object;
 object.ObjectX=0;
 object.ObjectY=0;
 object.ObjectWidth=30;
 object.ObjectHeight=15;
 object.XShift=2;
 object.YShift=-1;
 object.Color=UColorT(255,0,255);
 object.Visible=true;
 object.MovingDirection=1;
 SetObjectData(0,object);

 object.ObjectX=0;
 object.ObjectY=0;
 object.ObjectWidth=20;
 object.ObjectHeight=40;
 object.XShift=4;
 object.YShift=-3;
 object.Color=UColorT(0,255,0);
 object.Visible=true;
 object.MovingDirection=-1;
 SetObjectData(1,object);

 SetHideAllFlag(true);

 ShowGrid=false;
 PixelGridStep=30;
 PixelGridColor=0x00FFFFFF;
 PixelGridWidth=2;

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAVideoSimulatorSimple::AFSBuild(void)
{
// SetOutputColorModel(0,ubmRGB24);
 return true;
}

// ����� �������� ����� ��� ������ ��������
bool UBAVideoSimulatorSimple::AFSReset(void)
{
 return true;
}

#ifdef __BORLANDC__
#pragma warn -8058
#endif
// ��������� ������ ����� �������
bool UBAVideoSimulatorSimple::AFSCalculate(void)
{
 Canvas.SetRes(Input->GetWidth(),Input->GetHeight(),ubmRGB24);
 static_cast<UGraphics*>(Graphics)->SetCanvas(&Canvas);

 Input->ConvertTo(Canvas);

 // ��� �������������� ���...
 switch(BgMode)
 {
 case 0:
 break;

 case 1:
  CreateFillBackground(Canvas);
 break;

 case 2:
//  CreateLineBackground(BgLines,Canvas);
 break;
 }
 // ����� ������������� ����

 for(int i=0;i<NumObjects;i++)
 {
  UBVSObject &object=Objects[i];
  if(HideAllFlag)
   break;

  if(!object.Visible)
   continue;

  Graphics->SetPenColor(object.Color);
  Graphics->SetPenWidth(1);
  if(object.Mode == 0)
  {
   Graphics->Rect(object.ObjectX-object.ObjectWidth/2,object.ObjectY-object.ObjectHeight/2,
			object.ObjectX+object.ObjectWidth/2,object.ObjectY+object.ObjectHeight/2,true);
  }
  else
  if(object.Mode == 1)
  {
   Graphics->SetPenWidth(1);
   int n=0;
   for(int k=object.ObjectY-object.ObjectHeight/2; k<object.ObjectY+object.ObjectHeight/2; k++)
   {
	UColorT color;
	unsigned char channel=n*(object.Color2.rgb.r-object.Color.rgb.r)/object.ObjectHeight+object.Color.rgb.r;
	color.rgb.r=channel;
	channel=n*(object.Color2.rgb.g-object.Color.rgb.g)/object.ObjectHeight+object.Color.rgb.g;
	color.rgb.g=channel;
	channel=n*(object.Color2.rgb.b-object.Color.rgb.b)/object.ObjectHeight+object.Color.rgb.b;
	color.rgb.b=channel;
	Graphics->SetPenColor(color);
	Graphics->Line(object.ObjectX-object.ObjectWidth/2,k,object.ObjectX+object.ObjectWidth/2,k);
	++n;
   }
  }
  else
  if(object.Mode == 2)
  {
   Graphics->SetPenWidth(1);
   int n=0,m=0;
   for(int k=object.ObjectY-object.ObjectHeight/2; k<object.ObjectY+object.ObjectHeight/2; k++)
   {
	UColorT color, color2;

	unsigned char channel=n*(object.Color2.rgb.r-object.Color.rgb.r)/object.ObjectHeight+object.Color.rgb.r;
	color.rgb.r=channel;
	channel=n*(object.Color2.rgb.g-object.Color.rgb.g)/object.ObjectHeight+object.Color.rgb.g;
	color.rgb.g=channel;
	channel=n*(object.Color2.rgb.b-object.Color.rgb.b)/object.ObjectHeight+object.Color.rgb.b;
	color.rgb.b=channel;

	m=0;
	for(int l=object.ObjectX-object.ObjectWidth/2; l<object.ObjectX+object.ObjectWidth/2; l++)
	{
	 channel=m*(object.Color4.rgb.r-object.Color3.rgb.r)/object.ObjectWidth+object.Color3.rgb.r;
	 color2.rgb.r=channel;
	 channel=m*(object.Color4.rgb.g-object.Color3.rgb.g)/object.ObjectWidth+object.Color3.rgb.g;
	 color2.rgb.g=channel;
	 channel=m*(object.Color4.rgb.b-object.Color3.rgb.b)/object.ObjectWidth+object.Color3.rgb.b;
	 color2.rgb.b=channel;

	 color.rgb.r=(int(color.rgb.r)+int(color2.rgb.r))/2;
	 color.rgb.g=(int(color.rgb.g)+int(color2.rgb.g))/2;
	 color.rgb.b=(int(color.rgb.b)+int(color2.rgb.b))/2;
	 Graphics->SetPenColor(color);
	 Graphics->Pixel(l,k);
	 ++m;
	}
	++n;
   }
  }

  object.ObjectX+=object.XShift; object.ObjectY+=object.YShift;
  if((object.ObjectX>=WorkArea.v.X+WorkArea.v.Width && object.XShift>0) || (object.ObjectX<WorkArea.v.X && object.XShift<0) )
   object.XShift=-object.XShift;
  if((object.ObjectY>=WorkArea.v.Y+WorkArea.v.Height && object.YShift>0) || (object.ObjectY<WorkArea.v.Y && object.YShift<0))
   object.YShift=-object.YShift;
 }

 if(ShowGrid)
 {
  Graphics->SetPenColor(PixelGridColor);
  Graphics->SetPenWidth(PixelGridWidth);
  for(int i=0;i<Canvas.GetHeight();i+=PixelGridStep)
   Graphics->Line(0,i,Canvas.GetWidth()-1,i);
  for(int i=0;i<Canvas.GetWidth();i+=PixelGridStep)
   Graphics->Line(i,0,i,Canvas.GetWidth()-1);
 }


 *Output=Canvas;

 return true;

}
#ifdef __BORLANDC__
#pragma warn .8058
#endif
// --------------------------


// ---------------------
// ---------------------
// ������������ � �����������
// ---------------------
UBAVideoSimulatorSimpleBin::UBAVideoSimulatorSimpleBin(void)
    :BinarOutput("BinarOutput", this),
     countFirstCleanBgFrame ("countFirstCleanBgFrame", this)

{
 Graphics=new UGraphics;
}

UBAVideoSimulatorSimpleBin::~UBAVideoSimulatorSimpleBin(void)
{
 if(Graphics)
 {
  delete Graphics;
  Graphics=0;
 }
 nCounterBG=0;
 countFirstCleanBgFrame = 30;
}
// ---------------------
// ������ ���������� �����������
// ---------------------
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBAVideoSimulatorSimpleBin *UBAVideoSimulatorSimpleBin::New(void)
{
 return new UBAVideoSimulatorSimpleBin;
}
// ---------------------


// --------------------------
// ������� ������ ���������� ������ �������� �����������
// --------------------------
void UBAVideoSimulatorSimpleBin::CreateFillBackground(UBitmap &canvas)
{
 canvas.Fill(BgColor);
}

// �������������� �������� �� ��������� � ����� �������� �����
bool UBAVideoSimulatorSimpleBin::AFSDefault(void)
{
 SetNumObjects(2);
 UBVSObject object;
 object.ObjectX=0;
 object.ObjectY=0;
 object.ObjectWidth=30;
 object.ObjectHeight=15;
 object.XShift=2;
 object.YShift=-1;
 object.Color=UColorT(255,0,255);
 object.Visible=true;
 object.MovingDirection=1;
 SetObjectData(0,object);

 object.ObjectX=0;
 object.ObjectY=0;
 object.ObjectWidth=20;
 object.ObjectHeight=40;
 object.XShift=4;
 object.YShift=-3;
 object.Color=UColorT(0,255,0);
 object.Visible=true;
 object.MovingDirection=-1;
 SetObjectData(1,object);

 SetHideAllFlag(true);

 return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAVideoSimulatorSimpleBin::AFSBuild(void)
{
// SetOutputColorModel(0,ubmRGB24);
 return true;
}


void UBAVideoSimulatorSimpleBin::DrawSimple (UBitmap &canvas, int isBin)
{
    static_cast<UGraphics*>(Graphics)->SetCanvas(&canvas);
    for(int i=0;i<NumObjects;i++)
    {
     UBVSObject &object=Objects[i];
     if(HideAllFlag)
      break;

     if(!object.Visible)
      continue;

     UColorT colorBlack;
     colorBlack.rgb.r=0;
     colorBlack.rgb.g=0;
     colorBlack.rgb.b=0;

     UColorT colorWhite;
     colorWhite.rgb.r=255;
     colorWhite.rgb.g=255;
     colorWhite.rgb.b=255;

     if (isBin == 1)
     {
         Graphics->SetPenColor(colorWhite);
     }
     else
     {
         Graphics->SetPenColor(object.Color);
     }
     if(object.Mode == 0)
     {
      Graphics->Rect(object.ObjectX-object.ObjectWidth/2,object.ObjectY-object.ObjectHeight/2,
               object.ObjectX+object.ObjectWidth/2,object.ObjectY+object.ObjectHeight/2,true);

     }
     else
     if(object.Mode == 1)
     {
      Graphics->SetPenWidth(1);
      int n=0;
      for(int k=object.ObjectY-object.ObjectHeight/2; k<object.ObjectY+object.ObjectHeight/2; k++)
      {
       UColorT color;
       unsigned char channel=n*(object.Color2.rgb.r-object.Color.rgb.r)/object.ObjectHeight+object.Color.rgb.r;
       color.rgb.r=channel;
       channel=n*(object.Color2.rgb.g-object.Color.rgb.g)/object.ObjectHeight+object.Color.rgb.g;
       color.rgb.g=channel;
       channel=n*(object.Color2.rgb.b-object.Color.rgb.b)/object.ObjectHeight+object.Color.rgb.b;
       color.rgb.b=channel;
       if (isBin == 1)
           Graphics->SetPenColor(colorWhite);
       else
           Graphics->SetPenColor(color);
       Graphics->Line(object.ObjectX-object.ObjectWidth/2,k,object.ObjectX+object.ObjectWidth/2,k);
       ++n;
      }
     }
     else
     if(object.Mode == 2)
     {
      Graphics->SetPenWidth(1);
      int n=0,m=0;
      for(int k=object.ObjectY-object.ObjectHeight/2; k<object.ObjectY+object.ObjectHeight/2; k++)
      {
       UColorT color, color2;

       unsigned char channel=n*(object.Color2.rgb.r-object.Color.rgb.r)/object.ObjectHeight+object.Color.rgb.r;
       color.rgb.r=channel;
       channel=n*(object.Color2.rgb.g-object.Color.rgb.g)/object.ObjectHeight+object.Color.rgb.g;
       color.rgb.g=channel;
       channel=n*(object.Color2.rgb.b-object.Color.rgb.b)/object.ObjectHeight+object.Color.rgb.b;
       color.rgb.b=channel;

       m=0;
       for(int l=object.ObjectX-object.ObjectWidth/2; l<object.ObjectX+object.ObjectWidth/2; l++)
       {
        channel=m*(object.Color4.rgb.r-object.Color3.rgb.r)/object.ObjectWidth+object.Color3.rgb.r;
        color2.rgb.r=channel;
        channel=m*(object.Color4.rgb.g-object.Color3.rgb.g)/object.ObjectWidth+object.Color3.rgb.g;
        color2.rgb.g=channel;
        channel=m*(object.Color4.rgb.b-object.Color3.rgb.b)/object.ObjectWidth+object.Color3.rgb.b;
        color2.rgb.b=channel;

        color.rgb.r=(int(color.rgb.r)+int(color2.rgb.r))/2;
        color.rgb.g=(int(color.rgb.g)+int(color2.rgb.g))/2;
        color.rgb.b=(int(color.rgb.b)+int(color2.rgb.b))/2;

        if (isBin == 1)
            Graphics->SetPenColor(colorWhite);
        else
            Graphics->SetPenColor(color);

        Graphics->Pixel(l,k);
        ++m;
       }
       ++n;
      }
     }

     object.ObjectX+=object.XShift; object.ObjectY+=object.YShift;
     if((object.ObjectX>=WorkArea.v.X+WorkArea.v.Width && object.XShift>0) || (object.ObjectX<WorkArea.v.X && object.XShift<0) )
      object.XShift=-object.XShift;
     if((object.ObjectY>=WorkArea.v.Y+WorkArea.v.Height && object.YShift>0) || (object.ObjectY<WorkArea.v.Y && object.YShift<0))
      object.YShift=-object.YShift;
    }

}


// ����� �������� ����� ��� ������ ��������
bool UBAVideoSimulatorSimpleBin::AFSReset(void)
{
 nCounterBG = 0;
 return true;
}

#ifdef __BORLANDC__
#pragma warn -8058
#endif
// ��������� ������ ����� �������
bool UBAVideoSimulatorSimpleBin::AFSCalculate(void)
{
 //if (nCounterBG > countFirstCleanBgFrame)
// {

     Canvas.SetRes(Input->GetWidth(),Input->GetHeight(),ubmRGB24);
     static_cast<UGraphics*>(Graphics)->SetCanvas(&Canvas);
     //���������� ��������� ��������� ����������� ������ �����
     BinarOutput->SetRes(Input->GetWidth(),Input->GetHeight(),ubmRGB24); //ubmY8
     Input->ConvertTo(Canvas);
     // ��� �������������� ���...
     switch(BgMode)
     {
     case 0:
     break;

     case 1:
      CreateFillBackground(Canvas);
     break;

     case 2:
    //  CreateLineBackground(BgLines,Canvas);
     break;
     }
     // ����� ������������� ����
     DrawSimple(Canvas,0);

    // output.SetColorModel(ubmY8);
    // Canvas.ConvertTo(output);
     if (nCounterBG > countFirstCleanBgFrame)
        *Output=Canvas;
     else
     {
         nCounterBG++;
         *Output=*Input;
     }



     CanvasBin.SetRes(Input->GetWidth(),Input->GetHeight(),ubmRGB24);
     //static_cast<UGraphics*>(Graphics)->SetCanvas(&CanvasBin);
     CanvasBin.Fill(0);
     DrawSimple(CanvasBin,1);
     BinarOutput->SetColorModel(ubmY8,false);
     CanvasBin.ConvertTo(*BinarOutput);
     //BinarOutput->Fill(0);
     //*BinarOutput=CanvasBin;
 //}
// else {
 //    nCounterBG++;
// }

 return true;

}
#ifdef __BORLANDC__
#pragma warn .8058
#endif

}

#endif

