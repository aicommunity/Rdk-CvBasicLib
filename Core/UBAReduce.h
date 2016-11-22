#ifndef UBA_REDUCE_H
#define UBA_REDUCE_H

//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// Базовый класс масштабирования изображения
class RDK_LIB_TYPE UBAReduce: public UNet
{
protected: // Параметры
/// Номер столбца и строки для сохранения
int NumCols, NumRows;

public: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBAReduce> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBAReduce> Output;

protected: // Временные переменные
UBitmap Buffer;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAReduce(void);
virtual ~UBAReduce(void);
// ---------------------

public: // Методы
// ---------------------
// Методы управления параметрами
// ---------------------
/// Номер строки и столбца для удаления
const int& GetNumCols(void) const;
const int& GetNumRows(void) const;
bool SetNumCols(const int &value);
bool SetNumRows(const int &value);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBAReduce* New(void);

// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild(void);

/// Сброс процесса счета.
virtual bool AReset(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------
};
}
//---------------------------------------------------------------------------

#endif
