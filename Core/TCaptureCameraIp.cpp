/* ***********************************************************

*********************************************************** */

#ifndef TCaptureCameraIp_CPP
#define TCaptureCameraIp_CPP

#include "TCaptureCameraIp.h"
namespace RDK
{
// --------------------------
// Конструкторы и деструкторы
// --------------------------
TCaptureCameraIp::TCaptureCameraIp(void)
: Address("Address",this,&TCaptureCameraIp::SetAddress),
  Login("Login",this,&TCaptureCameraIp::SetLogin),
  Password("Password",this,&TCaptureCameraIp::SetPassword)
{

}
TCaptureCameraIp::~TCaptureCameraIp(void)
{

}
// --------------------------
// Методы управления параметрами
// --------------------------
/// Установка адреса соединения
bool TCaptureCameraIp::SetAddress(const std::string &num)
{
 Ready=false;
 return true;
}
/// Установка имени пользователя
bool TCaptureCameraIp::SetLogin(const std::string &num)
{
 Ready=false;
 return true;
}
/// Установка пароля
bool TCaptureCameraIp::SetPassword(const std::string &num)
{
 Ready=false;
 return true;
}
// --------------------------
// Скрытые методы
// --------------------------
bool TCaptureCameraIp::ASetEnableCapture1(const bool &value)
{
 return ASetEnableCapture2(value);
}
// --------------------------
bool TCaptureCameraIp::AStartCapture1(void)
{
 return AStartCapture2();
}
// --------------------------
bool TCaptureCameraIp::AStopCapture1(void)
{
 return AStopCapture2();
}
// --------------------------
// --------------------------
bool TCaptureCameraIp::ADefault2(void)
{
 return ADefault3();
}
// --------------------------
bool TCaptureCameraIp::ABuild2(void)
{
 return ABuild3();
}
// --------------------------
bool TCaptureCameraIp::AReset2(void)
{
 return AReset3();
}
// --------------------------
bool TCaptureCameraIp::ACalculate2(void)
{
 return ACalculate3();
}
// --------------------------
}
#endif