/* ***********************************************************

*********************************************************** */

#ifndef TCaptureCamera_CPP
#define TCaptureCamera_CPP

#include "TCaptureCamera.h"

namespace RDK
{
// --------------------------
// Конструкторы и деструкторы
// --------------------------
TCaptureCamera::TCaptureCamera(void)
{

}
TCaptureCamera::~TCaptureCamera(void)
{
}
// --------------------------
// Скрытые методы
// --------------------------
bool TCaptureCamera::ASetEnableCapture(const bool &value)
{
 return ASetEnableCapture1(value);
}
// --------------------------
bool TCaptureCamera::AStartCapture(void)
{
 return AStartCapture1();
}
// --------------------------
bool TCaptureCamera::AStopCapture(void)
{
 return AStopCapture1();
}
// --------------------------
// --------------------------
bool TCaptureCamera::ADefault1(void)
{
 return ADefault2();
}
// --------------------------
bool TCaptureCamera::ABuild1(void)
{
 return ABuild2();
}
// --------------------------
bool TCaptureCamera::AReset1(void)
{
 return AReset2();
}
// --------------------------
bool TCaptureCamera::ACalculate1(void)
{
 return ACalculate2();
}
// --------------------------

}
#endif
