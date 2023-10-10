/* ***********************************************************
@Copyright Alexander V. Bakhshiev.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBMathOperatorH
#define UBMathOperatorH

//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

// Перечень арифметических операций с изображениями
enum { ubmAnd=0, ubmOr=1, ubmXor=2, ubmNot=3, ubmSum=4, ubmSub=5, ubmSubAbs=6 };

// Базовый класс масштабирования изображения
class RDK_LIB_TYPE UBMathOperator: public UNet
{
protected: // Параметры
// Идентификатор оператора
int OperatorId;

protected: // Входы и выходы
/// Аргумент 1
UPropertyInputData<UBitmap, UBMathOperator> Input1;

/// Аргумент 2
UPropertyInputData<UBitmap, UBMathOperator> Input2;

/// Результирующее изображение
UPropertyOutputData<UBitmap, UBMathOperator> Output;

protected: // Временные переменные
UBitmap Buffer;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBMathOperator(void);
virtual ~UBMathOperator(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// Идентификатор оператора
const int& GetOperatorId(void) const;
bool SetOperatorId(const int &value);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBMathOperator* New(void);
// ---------------------


// --------------------------
// Методы, реализующие арифметические операции
// --------------------------
void And(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Or(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Sub(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
void Sum(const UBitmap &in1, const UBitmap &in2, UBitmap &out);
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool ABuild(void);

// Сброс процесса счета без потери настроек
virtual bool AReset(void);

// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif

