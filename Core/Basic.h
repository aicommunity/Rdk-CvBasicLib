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

#include "../../../Rdk/Deploy/Include/rdk.h"
#include "UBAColorConvert.h"
#include "UBAModel.h"
#include "UBAReceiver.h"
#include "UBPipeline.h"
#include "UBASource.h"
#include "UBASourceFile.h"
#include "UBASourceMultiFile.h"
#include "UBAResize.h"
#include "UBARotate.h"
#include "UBAFlipImage.h"
#include "UBACrop.h"
#include "UBAReduce.h"

#include "UBMathOperator.h"
#include "UMDMatrixMux.h"
#include "UMatrixMath.h"

#include "UBADifferenceFrame.h"
#include "UBABackground.h"
#include "UBABinarization.h"
#include "UBALooping.h"
#include "UBAMovingDetector.h"
#include "UBAObjectDetector.h"
#include "UBALabeling.h"

#include "UBAGuiSelection.h"
#include "UBAShowObjects.h"
#include "UBShowRect.h"

#include "UBAVideoSimulator.h"
#include "UBADataSimulator.h"
#include "UBABitmapSource.h"
#include "UBARotCameraSimulator.h"

#include "UBStatistic.h"

//#include "UCRPerseptron.h"
//#include "UCRDirectCompare.h"
//#include "UCRDistance.h"
//#include "UCRFusion.h"
//#include "UCRSample.h"
//#include "UCRTeacherPerseptronDL.h"
//#include "UCRTeacher.h"
//#include "UCRTeacherPerseptronBP.h"
//#include "UCRTeacherCVNetworkBP.h"
//#include "UCRConvolutionNetwork.h"
//#include "UCRClassifier.h"
#include "UClassifierBase.h"
#include "UDetectorBase.h"
#include "USegmentatorBase.h"
#include "UClassifierResSaver.h"
#include "UDetResSaverPVOC.h"
#include "UCRPrincipalComponentAnalysis.h"
#include "UCRBarnesHutTSNE.h"


#if defined(__BORLANDC__) || defined(WIN32)
#define RDK_WINAPI
#endif

#include "TCaptureImageSequence.h"

#include "../../../Rdk/Core/Engine/UBasePropCreatorTempl.h"

namespace RDK{

class RDK_LIB_TYPE CvBasicLib : public ULibrary
{
public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
CvBasicLib(void);
// --------------------------

// --------------------------
// Методы заполенения бибилиотеки
// --------------------------
// Заполняет массив ClassSamples готовыми экземплярами образцов и их именами.
// Не требуется предварительная очистка массива и уборка памяти.
virtual void CreateClassSamples(UStorage *storage);
// --------------------------

// Функция, добавляемая в Storage
static bool CvBasicLibCrPropMock(RDK::USerStorageXML* serstorage, RDK::UMockUNet* mock_unet);

// Функция вызывает необходимые фукнции в зависимости от типа (строка) свойства
template <template<typename, typename, unsigned int> class PropType, unsigned int TypeInt>
static void CreateProperty(RDK::USerStorageXML* serstorage, RDK::UMockUNet* mock_unet, unsigned int ptype)
{
    std::string type = serstorage->GetNodeAttribute("Type");

    // vectors
    if(type == "std::vector")
    {
        int size=serstorage->GetNumNodes();

        // если вектор пуст берем тип - elemType
        // если есть элементы берем тип элементов
        std::string type;
        if(size == 0)
        {
            type = serstorage->GetNodeAttribute("elemType");
        }
        else
        {
            serstorage->SelectNode("elem",size-1);
            type = serstorage->GetNodeAttribute("Type");
            serstorage->SelectUp();
        }

        // std::vector<UBVSObject>
        if(type == "UBVSObject")
        {
            CreatorProperty<PropType, TypeInt, std::vector<UBVSObject> >::CreatePropertyByType(serstorage, mock_unet, ptype);
            return;
        }
    }
}
};

extern RDK_LIB_TYPE CvBasicLib CvBasicLibrary;

}


#endif

