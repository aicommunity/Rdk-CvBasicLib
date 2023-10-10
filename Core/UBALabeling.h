/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBALabelingH
#define UBALabelingH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// Базовый класс построения разнострого кадра
class RDK_LIB_TYPE UBALabeling: public UNet
{
protected: // Входные и выходные данные
UPropertyInputData<UBitmap, UBALabeling> Input;

/// Выходное изображение
UPropertyOutputData<MDMatrix<double>, UBALabeling, ptPubOutput | ptState> Zones;


public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBALabeling(void);
virtual ~UBALabeling(void);
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
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFBgDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBgBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFBgReset(void);

/// Выполняет расчет этого объекта
virtual bool AFBgCalculate(void);
// --------------------------
};

/// Вычисляет простой разностный кадр
class RDK_LIB_TYPE UBALabelingSimple: public UBALabeling
{
protected: // Параметры

protected: // Временные переменные

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBALabelingSimple(void);
virtual ~UBALabelingSimple(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBALabelingSimple* New(void);

void LCalculate(UBitmap &bmp, MDMatrix<double> &output);


// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFBgDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBgBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFBgReset(void);

/// Выполняет расчет этого объекта
virtual bool AFBgCalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif

