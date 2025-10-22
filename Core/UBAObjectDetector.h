/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAObjectDetectorH
#define UBAObjectDetectorH

#include "../../../Rdk/Deploy/Include/rdk.h"
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

// ������� ����� ��������������� �����������
class RDK_LIB_TYPE UBAObjectDetector
{
public:
// ��� ����������
struct Rect { int X,Y,Width,Height; };

// ����������� �� ���������
UBAObjectDetector() = default;
virtual ~UBAObjectDetector() = default;

public: // ������
// ---------------------
// ������ �����
// ---------------------
virtual bool Calculate(const UBitmap& input, Rect* objects)=0;
// ---------------------

// ---------------------
// ���������
// ---------------------
bool operator () (const UBitmap& input, Rect* objects);

// Modern C++20 methods with move semantics for object detection
// Thread-safe object detection
std::vector<Rect> DetectObjectsSafe(const UBitmap& input);
bool DetectObjectsSafe(const UBitmap& input, std::vector<Rect>& objects);

// Modern move semantics for large detection data
UBAObjectDetector(UBAObjectDetector&& other) noexcept;
UBAObjectDetector& operator=(UBAObjectDetector&& other) noexcept;

// Modern smart pointer factory
static std::shared_ptr<UBAObjectDetector> Create(void);

// Modern file operations with std::filesystem
bool LoadModelFromFile(const std::filesystem::path& filepath);
bool SaveModelToFile(const std::filesystem::path& filepath) const;

// ---------------------
};

// ����� �������� � ������ ��������
// �������� ���� �� ������
// "A real-time object detecting and tracking system for outdoor night surveillance"
// Kaiqi Huang, Liangsheng Wang, Tieniu Tan, Steve Maybank
class RDK_LIB_TYPE UBANightDetector: public UBAObjectDetector
{
public: // ���������
// ����� ����������� � �������
int HistorySize;

// ������ ����� �����������
int BlockWidth, BlockHeight;

// ������� ���������� ����������� ������
double AdaptiveThresholdPercent;

// ������� ��������, ����������� ���������� �����,
// ������ �����������
double MoveDetectionPercent;

// ������
double T1;

// ����������� ���������� ����� �������
double Tr;

protected: // ������
// ������ �����
int MapWidth, MapHeight;



protected: // ����� ��������� ����������
// ������� ������� �����������
const UBitmap* Input;

// ������ �����������
int Width,Height;

// ������������ �����������
UBitmap* LocalContrastedImages;

// ������� ������ �������
int CurrentHistorySize;

// ������� ������ ���� �������
int CurrentFirstHistoryIndex;

public: // ��������� ���������� ��� ���������� ���������� ���������
// ����� ������
int NumBlocks;

// ������ ��������� ����������
double* CL;

// ������ �������
double* ML;

// ������ ���
double* SigmaL;

protected: // ��������� ���������� ��� ���������� ����� ��������� �����������
// ����� ��������� �����
int NumMaps;

// ������ �����
double* MCm;
double* ICm;

// ����������� ����������� �����
UBitmap DiffImage;

// ����������� � ������������ ���������� ��������
UBitmap MovedImage;

// ����� ������ ����� ������ ���������
double* T;
double TT;

public:
// �����������
UBHistogram Histogram;

// ����� ����������� ��������
UBRect* ContrastGrid;

// ����� ���������� ��������
UBRect* MovedGrid;



protected: // ��������� ���������� ��� ����������� ���������� ��������
NCC2D Correlation;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UBANightDetector(void);
~UBANightDetector(void);
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����������� � �������
int GetHistorySize(void) const;
bool SetHistorySize(int value);
// --------------------------

// --------------------------
// ������ ������� � ������
// --------------------------
// ����������� � ������������ ���������� ��������
const UBitmap& GetMovedImage(void) const;
// --------------------------

// ---------------------
// ������ �����
// ---------------------
bool Calculate(const UBitmap& input, Rect* objects);
// ---------------------

// ---------------------
// ������� ������ �����
// ---------------------
protected:
// ���������� ���������� ���������
bool CalcLocalContrasting(void);

// ���������� ����� ��������� �����������
bool CalcLocalMap(void);

// ����������� ���������� ��������
bool CalcMovedObjects(void);

// ������ ����������� ������
bool CalcAdaptiveThreshold(void);
// ---------------------

// --------------------------
// Modern C++20 methods
// --------------------------
// Move semantics
UBANightDetector(const UBANightDetector&) = default;
UBANightDetector(UBANightDetector&&) noexcept = default;
UBANightDetector& operator=(const UBANightDetector&) = default;
UBANightDetector& operator=(UBANightDetector&&) noexcept = default;

// Modern object detection operations
void OptimizeObjectDetectionPerformance();
bool IsObjectDetectorValid() const;
void ReserveObjectDetectionMemory(size_t max_objects_count);
TimePoint GetLastDetectionTime() const;
void SetLastDetectionTime(TimePoint time);

// Modern detection algorithms
template<typename T>
void ReserveDetectionBuffer(std::vector<T>& buffer, size_t width, size_t height);

template<typename T>
void MoveDetectionBuffer(std::vector<T>& target, std::vector<T>&& source);

// Advanced computer vision algorithms
void UpdateDetectionParameters(const std::vector<double>& parameters);
void CalculateObjectFeatures(const std::vector<double>& image_data);
void OptimizeDetectionThreshold(double threshold_value);
void ProcessMultiScaleDetection(const std::vector<std::vector<double>>& image_pyramid);
// --------------------------
};


}

#endif
