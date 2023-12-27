#include "UBAGuiSelection.h"
//#include "../../UGraphics.h"
#include "../../../Rdk/Deploy/Include/rdk.h"
#include <math.h>

namespace RDK {

// ������ ���������� �����������
//���������� ����
UMouse::UMouse(void)
{
 LeftClickMouse.Previous = 0;
 LeftClickMouse.Current = 0;
 RightClickMouse.Previous = 0;
 RightClickMouse.Current= 0;
};

UMouse::~UMouse(void)
{};


bool UMouse::SetDecartMouse(int x, int y)
{
	if(x < 0 && y < 0)
  return false;

 if( X_mouse == x && Y_mouse == y)
  return true;

 X_mouse = x;
 Y_mouse = y;
 return true;
}

int UMouse::GetX_Mouse(void)
{
	return X_mouse;
	}

int UMouse::GetY_Mouse(void)
{
	return Y_mouse;
	}


//������ ���������� �������� ����(on/off)
//�������� ����� ���� ���� 0, ���� 1
//1 - ������ ������
//0 - ������ �� ������
bool UMouse::SetModeLCMouse(int click)
{
	if(click > 1 && click < 0)
	return false;

	LeftClickMouse.Previous = LeftClickMouse.Current;
	LeftClickMouse.Current = click;

	return true;
}



bool UMouse::SetModeRCMouse(int click)
{
 if(click > 1 && click < 0)
  return false;

 RightClickMouse.Previous = RightClickMouse.Current;
 RightClickMouse.Current = click;
 return true;
}



// ---------------------
StateTMouse UMouse::GetModeLCMouse(void)
{
 return LeftClickMouse;
}

StateTMouse UMouse::GetModeRCMouse(void)
{
 return RightClickMouse;
}
// ---------------------


// --------------------------
// ������������ � �����������
// --------------------------
UBAGuiSelection::UBAGuiSelection(void)
: Input("Input",this),
  Output("Output",this)
{

}

UBAGuiSelection::~UBAGuiSelection(void)
{

}
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAGuiSelection::ADefault(void)
{
 return AFCDefault();
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAGuiSelection::ABuild(void)
{
 return AFCBuild();
}

// ����� �������� �����.
bool UBAGuiSelection::AReset(void)
{
 return AFCReset();
}

// ��������� ������ ����� �������
bool UBAGuiSelection::ACalculate(void)
{
 if(!AFCCalculate())
  return false;

 return true;
}
// --------------------------

// ---------------------
// ������������ � �����������
// ---------------------
UBAGuiSelectionRect::UBAGuiSelectionRect(void)
{

}
// ---------------------
 UBAGuiSelectionRect::~UBAGuiSelectionRect(void)
{

}
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
UBAGuiSelectionRect* UBAGuiSelectionRect::New(void)
{
 return new UBAGuiSelectionRect;
}

// ������� ��������� �������� �����������
bool UBAGuiSelectionRect::SetImageParams(int width , int height)
{

	if(width<=0 && height<=0)
	return false;
	if(IWidth == width && IHeight == height)
	return true;

	IWidth = width;
	IHeight = height;
	return true;
}

 int UBAGuiSelectionRect::GetIWidth(void)
 {
	return IWidth;
	}

 int UBAGuiSelectionRect::GetIHeight(void)
 {
	return IHeight;
	}

//������� ��������� �������, ��� � ��� ��������� �����������
 bool UBAGuiSelectionRect::SetTImageParamsWH(int wight, int height)
 {
	if(wight<=0 && height<=0)
	return false;
	if(TIWidth == wight && TIHeight == height)
	return true;

	TIWidth = wight;
	TIHeight = height;
	return true;
 }

 int UBAGuiSelectionRect::GetTIWidth(void)
 {
	return TIWidth;
	}

 int UBAGuiSelectionRect::GetTIHeight(void)
 {
	return TIHeight;
	}



bool UBAGuiSelectionRect::SetDecartPrevious(int x, int y)
{
   if(x < 0 && y < 0)
	return false;

	if(PreviousX == x && PreviousY == y)
	return true;

	PreviousX = x;
	PreviousY = y;
	return true;
}

bool UBAGuiSelectionRect::SetDecartCurrent(int x, int y)
{
   if(x < 0 && y < 0)
	return false;

	if(CurrentX == x && CurrentY == y)
	return true;

	CurrentX = x;
	CurrentY = y;
	return true;
}



 int UBAGuiSelectionRect::GetRectangleXPrev(void)
 {
	return PreviousX;
	}

 int UBAGuiSelectionRect::GetRectangleYPrev(void)
 {
	return PreviousY;
	}
 int UBAGuiSelectionRect::GetRectangleXCurr(void)
 {
	return CurrentX;
	}
 int UBAGuiSelectionRect::GetRectangleYCurr(void)
 {
	return CurrentY;
	}

bool UBAGuiSelectionRect::SetDecartFromMousUse(void)
{
	StateTMouse LParam = MouseState.GetModeLCMouse();
//	StateTMouse RParam = MouseState.GetModeRCMouse();
	int xm, ym;

	xm =  (MouseState.GetX_Mouse()*GetIWidth())/GetTIWidth();
	ym =  (MouseState.GetY_Mouse()*GetIHeight())/GetTIHeight();

	//�������� ���������� ���� � ����������� �� ������� ���

	if (LParam.Current != LParam.Previous && LParam.Current == 1)
		{
			SetDecartPrevious(xm, ym);
			SetDecartCurrent(xm, ym);
		}
	else if (LParam.Current == LParam.Previous && LParam.Current == 1)
		{
			SetDecartCurrent(xm, ym);
		}

  return true;
}

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
// �������������� �������� �� ��������� � ����� �������� �����
bool UBAGuiSelectionRect::AFCDefault(void)
{
  return true;
}

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
bool UBAGuiSelectionRect::AFCBuild(void)
{
  return true;
}

// ����� �������� �����.
bool UBAGuiSelectionRect::AFCReset(void)
{
  return true;
}

// ��������� ������ ����� �������
bool UBAGuiSelectionRect::AFCCalculate(void)
{
 int x= Input->GetWidth();
 int y= Input->GetHeight();

 SetImageParams(x, y);
 SetDecartFromMousUse(); //�������� ���������� ����;

 Output->SetRes(Input->GetWidth(), Input->GetHeight(), ubmRGB24);
 Input->ConvertTo(*Output);

 Graphics.SetCanvas(&Output.v);

 Graphics.SetPenWidth(5);
 Graphics.SetPenColor(UColorT(0x00FF0000));

 Graphics.Rect( GetRectangleXPrev(),
	GetIHeight() - GetRectangleYPrev(),
	GetRectangleXCurr(),
	GetIHeight() - GetRectangleYCurr(), false);

 return true;

}
// --------------------------


}
