#ifndef RDK_UDETRESSAVERPVOC_H
#define RDK_UDETRESSAVERPVOC_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
/// Компонент для сохранения результатов классификации

class RDK_LIB_TYPE UDetResSaverPVOC: virtual public RDK::UNet
{
protected: // Параметры

/// Папка, в которую сохраняются результаты детекции.
/// Полный путь: {ProjectPath}/Result/{SaveDirectory}
/// внутри {SaveDirectory} будут созданы две папки images и annotations
ULProperty<std::string, UDetResSaverPVOC, ptPubParameter> SaveDirectory;

/// Перезаписывать ли SaveDirectory при повторном запуске (папка будет очищена)
/// если нет - к SaveDirectory параметру добавиться некоторый индекс { SaveDirectory_id }
ULProperty<bool, UDetResSaverPVOC, ptPubParameter> OverwriteSaveDirectory;

/// Названия классов. В случае наличие имени у класса, при сохранении создается папка с "именем"
/// В противном случае с номеров класса
UPropertyInputData<std::map<int, std::string>, UDetResSaverPVOC, ptPubParameter> ObjectsName;

protected: // Входы и выходы

/// Входная матрица. Количество строк по числу объектов
/// Формат матрицы:
/// Высота по количеству объектов
/// Ширина 4+1+1=Left; Top; Right; Bottom; ClassReliability; ClassNumber
UPropertyInputData<MDMatrix<double>, UDetResSaverPVOC, ptPubInput > InputObjects;

/// Входное изображение
UPropertyInputData<UBitmap, UDetResSaverPVOC, ptPubInput> InputImage;

/// Название входного изображения
/// Если подключен, то папка images не будет создаваться
/// Также из этого имени формируется имена разметок xml в папке annotations
UPropertyInputData<std::string, UDetResSaverPVOC, ptPubInput> ImageName;

protected: // Переменные состояния

ULProperty<bool, UDetResSaverPVOC, ptPubState> CalculateFlag;

std::string OldSaveDirectory;

protected: // Временные переменные

UBitmap ProcessedBmp;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UDetResSaverPVOC(void);
virtual ~UDetResSaverPVOC(void);
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
virtual UDetResSaverPVOC* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
virtual bool ACalculate(void);

bool SaveImage();
};

}
#endif



