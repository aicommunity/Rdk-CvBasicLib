/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBASOURCE_MULTI_FILE_H
#define UBASOURCE_MULTI_FILE_H

#include "../../../Rdk/Deploy/Include/rdk.h"
#include "UBASourceFile.h"

namespace RDK {

/// Простой класс-источник изображений
class RDK_LIB_TYPE UBASourceMultiFile: public UNet
{
public:
/// Список файлов изображений
ULProperty<std::vector<std::string>, UBASourceMultiFile> FileNames;

protected: // Временные переменные
bool LoadFlag;

std::vector<bool> LoadFlags;

bool BuildFlag;

std::vector<UPropertyOutputData<UBitmap,UBASourceMultiFile>* > DynamicOutputs;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBASourceMultiFile(void);
virtual ~UBASourceMultiFile(void);
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
bool SetFileNames(const std::vector<std::string> &value);
// --------------------------

// --------------------------
// Методы управления данными
// --------------------------
/// Проверяет были ли загружены изображения
bool IsLoad(void) const;
// --------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
/// Выделяет память для новой чистой копии объекта этого класса
virtual UBASourceMultiFile* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

virtual bool ABuild(void);

/// Сброс процесса счета.
virtual bool AReset(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------
};

}
#endif



