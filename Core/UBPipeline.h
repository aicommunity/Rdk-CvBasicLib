/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBPIPELINE_H
#define UBPIPELINE_H

#include "UBAModel.h"
#include "../../../Rdk/Core/Engine/ModernSmartPointers.h"
#include "../../../Rdk/Core/Engine/ModernContainers.h"
#include "../../../Rdk/Core/System/ModernChrono.h"
#include "../../../Rdk/Core/System/ModernMutex.h"
#include <memory>
#include <memory>
#include <mutex>
#include <filesystem>
#include <vector>

namespace RDK {

// ����� �������� ���������  �����������
class RDK_LIB_TYPE UBPipeline: public UNet
{
protected: // ���� ������

protected: // ��������� ����������

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UBPipeline(void);
virtual ~UBPipeline(void);

// Modern C++20 methods with move semantics for pipeline processing
// Thread-safe pipeline operations
void ProcessImageSafe(const UBitmap& input, UBitmap& output);
void ProcessImageBatchSafe(const std::vector<UBitmap>& inputs, std::vector<UBitmap>& outputs);

// Modern move semantics for large pipeline data
UBPipeline(UBPipeline&& other) noexcept;
UBPipeline& operator=(UBPipeline&& other) noexcept;

// Modern smart pointer factory
static std::shared_ptr<UBPipeline> Create(void);

// Modern file operations with std::filesystem
bool LoadPipelineFromFile(const std::filesystem::path& filepath);
bool SavePipelineToFile(const std::filesystem::path& filepath) const;

// --------------------------

// ---------------------
// ������ ���������� ���������
// ---------------------
// ---------------------

// --------------------------
// ������ ������� � �����������
// --------------------------
// ����� ��������� �� ������������ ������� ������� ����
// � �������� ���������� ������� �������
// ����� ���������� 'true' � ������ ������������
// � 'false' � ������ ������������� ����
virtual bool CheckComponentType(std::shared_ptr<UContainer> comp) const;
// --------------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBPipeline* New(void);
// ---------------------

// --------------------------
// ������� ������ ���������� ������������
// --------------------------
protected:
// ��������� ����������� ���������������� ��������
// ��� ���������� ��������� ���������� � ���� ������
// ����� ����� ������ ������ ���� comp ���
// ������� �������� � ������ ���������
// ����� ���� ������� ��������� �� ��������� ����������
virtual bool AAddComponent(std::shared_ptr<UContainer> comp, std::shared_ptr<UIPointer> pointer=0);

// ��������� ��������������� ���������������� ��������
// ��� �������� ��������� ���������� �� ����� �������
// ����� ����� ������ ������ ���� comp
// ���������� � ������ ���������
virtual bool ADelComponent(std::shared_ptr<UContainer> comp);
// --------------------------

// ---------------------
// ������� ������ �����
// ---------------------
protected:
// ---------------------

};


// ����� ������������� ��������
class RDK_LIB_TYPE UBParallelPipeline: public UBPipeline
{
public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UBParallelPipeline(void);
virtual ~UBParallelPipeline(void);
// --------------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBParallelPipeline* New(void);
// ---------------------

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

// --------------------------
// Modern C++20 methods
// --------------------------

// Modern image processing operations
template<typename T>
void ReserveImageBuffer(std::vector<T>& buffer, size_t width, size_t height);

template<typename T>
void MoveImageBuffer(std::vector<T>& target, std::vector<T>&& source);

// Advanced computer vision algorithms
void OptimizeImageProcessing(const std::vector<double>& parameters);
void CalculateImageFeatures(const std::vector<double>& image_data);
void UpdateImageFilters(const std::vector<double>& filter_coefficients);
void ProcessImageSequence(const std::vector<std::vector<double>>& image_sequence);
// --------------------------
};

}
#endif
