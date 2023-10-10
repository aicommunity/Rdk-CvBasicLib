/* ***********************************************************

*********************************************************** */

#ifndef TCapture_CPP
#define TCapture_CPP

#include "TCapture.h"

namespace RDK
{
// --------------------------
// Конструкторы и деструкторы
// --------------------------
TCapture::TCapture(void)
: DesiredFps("DesiredFps",this,&TCapture::SetDesiredFps),
  CloseTimeout("CloseTimeout",this,&TCapture::SetCloseTimeout),
  ReconnectTimeout("ReconnectTimeout",this,&TCapture::SetReconnectTimeout),
  CaptureTimeout("CaptureTimeout",this,&TCapture::SetCaptureTimeout),
  RestartMode("RestartMode",this,&TCapture::SetRestartMode),
  DesiredWidth("DesiredWidth",this,&TCapture::SetDesiredWidth),
  DesiredHeight("DesiredHeight",this,&TCapture::SetDesiredHeight),
  DesiredResolutionFlag("DesiredResolutionFlag",this,&TCapture::SetDesiredResolutionFlag),
  CameraType("CameraType",this,&TCapture::SetCameraType),
  OutputImage("OutputImage",this),
  CaptureTime("CaptureTime", this),
  EnableCapture("EnableCapture", this, &TCapture::SetEnableCapture),
  Paused("Paused",this, &TCapture::SetPaused),
  FlipX("FlipX", this, &TCapture::SetFlipX),
  FlipY("FlipY", this, &TCapture::SetFlipY),
  RelevData("RelevData", this, &TCapture::SetRelevData),
  RotationAngle("RotationAngle", this, &TCapture::SetRotationAngle),
  FixedRotation("FixedRotation",this, &TCapture::SetFixedRotation),
  NumFrames("NumFrames",this),
  CaptureFps("CaptureFps",this),
  RealFps("RealFps",this),
  CaptureState("CaptureState",this),
  FramePosition("FramePosition",this),
  FrameTime("FrameTime",this)


{

}
TCapture::~TCapture(void)
{

}
// --------------------------
// Методы управления параметрами
// --------------------------
/// Установка желаемой частоты кадров
bool TCapture::SetDesiredFps(const double &value)
{
 return ASetDesiredFps(value);
}

bool TCapture::ASetDesiredFps(const double &value)
{
 return true;
}

/// Установка флага запуска захвата
bool TCapture::SetCameraType(const int &value)
{
 return ASetCameraType(value);
}

bool TCapture::ASetCameraType(const int &value)
{
 return true;
}


/// Таймаут на ожидание завершения захвата, мс
bool TCapture::SetCloseTimeout(const int &value)
{
 return ASetCloseTimeout(value);
}

bool TCapture::ASetCloseTimeout(const double &value)
{
 return true;
}

/// Таймаут между переподключениями
bool TCapture::SetReconnectTimeout(const int &value)
{
 return ASetReconnectTimeout(value);
}

bool TCapture::ASetReconnectTimeout(const double &value)
{
 return true;
}

bool TCapture::SetCaptureTimeout(const int &value)
{
 return ASetCaptureTimeout(value);
}

bool TCapture::ASetCaptureTimeout(const double &value)
{
 return true;
}

/// Режим восстановления после сбоя захвата
/// 0 - не делать ничего
/// 1 - попытаться восстановить захват
/// 2 - вызвать метод останова захвата
bool TCapture::SetRestartMode(const int &value)
{
 return ASetRestartMode(value);
}

bool TCapture::ASetRestartMode(const double &value)
{
 return true;
}

/// Желаемое разрешение захвата
bool TCapture::SetDesiredWidth(const int &value)
{
 return ASetDesiredWidth(value);
}

bool TCapture::ASetDesiredWidth(const double &value)
{
 return true;
}

bool TCapture::SetDesiredHeight(const int &value)
{
 return ASetDesiredHeight(value);
}

bool TCapture::ASetDesiredHeight(const double &value)
{
 return true;
}

/// Флаг включения выбора желаемого разрешения захвата
bool TCapture::SetDesiredResolutionFlag(const bool &value)
{
 return ASetDesiredResolutionFlag(value);
}

bool TCapture::ASetDesiredResolutionFlag(const bool &value)
{
 return true;
}

/// Установка флага запуска захвата
bool TCapture::SetEnableCapture(const bool &value)
{
 return ASetEnableCapture(value);
}

/// Установка Флага приостановки захвата
bool TCapture::SetPaused(const bool &value)
{
 return ASetPaused(value);
}

bool TCapture::ASetPaused(const bool &value)
{
 return true;
}

/// Инверсия по оси X
bool TCapture::SetFlipX(const bool &value)
{
 return ASetFlipX(value);
}

bool TCapture::ASetFlipX(const bool &value)
{
 return true;
}

/// Инверсия по оси Y
bool TCapture::SetFlipY(const bool &value)
{
 return ASetFlipY(value);
}

bool TCapture::ASetFlipY(const bool &value)
{
 return true;
}

/// Установка угла поворота
bool TCapture::SetRotationAngle(const double &value)
{
 return ASetRotationAngle(value);
}

bool TCapture::ASetRotationAngle(const double &value)
{
 return true;
}

/// Проверка актуальности данных
bool TCapture::SetRelevData(const bool &value)
{
 return true;
}

/// Поворот изображения на фиксированный угол
/// 0 - нет поворота
/// 1 - 90
/// 2 - 180
/// 3 - 270
bool TCapture::SetFixedRotation(const int &value)
{
 return ASetFixedRotation(value);
}

bool TCapture::ASetFixedRotation(const int &value)
{
 return true;
}

int TCapture::GetCaptureState(void)
{
 return CaptureState;
}

// --------------------------
// Методы
// --------------------------
/// Запуск захвата
bool TCapture::StartCapture(void)
{
// Paused=false;
 return AStartCapture();
}
/// Останов захвата
bool TCapture::StopCapture(void)
{
 return AStopCapture();
}

/// Пауза захвата
bool TCapture::PauseCapture(void)
{
// Paused=true;
 return APauseCapture();
}

bool TCapture::APauseCapture(void)
{
 return true;
}


/// Возвращает общее число кадров в источнике
unsigned long long TCapture::GetNumFrames(void) const
{
 return NumFrames;
}

/// Возвращает индекс текущего кадра в источнике
unsigned long long TCapture::GetFramePosition(void) const
{
 return FramePosition;
}

/// Устанавливает имя текущего кадра в источнике
void TCapture::SetFramePosition(unsigned long long value)
{
}


/// Возвращает общее число секунд в источнике
double TCapture::GetTimeDuration(void) const
{
 if(CaptureFps>0)
  return NumFrames/CaptureFps;
 return 0;
}

/// Возвращает текущую секунду в источнике
double TCapture::GetTimePosition(void) const
{
 if(RealFps>0)
  return FrameTime;
 return 0;
}

/// Устанавливает текущую секунду в источнике
void TCapture::SetTimePosition(double value)
{
 SetFramePosition(static_cast<unsigned long long >(value*CaptureFps));
}

/// Перемещает позицию в источнике на value кадров
void TCapture::ChangeRelativeFramePosition(long long value)
{
 unsigned long long position(GetFramePosition());
 if(value>0)
  SetFramePosition(position+value);
 else
 if((unsigned long long)(-value)>position)
  SetFramePosition(0);
 else
  SetFramePosition(position-(unsigned long long)(-value));
}

/// Перемещает позицию в источнике на value секунд
void TCapture::ChangeRelativeTimePosition(double value)
{
 ChangeRelativeFramePosition(static_cast<unsigned long long >(value*CaptureFps));
}

// --------------------------
// Скрытые методы
// --------------------------
bool TCapture::ADefault(void)
{
 RelevData = false;
 DesiredWidth=720;
 DesiredHeight=576;
 DesiredResolutionFlag=false;
 RestartMode=1;
 CloseTimeout=60000;
 ReconnectTimeout=30000;
 CaptureTimeout=10000;
 RotationAngle=0.0;
 FixedRotation=0;
 FlipX=false;
 FlipY=false;
 return ADefault1();
}

bool TCapture::ABuild(void)
{
 return ABuild1();
}

bool TCapture::AReset(void)
{
 FramePosition=0;
 FrameTime=0.0;
 NumFrames=0;
 return AReset1();
}

bool TCapture::ACalculate(void)
{
 if(!ACalculate1())
  return false;

 if(CaptureFps>0)
 {
  FrameTime=FramePosition/CaptureFps;
 }
 if(RelevData)
 {
  if(data_changed)
  {
   data_changed = false;
   return true;
  }
  else
  {
   if(GetOwner())
	GetOwner()->ForceSkipComponentCalculation();
   else
	ForceSkipComponentCalculation();
   return true;
  }
 }
 return true;
}
}
#endif
