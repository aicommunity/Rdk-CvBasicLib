/* ***********************************************************
@Copyright Pavel Korban, 2011.
E-mail:        korapaxa@gmail.com

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBACropH
#define UBACropH
#include "../../../Engine/UNet.h"
#include "../../UBitmap.h"

namespace RDK {

/// Класс преобразования цветовых моделей изображения
class RDK_LIB_TYPE UBACrop: public UNet
{
protected: // Параметры

protected: // Входы и выходы
UPropertyInputData<UBitmap, UBACrop> Input;

/// Прямоугольник, описывающий область выходного изображения во входном
/// (применяется, при заданном InputSample
UPropertyInputData<UBRect, UBACrop, ptPubInput | ptState> CropRect;

UPropertyOutputData<UBitmap, UBACrop> Output;

protected: // Временные переменные
UBitmap Buffer;   //?

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBACrop(void);
virtual ~UBACrop(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------

// ---------------------
// Методы счета
// ---------------------
UBACrop* New(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AReset(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------
};
}
//---------------------------------------------------------------------------
#endif
