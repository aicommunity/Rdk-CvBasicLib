#ifndef RDK_USEGMENTATORBASE_H
#define RDK_USEGMENTATORBASE_H
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {
/// Базовый сегментатор.  Имеет ACalculate с необходимой обработкой.
/// Потомки обязаны определить метод Inference. Метод возвращает bool в зависимости от успешности исполнения
/// Потомки не могут переопределять ACalculate. Все дополнительные действия стоит осуществлять в ABeforeCalculate() и AAfterCalculate()
class RDK_LIB_TYPE USegmentatorBase: virtual public RDK::UNet
{
protected: // Входы и выходы
/// Входное изображение
UPropertyInputData<UBitmap, USegmentatorBase> InputImage;

/// Выходное изображение c результирующей маской
UPropertyOutputData<UBitmap, USegmentatorBase> OutputImage;


protected: // Переменные состояния
/// Соответствие классов и цветов
ULProperty<std::vector< UColorT>,USegmentatorBase, ptPubParameter> ClassColors;


protected: // Временные переменные
UBitmap ProcessedBmp;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
USegmentatorBase(void);
virtual ~USegmentatorBase(void);
// --------------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------


// ---------------------
// Методы управления переменными состояния
// ---------------------
// ---------------------

// --------------------------
// Системные методы управления объектом
// --------------------------

// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
virtual bool ACalculate(void);

virtual bool Inference(UBitmap &bmp, UBitmap &mask) { return true; };

protected:
// --------------------------


};



}

#endif



