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
virtual bool CheckComponentType(UEPtr<UContainer> comp) const;
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
virtual bool AAddComponent(UEPtr<UContainer> comp, UEPtr<UIPointer> pointer=0);

// ��������� ��������������� ���������������� ��������
// ��� �������� ��������� ���������� �� ����� �������
// ����� ����� ������ ������ ���� comp
// ���������� � ������ ���������
virtual bool ADelComponent(UEPtr<UContainer> comp);
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
// Move semantics
UBPipeline(const UBPipeline&) = default;
UBPipeline(UBPipeline&&) noexcept = default;
UBPipeline& operator=(const UBPipeline&) = default;
UBPipeline& operator=(UBPipeline&&) noexcept = default;

// Modern pipeline operations
void OptimizePipelinePerformance();
bool IsPipelineValid() const;
void ReservePipelineMemory(size_t components_count);
TimePoint GetLastPipelineUpdateTime() const;
void SetLastPipelineUpdateTime(TimePoint time);

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
