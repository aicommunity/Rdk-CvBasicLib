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

#include "../../../Rdk/Deploy/Include/rdk.h"
//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"

namespace RDK {

/// Класс преобразования цветовых моделей изображения
class RDK_LIB_TYPE UBAColorConvert: public UNet
{
protected: // Параметры
/// Новый режим изображения
UProperty<UBMColorModel,UBAColorConvert> NewColorModel;

public: // Входы и выходы
UPropertyInputData<UBitmap, UBAColorConvert> Input;

UPropertyOutputData<UBitmap, UBAColorConvert> Output;

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
// Методы счета
// ---------------------
UBAColorConvert* New(void);
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
