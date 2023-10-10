/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBADATA_SIMULATOR_H
#define UBADATA_SIMULATOR_H

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {


/// Базовый класс источник данных
class RDK_LIB_TYPE UBADataSimulator: public UNet
{
protected: // Параметры

protected: // Временные переменные

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBADataSimulator(void);
virtual ~UBADataSimulator(void);
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

/// Класс источник данных о геометрии точек
class RDK_LIB_TYPE UBADataSimulatorSimple: public UBADataSimulator
{
protected: // Параметры
/// Данные точек экрана
std::vector<MVector<double,2> > ScreenPoints;

/// Данные точек плоскости
std::vector<MVector<double,3> > PlanePoints;

/// Данные точек пространства
std::vector<MVector<double,4> > SpacePoints;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBADataSimulatorSimple(void);
virtual ~UBADataSimulatorSimple(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBADataSimulatorSimple* New(void);
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

