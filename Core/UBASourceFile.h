/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBASOURCEFile_H
#define UBASOURCEFile_H

#include "../../../Rdk/Deploy/Include/rdk.h"
#include "UBASource.h"

namespace RDK {

/// Простой класс-источник изображений
class RDK_LIB_TYPE UBASourceFile: public UBASource
{
public: // Параметры
/// Имя файла
ULProperty<std::string, UBASourceFile> FileName;

protected: // Временные переменные
/// Признак того, что изображение уже загружено
bool LoadFlag;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBASourceFile(void);
virtual ~UBASourceFile(void);
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
bool SetFileName(const std::string &value);
// --------------------------

// --------------------------
// Методы управления данными
// --------------------------
/// Возвращает признак того, что изображение уже загружено
bool IsLoad(void) const;
// --------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
/// Выделяет память для новой чистой копии объекта этого класса
virtual UBASourceFile* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

/// Сброс процесса счета.
virtual bool AReset(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------
};

}
#endif



