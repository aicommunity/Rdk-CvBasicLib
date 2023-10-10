/* ***********************************************************

*********************************************************** */

#ifndef TCaptureCameraH
#define TCaptureCameraH

#include "TCapture.h"

namespace RDK {
using namespace RDK;

class RDK_LIB_TYPE TCaptureCamera: public TCapture
{
// --------------------------
public: 	// Методы
// --------------------------
/// Конструктор
TCaptureCamera(void);

/// Деструктор
virtual ~TCaptureCamera(void);

// --------------------------
protected:	// Скрытые методы управления счетом
// --------------------------
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault1(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild1(void);

/// Сброс процесса счета без потери настроек
virtual bool AReset1(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate1(void);

/// Установка флага запуска захвата
virtual bool ASetEnableCapture(const bool &value);

/// Запуск захвата
virtual bool AStartCapture(void);

/// Останов захвата
virtual bool AStopCapture(void);
// --------------------------
// --------------------------
protected:	// Скрытые методы управления счетом дочерних классов
// --------------------------
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault2(void)=0;

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild2(void)=0;

/// Сброс процесса счета без потери настроек
virtual bool AReset2(void)=0;

/// Выполняет расчет этого объекта
virtual bool ACalculate2(void)=0;

/// Установка флага запуска захвата
virtual bool ASetEnableCapture1(const bool &value)=0;

/// Запуск захвата
virtual bool AStartCapture1(void)=0;

/// Останов захвата
virtual bool AStopCapture1(void)=0;
// --------------------------
};
}
#endif