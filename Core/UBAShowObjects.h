/* ***********************************************************
@Copyright Aleksandr Bakhshiev, 2011.
E-mail:        palexab@gmail.com
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAShowObjectsH
#define UBAShowObjectsH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// Базовый класс отображения объектов
class RDK_LIB_TYPE UBAShowObjects: public UNet
{
protected: // Параметры
/// Цвет рамки
UProperty<RDK::UColorT,UBAShowObjects, ptPubParameter> PenColor;

/// Толщина рамки
UProperty<int,UBAShowObjects, ptPubParameter> PenWidth;

/// Флаг разрешения отрисовки
UProperty<bool,UBAShowObjects, ptPubParameter> EnableShowFlag;

public: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBAShowObjects> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBAShowObjects> Output;

/// Массив цветов отрисовки объектов
/// Объекты для которых цвет не опеределен используют цвет по умолчанию
UPropertyInputData<std::vector<UColorT>, UBAShowObjects, ptPubInput | ptParameter> ObjectsColor;

/// Массив имен объектов
UPropertyInputData<std::vector<std::string>, UBAShowObjects, ptPubInput | ptParameter> ObjectsName;

/// Вектор идентификаторов объектов
UPropertyInputData<MDMatrix<int>, UBAShowObjects, ptPubInput | ptParameter> ObjectsId;


protected: // Данные
UBitmap Canvas;
UGraphics Graphics;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAShowObjects(void);
virtual ~UBAShowObjects(void);
// ---------------------

// --------------------------
// Методы управления параметрами
// --------------------------
bool SetActivity(const bool &activity);
// --------------------------

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

// Класс отображения объектов-точек
class RDK_LIB_TYPE UBAShowObjectsSimple: public RDK::UBAShowObjects
{
protected: // Коммуникационные данные
/// Указатель на источник данных
UPropertyInputData<std::vector<UBPoint>, UBAShowObjectsSimple> Zones;

/// Указатель на источник данных
UPropertyInputData<MDMatrix<double>, UBAShowObjectsSimple> MatrixPoints;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAShowObjectsSimple(void);
virtual ~UBAShowObjectsSimple(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBAShowObjectsSimple* New(void);
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
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif
