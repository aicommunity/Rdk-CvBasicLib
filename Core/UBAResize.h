/* ***********************************************************
@Copyright Alexander V. Bakhshiev, Anton M. Korsakov 2009.
E-mail:        alexab@ailab.ru, anton_korsakov@mail.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAResizeH
#define UBAResizeH
#include "../../UBAbstract.h"

namespace RDK {

// Базовый класс масштабирования изображения
class UBAResize: public UBAbstract
{
protected: // Параметры
// Новый размер
int NewWidth,NewHeight;

protected: // Временные переменные
UBitmap Buffer;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAResize(void);
virtual ~UBAResize(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// Новый размер
int GetNewWidth(void) const;
int GetNewHeight(void) const;
bool SetNewWidth(int value);
bool SetNewHeight(int value);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
virtual bool PLACalculate(UBitmap **input, UBitmap **output, int num_inputs=1, int num_outputs=1);
virtual bool BCalculate(UBitmap &input, UBitmap &output)=0;
bool BCalculate(UBitmap &input, int width, int height);
bool BCalculate(UBitmap &input, UBitmap &output, int width, int height);
// ---------------------

// ---------------------
// Операторы
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, int width, int height);
bool operator () (UBitmap &input, UBitmap &output, int width, int height);
// ---------------------
};

// Изменяет размер изображения по четырем угловым точкам
class UBAResizeEdges: public UBAResize
{
public: // Методы
// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBAResizeEdges* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------
};

//extern UBAResizeEdges UBResizeEdges;
}
//---------------------------------------------------------------------------
#endif
