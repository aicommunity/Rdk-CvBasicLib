#ifndef RDK_UCLASSIFIERRESSAVER_H
#define RDK_UCLASSIFIERRESSAVER_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
/// Компонент для сохранения результатов классификации

class RDK_LIB_TYPE UClassifierResSaver: virtual public RDK::UNet
{
protected: // Параметры


/// Папка, в которую сохраняются результаты классификации.
/// Полный путь: {ProjectPath}/Result/{SaveDirectory}
ULProperty<std::string, UClassifierResSaver, ptPubParameter> SaveDirectory;

/// Перезаписывать ли SaveDirectory при повторном запуске (папка будет очищена)
/// если нет - к SaveDirectory параметру добавиться некоторый индекс { SaveDirectory_id }
ULProperty<bool, UClassifierResSaver, ptPubParameter> OverwriteSaveDirectory;

/// Названия классов. В случае наличие имени у класса, при сохранении создается папка с "именем"
/// В противном случае с номеров класса
UPropertyInputData<std::map<int, std::string>, UClassifierResSaver, ptPubParameter> ObjectsName;

protected: // Входы и выходы

/// Входное изображение
/// Игнорируется, если подключен векторный вход InputImages
UPropertyInputData<UBitmap, UClassifierResSaver, ptPubInput> InputImage;

/// Название входного изображения
/// Если подключен, то папка images не будет создаваться
UPropertyInputData<UBitmap, UClassifierResSaver, ptPubInput> ImageName;




/// Массив входных изображений
UPropertyInputData<std::vector<UBitmap>, UClassifierResSaver, ptPubInput> InputImages;

/// Входная матрица с классами объектов
UPropertyInputData<MDMatrix<int>,UClassifierResSaver, ptPubInput> InputClasses;

/// Входная матрица. Количество столбцов по числу объектов, количество строк в столбце по числу классов
/// Каждое значение - уверенность класса
UPropertyInputData<MDMatrix<double>, UClassifierResSaver, ptPubInput> InputConfidences;

protected: // Переменные состояния


ULProperty<bool, UClassifierResSaver, ptPubState> CalculateFlag;

std::string OldSaveDirectory;

protected: // Временные переменные

UBitmap ProcessedBmp;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UClassifierResSaver(void);
virtual ~UClassifierResSaver(void);
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
// Выделяет память для новой чистой копии объекта этого класса
virtual UClassifierResSaver* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------

virtual bool ACalculate(void);

bool SaveImage(UBitmap& img, int class_id, MDMatrix<double>& confidences);
};

}
#endif



