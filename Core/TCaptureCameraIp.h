/* ***********************************************************

*********************************************************** */

#ifndef TCaptureCameraIpH
#define TCaptureCameraIpH

#include "TCaptureCamera.h"

namespace RDK {
using namespace RDK;

class RDK_LIB_TYPE TCaptureCameraIp: public TCaptureCamera
{
// --------------------------
public: 	// Параметры
// --------------------------
// Адрес
ULProperty<std::string,TCaptureCameraIp> Address;

// Логин
ULProperty<std::string,TCaptureCameraIp> Login;

// Пароль
ULProperty<std::string,TCaptureCameraIp> Password;
// --------------------------
public: 	// Методы
// --------------------------
/// Конструктор
TCaptureCameraIp(void);

/// Деструктор
virtual ~TCaptureCameraIp(void);
// --------------------------
public:		// Методы управления параметрами
// --------------------------
// Установка адреса
bool SetAddress(const std::string &num);

// Установка имени пользователя
bool SetLogin(const std::string &num);

// Установка пароля
bool SetPassword(const std::string &num);

// --------------------------
protected:	// Скрытые методы управления счетом
// --------------------------
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault2(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild2(void);

/// Сброс процесса счета без потери настроек
virtual bool AReset2(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate2(void);

/// Установка флага запуска захвата
virtual bool ASetEnableCapture1(const bool &value);

/// Запуск захвата
virtual bool AStartCapture1(void);

/// Останов захвата
virtual bool AStopCapture1(void);
// --------------------------
// --------------------------
protected:	// Скрытые методы управления счетом дочерних классов
// --------------------------
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault3(void)=0;

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild3(void)=0;

/// Сброс процесса счета без потери настроек
virtual bool AReset3(void)=0;

/// Выполняет расчет этого объекта
virtual bool ACalculate3(void)=0;

/// Установка флага запуска захвата
virtual bool ASetEnableCapture2(const bool &value)=0;

/// Запуск захвата
virtual bool AStartCapture2(void)=0;

/// Останов захвата
virtual bool AStopCapture2(void)=0;
// --------------------------
};
}
#endif
