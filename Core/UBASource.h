/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBASOURCE_H
#define UBASOURCE_H

#include "../../../Rdk/Deploy/Include/rdk.h"
#include "UEPtr.h"
#include "ModernSmartPointers.h"
#include <memory>
#include <mutex>
#include <filesystem>

namespace RDK {

/// ������� �����-�������� �����������
class RDK_LIB_TYPE UBASource: public UNet
{
public:
UPropertyOutputData<UBitmap, UBASource> Output;
UPropertyInputData<UBitmap, UBASource> Input;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UBASource(void);
virtual ~UBASource(void);

// Modern C++20 methods with move semantics for images
// Thread-safe image operations
void SetImageSafe(const UBitmap& image);
UBitmap GetImageSafe(void) const;

// Modern move semantics for large image data
UBASource(UBASource&& other) noexcept;
UBASource& operator=(UBASource&& other) noexcept;

// Modern smart pointer factory
static std::shared_ptr<UBASource> Create(void);

// Modern file operations with std::filesystem
bool LoadImageFromFile(const std::filesystem::path& filepath);
bool SaveImageToFile(const std::filesystem::path& filepath) const;

// --------------------------

protected:
// --------------------------
// ������ ���������� �������
// --------------------------
/// ��������������� ������ �������� �����������
bool SetOutputData(int index, const UBitmap &bitmap);
// --------------------------

// --------------------------
// ��������� ������ ���������� ��������
// --------------------------
/// �������� ������ ��� ����� ������ ����� ������� ����� ������
virtual UBASource* New(void);
// --------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);

/// ����� �������� �����.
virtual bool AReset(void);

/// ��������� ������ ����� �������
virtual bool ACalculate(void);
// --------------------------
};

}
#endif



