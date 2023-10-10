/* ***********************************************************

*********************************************************** */

#ifndef TCaptureImageSequenceH
#define TCaptureImageSequenceH

#include "TCapture.h"

namespace RDK {
using namespace RDK;

class RDK_LIB_TYPE TCaptureImageSequence: public TCapture
{
public: // Параметры
/// Путь до папки с изображениями
ULProperty<std::string, TCaptureImageSequence> Path;

/// Признак, требующий рассматривать путь как относительный от папки с конфигурацией
ULProperty<bool, TCaptureImageSequence> IsPathRelativeFromConfig;

/// Флаг зацикливания воспроизведения
ULProperty<bool, TCaptureImageSequence> RepeatFlag;

/// Интервал между считыванием изображений (мс)
ULProperty<int, TCaptureImageSequence> CaptureDelay;

public: // Состояния
/// Общее число изображений в папке
ULProperty<int, TCaptureImageSequence, ptPubState> NumImages;

/// Индекс текущего изображения
ULProperty<int, TCaptureImageSequence, ptPubState> CurrentImageIndex;

public: // Входы и выходы
/// Индекс текущего изображения
UPropertyOutputData<std::string, TCaptureImageSequence, ptPubState> CurrentImageFileName;

protected: // Временные переменные
unsigned long long LastImageTime;

/// Массив имен файлов изображений
std::vector<std::string> Images;

/// Скорректированный путь
std::string ActualPath;

// --------------------------
public: 	// Методы
// --------------------------
/// Конструктор
TCaptureImageSequence(void);

/// Деструктор
virtual ~TCaptureImageSequence(void);

// --------------------------
// Методы управления параметрами
// --------------------------
/// Путь до папки с изображениями
bool SetPath(const std::string &value);

/// Признак, требующий рассматривать путь как относительный от папки с конфигурацией
bool SetIsPathRelativeFromConfig(const bool &value);

/// Флаг зацикливания воспроизведения
bool SetRepeatFlag(const bool &value);

/// Интервал между считыванием изображений (мс)
bool SetCaptureDelay(const int &value);
// --------------------------

// --------------------------
protected:	// Скрытые методы управления счетом
// --------------------------
/// Выделяет память для новой чистой копии объекта этого класса
virtual TCaptureImageSequence* New(void);

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

/// Вычисляет актуальный путь
void CalcActualPath(const std::string &path, bool is_relative, std::string &result);
// --------------------------

};
}
#endif
