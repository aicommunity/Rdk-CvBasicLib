/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAColorConvertH
#define UBAColorConvertH
#include "../../UBAbstract.h"

namespace RDK {

// Базовый класс масштабирования изображения
class UBAColorConvert: public UBAbstract
{
protected: // Параметры
// Новый режим изображения
UBMColorModel NewColorModel;

protected: // Временные переменные
UBitmap Buffer;   //?

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAColorConvert(void);
virtual ~UBAColorConvert(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// Новый режим изображения
UBMColorModel GetNewColorModel(void) const;
bool SetNewColorModel(UBMColorModel value);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
UBAColorConvert* New(void);
virtual bool PLACalculate(UBitmap **input, UBitmap **output, int num_inputs=1, int num_outputs=1);
virtual bool BCalculate(UBitmap &input, UBitmap &output);
bool BCalculate(UBitmap &input, UBMColorModel color_model);
bool BCalculate(UBitmap &input, UBitmap &output, UBMColorModel color_model);
// ---------------------

// ---------------------
// Операторы
// ---------------------
bool operator () (UBitmap &input, UBitmap &output);
bool operator () (UBitmap &input, UBMColorModel color_model);
bool operator () (UBitmap &input, UBitmap &output, UBMColorModel color_model);  //?
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFDefault(void);
// --------------------------
};
}
//---------------------------------------------------------------------------
#endif
