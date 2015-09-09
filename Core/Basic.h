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

//#include "../../../Engine/ULibrary.h"
#include "../../../Rdk/Deploy/Include/rdk.h"
#include "UBAColorConvert.h"
#include "UBAModel.h"
#include "UBAReceiver.h"
#include "UBPipeline.h"
#include "UBASource.h"
#include "UBAResize.h"
#include "UBARotate.h"
#include "UBAFlipImage.h"
#include "UBACrop.h"
#include "UBAReduce.h"

namespace RDK{

class RDK_LIB_TYPE Basic : public ULibrary
{
public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
Basic(void);
// --------------------------

// --------------------------
// ������ ����������� �����������
// --------------------------
// ��������� ������ ClassSamples �������� ������������ �������� � �� �������.
// �� ��������� ��������������� ������� ������� � ������ ������.
virtual void CreateClassSamples(UStorage *storage);
// --------------------------
};

extern RDK_LIB_TYPE Basic BasicLibrary;

}


#endif

