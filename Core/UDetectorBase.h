#ifndef RDK_UDETECTORBASE_H
#define RDK_UDETECTORBASE_H
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {
/// Базовый детектор. Имеет ACalculate с необходимой обработкой.
/// Потомки обязаны определить метод Detect. Метод возвращает bool в зависимости от успешности исполнения
/// Потомки не могут переопределять ACalculate. Все дополнительные действия стоит осуществлять в ABeforeCalculate() и AAfterCalculate()
class RDK_LIB_TYPE UDetectorBase: virtual public RDK::UNet
{
protected: // Параметры

///Порог уверенности
ULProperty<double,UDetectorBase, ptPubParameter> ConfidenceThreshold;

///Порог используемый в подавлении не-максимумов
ULProperty<double,UDetectorBase, ptPubParameter> NMSthreshold;

///Отвечает за домножение полученных координат на ширину и высоту
//ULProperty<bool,UDetectorBase, ptPubParameter | ptOutput> UseRelativeCoords;

///Рисовать или не рисовать отладочные изображения
ULProperty<bool,UDetectorBase, ptPubParameter> UseDebugImage;

protected: // Входы и выходы

/// Входное изображение
UPropertyInputData<UBitmap, UDetectorBase, ptPubInput | ptPubOutput> InputImage;

/// Выходное отладочное изображение
UPropertyOutputData<UBitmap, UDetectorBase> DebugImage;

/// Выходная матрица. Количество строк по числу объектов
/// Формат матрицы:
/// Высота по количеству объектов
/// Ширина 4+1+1=Left; Top; Right; Bottom; ClassReliability; ClassNumber
UPropertyOutputData<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputObjects;

/// Выходная матрица только прямоугольников с экранными координатами
UPropertyOutputData<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputRects;

/// Выходная матрица идентификаторов классов
UPropertyOutputData<MDMatrix<int>, UDetectorBase, ptOutput | ptPubState> OutputClasses;

/// Выходная матрица оценок достоверностей
UPropertyOutputData<MDMatrix<double>, UDetectorBase, ptOutput | ptPubState> OutputReliability;


protected: // Временные переменные
UGraphics Graph;
UBitmap ProcessedBmp;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UDetectorBase(void);
virtual ~UDetectorBase(void);
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

virtual bool Detect(UBitmap &bmp, MDMatrix<double> &output_rects, MDMatrix<int> &output_classes, MDMatrix<double> &reliabilities)
{ return true; };

protected:
// --------------------------


};



}

#endif



