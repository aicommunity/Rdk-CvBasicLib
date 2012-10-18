/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBARotateH
#define UBARotateH
#include "../../UBAbstract.h"

namespace RDK {

// Базовый класс поворота изображения
class UBARotate: public UBAbstract
{
protected: // Параметры
// Угол поворота (градусы)
float Angle;

// Флаг расширения
bool Enlarge;

protected: // Временные переменные
UBitmap Buffer;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBARotate(void);
virtual ~UBARotate(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// Угол поворота (градусы)
float GetAngle(void) const;
bool SetAngle(float angle);

// Флаг расширения
bool GetEnlarge(void) const;
bool SetEnlarge(bool enlarge);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
virtual bool PLACalculate(UBitmap **input, UBitmap **output, int num_inputs=1, int num_outputs=1);
virtual bool BCalculate(UBitmap &input, UBitmap &output)=0;
bool BCalculate(UBitmap &input, UBitmap &output, float angle, bool enlarge=false);
bool BCalculate(UBitmap &input, float angle, bool enlarge=false);
// ---------------------

// ---------------------
// Операторы
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, UBitmap &output, float angle, bool enlarge=false);
bool operator () (UBitmap &input, float angle, bool enlarge=false);
// ---------------------
};

// Поворачивает изображение на заданный угол
class UBARotateSimple: public UBARotate
{
public: // Методы
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBARotateSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------
};

//extern UBARotateSimple UBRotateSimple;
}
//---------------------------------------------------------------------------
#endif

