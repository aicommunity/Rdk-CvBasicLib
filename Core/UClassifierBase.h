#ifndef RDK_UCLASSIFIERBASE_H
#define RDK_UCLASSIFIERBASE_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
/// Базовый классификатор. Имеет ACalculate с необходимой обработкой.
/// Потомки обязаны определить метод classifyBitmap. Метод возвращает bool в зависимости от успешности исполнения
/// Потомки не могут переопределять ACalculate. Все дополнительные действия стоит осуществлять в ABeforeCalculate() и AAfterCalculate()

class RDK_LIB_TYPE UClassifierBase: virtual public RDK::UNet
{
protected: // Параметры

///Порог уверенности: если класс не превышает порога уверенности, то он выставляется в 0, все классы выставляются в 0.
ULProperty<double,UClassifierBase, ptPubParameter> ConfidenceThreshold;

/// Количество классов объектов (какой размер будет у вектора)
ULProperty<int,UClassifierBase, ptPubParameter> NumClasses;

protected: // Входы и выходы

/// Входное изображение
/// Игнорируется, если подключен векторный вход InputImages
UPropertyInputData<UBitmap,UClassifierBase, ptPubInput | ptPubOutput> InputImage;

/// Массив входных изображений
UPropertyInputData<std::vector<UBitmap>, UClassifierBase, ptPubInput | ptPubOutput> InputImages;

/// Выходная матрица с классами объектов
UPropertyOutputData<MDMatrix<int>,UClassifierBase, ptPubOutput> OutputClasses;

/// Выходная матрица. Количество столбцов по числу объектов, количество строк в столбце по числу классов
/// Каждое значение - уверенность класса
UPropertyOutputData<MDMatrix<double>, UClassifierBase, ptPubOutput> OutputConfidences;


protected: // Переменные состояния
/// Время, затраченное на классификацию, секунды
ULProperty<double,UClassifierBase, ptPubState> ClassificationTime;


protected: // Временные переменные
UBitmap ProcessedBmp;


public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UClassifierBase(void);
virtual ~UClassifierBase(void);
// --------------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------
bool SetNumClasses(const int &value);

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

//Классификация одного изображения. Потомки обязаны определить данный метод
virtual bool ClassifyBitmap(UBitmap &bmp, MDVector<double> &output_confidences, double conf_thresh, int &class_id, bool &is_classified)
{ return true; };

protected:
// --------------------------


};





}
#endif



