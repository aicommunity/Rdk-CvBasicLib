/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAROT_CAMERA_SIMULATOR_H
#define UBAROT_CAMERA_SIMULATOR_H

#include "../../../Rdk/Deploy/Include/rdk.h"
#include "UBAVideoSimulator.h"

namespace RDK {


/// Осуществляет симуляцию простых двумерных сцен
class RDK_LIB_TYPE UBARotCameraSimulator: public UBAVideoSimulatorSimple
{
protected: // Параметры

/// Выходное изображение
UPropertyOutputData<UBitmap, UBARotCameraSimulator, ptOutput | ptPubState> ViewOutput;
/// Размер окна обзора, относительно окна сцены
/// Например ViewOutputX = Input / ViewResizeCoef
/// Выходное изображение с рамкой
UPropertyOutputData<UBitmap, UBARotCameraSimulator, ptOutput | ptPubState> BorderOutput;

ULProperty<double, UBARotCameraSimulator, ptPubParameter> ViewResizeCoef;
/// Скорость движения окна обзора по окну сцены
/// В настоящий момент предполагается изменение по линейному закону,
/// Независимо от характера управляющего сигнала
/// (радианы, длина мышцы)
ULProperty<double, UBARotCameraSimulator, ptPubParameter> XSpeedCoef;
ULProperty<double, UBARotCameraSimulator, ptPubParameter> YSpeedCoef;

/// Входной сигнал, управляющий смещением окна обзора по окну сцены
UPropertyInputData<MDMatrix<double>,UBARotCameraSimulator, ptInput | ptPubState> MoveLeftSignal;
UPropertyInputData<MDMatrix<double>,UBARotCameraSimulator, ptInput | ptPubState> MoveRightSignal;
UPropertyInputData<MDMatrix<double>,UBARotCameraSimulator, ptInput | ptPubState> MoveTopSignal;
UPropertyInputData<MDMatrix<double>,UBARotCameraSimulator, ptInput | ptPubState> MoveBottomSignal;


protected: // Данные
/// Размер окна обзора в пикселях
int ViewX, ViewY;
/// Сдвиг окна обзора относительно окна сцены в пикселях
int ViewShiftX, ViewShiftY;
/// Счётчик кадров
int frame_counter;


public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBARotCameraSimulator(void);
virtual ~UBARotCameraSimulator(void);
// ---------------------

// ---------------------
// Методы управления параметрами
// ---------------------
/// Размер окна обзора, относительно окна сцены
/// Например ViewOutputX = Input / ViewResizeCoef
inline double GetViewResizeCoef(void) { return ViewResizeCoef; };
bool SetViewResizeCoef(double const &new_vol);
/// Размер окна обзора в пикселях
inline int GetViewWinX(void) { return ViewX; };
inline int GetViewWinY(void) { return ViewY; };
/// Скорость движения окна обзора по окну сцены
/// В настоящий момент предполагается изменение по линейному закону,
/// Независимо от характера управляющего сигнала
/// (радианы, длина мышцы)
inline double GetXSpeedCoef(void) { return XSpeedCoef; };
inline double GetYSpeedCoef(void) { return YSpeedCoef; };
bool SetXSpeedCoef(double const &new_vol);
bool SetYSpeedCoef(double const &new_vol);
/// Сдвиг окна обзора относительно окна сцены в пикселях
inline int GetViewShiftX(void) { return ViewShiftX; };
inline int GetViewShiftY(void) { return ViewShiftY; };
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBARotCameraSimulator* New(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров симуляторов
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
// --------------------------
};

}

#endif

