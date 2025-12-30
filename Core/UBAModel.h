/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBAMODEL_H
#define UBAMODEL_H

//#include "../Engine/UNet.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

class RDK_LIB_TYPE UBAModel: public UNet
{
protected: //   
UProperty<UBitmap,UBAModel, ptPubParameter> Output;

///   
UProperty<int, UBAModel, ptPubState> WorkWidth;
UProperty<int, UBAModel, ptPubState> WorkHeight;

public: // 
// --------------------------
//   
// --------------------------
UBAModel(void);
virtual ~UBAModel(void);
// --------------------------

// --------------------------
//    
// --------------------------
//         
virtual UBAModel* New(void);
// --------------------------

// --------------------------
//    
// --------------------------
protected:
//        
virtual bool ADefault(void);
virtual bool AMDefault(void);

//     
//   
//    Reset()   Ready  true
//    
virtual bool ABuild(void);
virtual bool AMBuild(void);

//   .
virtual bool AReset(void);
virtual bool AMReset(void);

//    
virtual bool ACalculate(void);
virtual bool AMCalculate(void);
// --------------------------
};

}

#endif



