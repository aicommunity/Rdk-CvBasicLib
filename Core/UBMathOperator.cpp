/* ***********************************************************
@Copyright Alexander V. Bakhshiev.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBMathOperator_CPP
#define UBMathOperator_CPP

#include "UBMathOperator.h"
#include <math.h>

namespace RDK {

// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBMathOperator::UBMathOperator(void)
 : Input1("Input1",this),
   Input2("Input2",this),
   Output("Output",this),
   OperatorId("OperatorId",this)
{
 OperatorId=0;
}
UBMathOperator::~UBMathOperator(void)
{
}
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
UBMathOperator* UBMathOperator::New(void)
{
 return new UBMathOperator;
}
// ---------------------

// --------------------------
// Методы, реализующие арифметические операции
// --------------------------
void UBMathOperator::And(const UBitmap &in1, const UBitmap &in2, UBitmap &out)
{
 if(in1.GetColorModel() != in2.GetColorModel())
  return;

 if(in1.GetWidth() != in2.GetWidth() || in1.GetHeight() != in2.GetHeight())
  return;

 out.SetRes(in1.GetWidth(),in1.GetHeight(),in1.GetColorModel());
 if(in1.GetColorModel() == ubmY8)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetLength();i++)
   *out_data++=*in1_data++ & *in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmRGB24)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetByteLength();i++)
   *out_data++=*in1_data++ & *in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmRGB32)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetByteLength();i++)
   *out_data++=*in1_data++ & *in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmY32)
 {
  unsigned int *in1_data=reinterpret_cast<unsigned int*>(in1.GetData()),
				*in2_data=reinterpret_cast<unsigned int*>(in2.GetData()),
				*out_data=reinterpret_cast<unsigned int*>(out.GetData());
  for(int i=0;i<in1.GetLength();i++)
   *out_data++=*in1_data++ & *in2_data++;
  return;
 }

}

void UBMathOperator::Or(const UBitmap &in1, const UBitmap &in2, UBitmap &out)
{
 if(in1.GetColorModel() != in2.GetColorModel())
  return;

 if(in1.GetWidth() != in2.GetWidth() || in1.GetHeight() != in2.GetHeight())
  return;

 out.SetRes(in1.GetWidth(),in1.GetHeight(),in1.GetColorModel());
 if(in1.GetColorModel() == ubmY8)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetLength();i++)
   *out_data++=*in1_data++ | *in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmRGB24)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetByteLength();i++)
   *out_data++=*in1_data++ | *in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmRGB32)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetByteLength();i++)
   *out_data++=*in1_data++ | *in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmY32)
 {
  unsigned int *in1_data=reinterpret_cast<unsigned int*>(in1.GetData()),
				*in2_data=reinterpret_cast<unsigned int*>(in2.GetData()),
				*out_data=reinterpret_cast<unsigned int*>(out.GetData());
  for(int i=0;i<in1.GetLength();i++)
   *out_data++=*in1_data++ | *in2_data++;
  return;
 }

}

void UBMathOperator::Sub(const UBitmap &in1, const UBitmap &in2, UBitmap &out)
{
 if(in1.GetColorModel() != in2.GetColorModel())
  return;

 if(in1.GetWidth() != in2.GetWidth() || in1.GetHeight() != in2.GetHeight())
  return;

 out.SetRes(in1.GetWidth(),in1.GetHeight(),in1.GetColorModel());
 if(in1.GetColorModel() == ubmY8)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetLength();i++)
   *out_data++=max(0,(int)(*in1_data++)) - (int)*in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmRGB24)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetByteLength();i++)
   *out_data++=max(0,(int)(*in1_data++)) - (int)*in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmRGB32)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetByteLength();i++)
   *out_data++=max(0,(int)(*in1_data++)) - (int)*in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmY32)
 {
  unsigned int *in1_data=reinterpret_cast<unsigned int*>(in1.GetData()),
				*in2_data=reinterpret_cast<unsigned int*>(in2.GetData()),
				*out_data=reinterpret_cast<unsigned int*>(out.GetData());
  for(int i=0;i<in1.GetLength();i++)
   *out_data++=max(0,(int)(*in1_data++)) - (int)*in2_data++;
  return;
 }
}

void UBMathOperator::Sum(const UBitmap &in1, const UBitmap &in2, UBitmap &out)
{
 if(in1.GetColorModel() != in2.GetColorModel())
  return;

 if(in1.GetWidth() != in2.GetWidth() || in1.GetHeight() != in2.GetHeight())
  return;

 out.SetRes(in1.GetWidth(),in1.GetHeight(),in1.GetColorModel());
 if(in1.GetColorModel() == ubmY8)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetLength();i++)
   *out_data++=(unsigned char)min(255,(int)(*in1_data++)) + (int)*in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmRGB24)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetByteLength();i++)
   *out_data++=(unsigned char)min(255,(int)(*in1_data++)) + (int)*in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmRGB32)
 {
  unsigned char *in1_data=in1.GetData(), *in2_data=in2.GetData(), *out_data=out.GetData();
  for(int i=0;i<in1.GetByteLength();i++)
   *out_data++=(unsigned char)min(255,(int)(*in1_data++)) + (int)*in2_data++;
  return;
 }

 if(in1.GetColorModel() == ubmY32)
 {
  unsigned int *in1_data=reinterpret_cast<unsigned int*>(in1.GetData()),
				*in2_data=reinterpret_cast<unsigned int*>(in2.GetData()),
				*out_data=reinterpret_cast<unsigned int*>(out.GetData());
  for(int i=0;i<in1.GetLength();i++)
   *out_data++=(unsigned char)min(255,(int)(*in1_data++)) + (int)*in2_data++;
  return;
 }
}
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
// Восстановление настроек по умолчанию и сброс процесса счета
bool UBMathOperator::ADefault(void)
{
 //SetNumOutputs(1);
 return true;
}

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
bool UBMathOperator::ABuild(void)
{
 return true;
}

// Сброс процесса счета без потери настроек
bool UBMathOperator::AReset(void)
{
 return true;
}

// Выполняет расчет этого объекта
bool UBMathOperator::ACalculate(void)
{
 switch(OperatorId)
 {
 case ubmAnd:
  if(!Input1.IsConnected() || !Input2.IsConnected())
   return true;
  And(*Input1,*Input2,*Output);
 break;

 case ubmOr:
  if(!Input1.IsConnected() || !Input2.IsConnected())
   return true;
  Or(*Input1,*Input2,*Output);
 break;

 case ubmXor:
  if(!Input1.IsConnected() || !Input2.IsConnected())
   return true;
 break;

 case ubmNot:
  if(!Input1.IsConnected())
   return true;
  Input1->Inverse(&*Output);
 break;

 case ubmSum:
  if(!Input1.IsConnected() || !Input2.IsConnected())
   return true;
 break;

 case ubmSub:
  if(!Input1.IsConnected() || !Input2.IsConnected())
   return true;
  Sub(*Input1,*Input2,*Output);
 break;

 case ubmSubAbs:
  if(!Input1.IsConnected() || !Input2.IsConnected())
   return true;
 break;
 }
 return true;
}
// --------------------------

}
//---------------------------------------------------------------------------

#endif


