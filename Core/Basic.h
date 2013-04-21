/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBGRAPHICS_BASIC_H
#define UBGRAPHICS_BASIC_H

#include "../../../Engine/ULibrary.h"
#include "UBAColorConvert.h"
#include "../../UBAModel.h"
#include "../../UBAReceiver.h"
#include "../../UBPipeline.h"
#include "../../UBASource.h"
#include "UBAResize.h"
#include "UBARotate.h"

namespace RDK{

class Basic : public ULibrary
{
public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
Basic(void);
// --------------------------

// --------------------------
// Методы заполенения бибилиотеки
// --------------------------
// Заполняет массив ClassSamples готовыми экземплярами образцов и их именами.
// Не требуется предварительная очистка массива и уборка памяти.
virtual void CreateClassSamples(UStorage *storage);
// --------------------------
};

extern Basic BasicLibrary;

}


#endif

