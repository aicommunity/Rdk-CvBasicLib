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

/// Класс преобразования цветовых моделей изображения
class UBAColorConvert: public UBAbstract
{
protected: // Параметры
/// Новый режим изображения
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
/// Новый режим изображения
const UBMColorModel& GetNewColorModel(void) const;
bool SetNewColorModel(const UBMColorModel &value);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
UBAColorConvert* New(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFReset(void);

/// Выполняет расчет этого объекта
virtual bool AFCalculate(void);
// --------------------------
};
}
//---------------------------------------------------------------------------
#endif
