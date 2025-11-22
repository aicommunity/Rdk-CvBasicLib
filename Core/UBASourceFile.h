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

///  - 
class RDK_LIB_TYPE UBASourceFile: public UBASource
{
public: // 
///  
UProperty<std::string, UBASourceFile, ptPubParameter> FileName;

protected: //  
///  ,    
bool LoadFlag;

public: // 
// --------------------------
//   
// --------------------------
UBASourceFile(void);
virtual ~UBASourceFile(void);
// --------------------------

// --------------------------
//   
// --------------------------
bool SetFileName(const std::string &value);
// --------------------------

// --------------------------
//   
// --------------------------
///   ,    
bool IsLoad(void) const;
// --------------------------

// --------------------------
//    
// --------------------------
///         
virtual UBASourceFile* New(void);
// --------------------------

// --------------------------
//    
// --------------------------
protected:
///        
virtual bool ADefault(void);

///   .
virtual bool AReset(void);

///    
virtual bool ACalculate(void);
// --------------------------
};

}
#endif



