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

///  - 
class RDK_LIB_TYPE UBASourceMultiFile: public UNet
{
public:
/// File names
UProperty<std::vector<std::string>, UBASourceMultiFile, ptPubParameter> FileNames;

protected: //  
bool LoadFlag;

std::vector<bool> LoadFlags;

bool BuildFlag;

std::vector<UProperty<UBitmap,UBASourceMultiFile, ptPubOutput>* > DynamicOutputs;

public: // 
// --------------------------
//   
// --------------------------
UBASourceMultiFile(void);
virtual ~UBASourceMultiFile(void);
// --------------------------

// --------------------------
//   
// --------------------------
bool SetFileNames(const std::vector<std::string> &value);
// --------------------------

// --------------------------
//   
// --------------------------
///     
bool IsLoad(void) const;
// --------------------------

// --------------------------
//    
// --------------------------
///         
virtual UBASourceMultiFile* New(void);
// --------------------------

// --------------------------
//    
// --------------------------
protected:
///        
virtual bool ADefault(void);

virtual bool ABuild(void);

///   .
virtual bool AReset(void);

///    
virtual bool ACalculate(void);
// --------------------------
};

}
#endif



