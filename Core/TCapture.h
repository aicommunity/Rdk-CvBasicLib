/* ***********************************************************

*********************************************************** */

#ifndef TCaptureH
#define TCaptureH

#include "../../../Rdk/Deploy/Include/rdk.h"

//Состояния
#define RDK_CAPTURE_EMPTY 0
#define RDK_CAPTURE_CREATED 64
#define RDK_CAPTURE_INITIALIZATION 1
#define RDK_CAPTURE_CONNECTED 2
#define RDK_CAPTURE_PAUSED 4
#define RDK_CAPTURE_ACTIVE 8
#define RDK_CAPTURE_DISCONNECTED 16
#define RDK_CAPTURE_RECONNECT 32

namespace RDK {

// Базовый класс захвата данных
class RDK_LIB_TYPE TCapture: public UNet
{
public: // Параметры
/// Желаемый Fps
ULProperty<double, TCapture> DesiredFps;

/// Таймаут на ожидание завершения захвата, мс
ULProperty<int, TCapture> CloseTimeout;

/// Таймаут между переподключениями
ULProperty<int, TCapture> ReconnectTimeout;

/// Таймаут на межкадровый интервал, при превышении которого инициируется состояние обрыва связи с источником
ULProperty<int, TCapture> CaptureTimeout;

/// Режим восстановления после сбоя захвата
/// 0 - не делать ничего
/// 1 - попытаться восстановить захват
/// 2 - вызвать метод останова захвата
ULProperty<int, TCapture> RestartMode;

/// Желаемое разрешение захвата
ULProperty<int, TCapture> DesiredWidth;
ULProperty<int, TCapture> DesiredHeight;

/// Флаг включения выбора желаемого разрешения захвата
ULProperty<bool, TCapture> DesiredResolutionFlag;

public: // Состояния
/// Тип видеозахвата
ULProperty<int, TCapture, ptPubState> CameraType;

public: // Выходы
UPropertyOutputData<UBitmap,TCapture> OutputImage;
UPropertyOutputData<unsigned long long, TCapture> CaptureTime;
public: 	// Флаги
/// Флаг запуска захвата
ULProperty<bool, TCapture> EnableCapture;

/// Флаг приостановки захвата
ULProperty<bool, TCapture> Paused;

/// Флаг инверсии по оси X
ULProperty<bool, TCapture> FlipX;

/// Флаг инверсии по оси Y
ULProperty<bool, TCapture> FlipY;

/// Флаг проверки актуальности данных
ULProperty<bool, TCapture> RelevData;

/// флаг обновления данных
bool data_changed;

/// Установка угла поворота
ULProperty<double, TCapture> RotationAngle;

/// Поворот изображения на фиксированный угол
/// 0 - нет поворота
/// 1 - 90
/// 2 - 180
/// 3 - 270
ULProperty<int, TCapture> FixedRotation;


public: // Данные
/// Число кадров в последовательности (0 - для онлайн-источников)
ULProperty<unsigned long long, TCapture, ptPubState> NumFrames;

/// Текущий Fps захвата
ULProperty<double, TCapture, ptPubState> CaptureFps;

/// Текущий реальный Fps
ULProperty<double, TCapture, ptPubState> RealFps;

/// Текущее состояние захвата
ULProperty<int, TCapture, ptPubState> CaptureState;

/// Номер текущего кадра
ULProperty<unsigned long long, TCapture, ptPubState> FramePosition;

/// Время текущего кадра, с
/// (обычно вычисляется из Position и Fps для offline источников)
ULProperty<double, TCapture, ptPubState> FrameTime;


public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
TCapture(void);
virtual ~TCapture(void);
// --------------------------

// --------------------------
// Методы управления захватом
// --------------------------
/// Запуск захвата
bool StartCapture(void);
virtual bool AStartCapture(void)=0;

/// Останов захвата
bool StopCapture(void);
virtual bool AStopCapture(void)=0;

/// Пауза захвата
bool PauseCapture(void);
virtual bool APauseCapture(void);
// --------------------------

public:	// Методы управления параметрами
/// Установка типа источника захвата
bool SetCameraType(const int &value);
virtual bool ASetCameraType(const int &value);

/// Установка желаемой частоты кадров
bool SetDesiredFps(const double &value);
virtual bool ASetDesiredFps(const double &value);

/// Таймаут на ожидание завершения захвата, мс
bool SetCloseTimeout(const int &value);
virtual bool ASetCloseTimeout(const double &value);

/// Таймаут между переподключениями
bool SetReconnectTimeout(const int &value);
virtual bool ASetReconnectTimeout(const double &value);

bool SetCaptureTimeout(const int &value);
virtual bool ASetCaptureTimeout(const double &value);

/// Режим восстановления после сбоя захвата
/// 0 - не делать ничего
/// 1 - попытаться восстановить захват
/// 2 - вызвать метод останова захвата
bool SetRestartMode(const int &value);
virtual bool ASetRestartMode(const double &value);

/// Желаемое разрешение захвата
bool SetDesiredWidth(const int &value);
virtual bool ASetDesiredWidth(const double &value);
bool SetDesiredHeight(const int &value);
virtual bool ASetDesiredHeight(const double &value);

/// Флаг включения выбора желаемого разрешения захвата
bool SetDesiredResolutionFlag(const bool &value);
virtual bool ASetDesiredResolutionFlag(const bool &value);

/// Установка флага запуска захвата
bool SetEnableCapture(const bool &value);
virtual bool ASetEnableCapture(const bool &value)=0;

/// Установка Флага приостановки захвата
bool SetPaused(const bool &value);
virtual bool ASetPaused(const bool &value);

/// Установка инверсии по оси X
bool SetFlipX(const bool &value);
virtual bool ASetFlipX(const bool &value);

/// Установка инверсии по оси Y
bool SetFlipY(const bool &value);
virtual bool ASetFlipY(const bool &value);
/// Установка проверки актуальности данных
bool SetRelevData(const bool &value);

/// Установка угла поворота
bool SetRotationAngle(const double &value);
virtual bool ASetRotationAngle(const double &value);

/// Поворот изображения на фиксированный угол
/// 0 - нет поворота
/// 1 - 90
/// 2 - 180
/// 3 - 270
bool SetFixedRotation(const int &value);
virtual bool ASetFixedRotation(const int &value);

int GetCaptureState(void);

/// Возвращает общее число кадров в источнике
virtual unsigned long long GetNumFrames(void) const;

/// Возвращает индекс текущего кадра в источнике
virtual unsigned long long GetFramePosition(void) const;

/// Устанавливает имя текущего кадра в источнике
virtual void SetFramePosition(unsigned long long value);

/// Возвращает общее число секунд в источнике
virtual double GetTimeDuration(void) const;

/// Возвращает текущую секунду в источнике
virtual double GetTimePosition(void) const;

/// Устанавливает текущую секунду в источнике
virtual void SetTimePosition(double value);

/// Перемещает позицию в источнике на value кадров
virtual void ChangeRelativeFramePosition(long long value);

/// Перемещает позицию в источнике на value секунд
virtual void ChangeRelativeTimePosition(double value);

protected:	// Скрытые методы
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
protected:	// Скрытые методы управления счетом дочерних классов
// --------------------------
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault1(void)=0;

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild1(void)=0;

/// Сброс процесса счета без потери настроек
virtual bool AReset1(void)=0;

/// Выполняет расчет этого объекта
virtual bool ACalculate1(void)=0;
// --------------------------
};
}
#endif
