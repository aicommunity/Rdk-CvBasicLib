/* ***********************************************************
@Copyright Alexsandr Nikolskiy, 2011.
E-mail:        alexxxniko@gmail.com
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBShowRectH
#define UBShowRectH

#include "UBAShowObjects.h"

namespace RDK {

// Класс отображения объектов-прямоугольнико
class RDK_LIB_TYPE UBShowRect: public UBAShowObjects
{
protected: // Коммуникационные данные
/// Указатель на источник данных в виде матриц
UPropertyInputData<MDMatrix<double>, UBShowRect> MatrixZones;

/// Указатель на источник данных в виде вектора UBRect
UPropertyInputData<std::vector<UBRect>, UBShowRect> RectZones;

/// Указатель на флаги необходимости отображать данные
UPropertyInputData<MDMatrix<int>, UBShowRect> ShowFlags;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBShowRect(void);
virtual ~UBShowRect(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UBShowRect* New(void);
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
