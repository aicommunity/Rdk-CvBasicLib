/* ***********************************************************
@Copyright Aleksandr Bakhshiev, 2012.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBStatisticH
#define UBStatisticH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// Базовый класс сбора статистики в виде изображений
class RDK_LIB_TYPE UBStatistic: public UNet
{
protected: // Параметры
/// Путь для сохранения статистики
UProperty<std::string,UBStatistic> SavePath;

/// Префикс имен для статистики
UProperty<std::string,UBStatistic> PrefixName;

/// Флаг необходимости создавать подкаталог дата/время каждый раз после Reset
UProperty<bool,UBStatistic> SubFolderAfterResetFlag;

/// Флаг необходимости переворачивать изображение при записи в лог
UProperty<bool,UBStatistic> ReflectionXFlag;

/// Флаг способа размещения данных в логе
/// 0 - в заданной папке с различением индекса входа по суффиксу файла.
/// 1 - в подпапках с именем индекса входа в заданной папке.
UProperty<int,UBStatistic> InputIndexMode;

// Флаг необходимости добавлять дату и время к имени файла
UProperty<bool,UBStatistic> TimeToFileNameFlag;

// Флаг необходимости добавлять порядковый номер файла к имени
UProperty<bool,UBStatistic> OrderIndexToFileNameFlag;

// Число шагов расчета которые следует пропустить перед началом регистрации
UProperty<int,UBStatistic> NumSkipSteps;

public:
/// Формат файла
/// 0 - bmp
/// 1 - jpeg
ULProperty<int,UBStatistic> FileFormat;

/// Суффикс имени файла
/// 0 - номер входа
/// 1 - имя подключенного выхода
ULProperty<int,UBStatistic> FileNameSuffix;

/// Флаг обрезки имени модели от полного имени формируемого файла
ULProperty<bool,UBStatistic> ExcludeModelFileName;

/// Флаг режима ручного сохранения кадров. Сохраняет текущий набор кадров при задании
/// состояния "ManualStatisticSwitch" в true
ULProperty<bool,UBStatistic> UseManualStatistic;

/// Флаг режима ручного сохранения кадров. Сохраняет текущий набор кадров при задании
/// состояния "ManualStatisticSwitch" в true
ULProperty<bool,UBStatistic,ptPubState> ManualStatisticSwitch;

protected: // Данные
UPropertyInputCData<UBitmap, UBStatistic> Input;

protected: // Временные переменные
/// Флаг, выставляемый, если был проведен Reset.
bool ResetFlag;

/// Текущий путь для записи статистики
std::string CurrentPath;

/// Текущее имя файла
std::string CurrentFileName;

/// Дополнительный постфикс для имени файла, когда на одну временную метку
/// приходится несколько сохранений лога
int CurrentFileNameNumber;

UBitmap TempBitmap;
UBitmap Rgb24TempBitmap;

time_t OldTimeStamp;

/// Индекс текущего номера файла
int CurrentFileIndex;

int CurrentStep;

std::vector<uint8_t> jpeg_buf;
std::vector<uint8_t> temp_buf;


public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBStatistic(void);
virtual ~UBStatistic(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
bool SetSavePath(const std::string &value);
bool SetPrefixName(const std::string &value);
bool SetSubFolderAfterResetFlag(bool value);
bool SetReflectionXFlag(bool value);
bool SetInputIndexMode(int value);
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

// --------------------------
// Скрытые методы управления счетом фильтров сплиттинга
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFSDefault(void)=0;

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFSBuild(void)=0;

/// Сброс процесса счета без потери настроек
virtual bool AFSReset(void)=0;

/// Выполняет расчет этого объекта
virtual bool AFSCalculate(void)=0;
// --------------------------
};

// Простой конечный класс сбора статистики в виде изображений
class RDK_LIB_TYPE UBStatisticSimple: public RDK::UBStatistic
{
protected: // Параметры
/// Интервал времени в миллисекундах, через который сохраняются кадры
/// Если 0, то интервал не учитывается
UProperty<int,UBStatisticSimple> TimeInterval;

/// Режим записи
/// 0 - по таймеру
/// 1 - по сигналу (с одновременным учетом таймера)
UProperty<int,UBStatisticSimple> Mode;

/// Сигнал разрешения записи
/// Автоматически сбрасывается при выполнении Calculate
UProperty<bool,UBStatisticSimple> WriteSignal;

protected: // Переменные состояния
unsigned long long LastSaveTime;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBStatisticSimple(void);
virtual ~UBStatisticSimple(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
bool SetTimeInterval(int value);
bool SetMode(int value);
bool SetWriteSignal(bool value);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBStatisticSimple* New(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров сплиттинга
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFSDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFSBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFSReset(void);

/// Выполняет расчет этого объекта
virtual bool AFSCalculate(void);

/// Осуществляет сохранение текущих данных
virtual bool Save(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif
